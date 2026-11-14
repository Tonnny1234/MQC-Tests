#!/usr/bin/env python3
"""Collect every result of a config and write a readable comparison against ASTRAL.

  python3 tools/report.py configs/smoke.json [--astral-q best|all|none] [--details auto|all|none]

writes  results/<name>/results.csv    one row per run (for your own analysis)
        results/<name>/report.md      the report as text
        results/<name>/report.html    the same report as a web page
Scores are quartet scores: the number of gene-tree quartets the species tree displays (ASTRAL's objective).
"""
import argparse
import csv
import glob
import html
import json
import os
import statistics
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import MQC, astral3_jar, clean_env, expand_datasets, java, load_config, rel, run, ROOT

BASE_LABEL = {"astral3": "ASTRAL-III", "astral3-exact": "ASTRAL-III exact", "astral4": "ASTRAL-IV", "astral4-R": "ASTRAL-IV -R"}


def num(x):
    return "" if x is None else "{:,}".format(x)


def secs(x):
    if x is None:
        return ""
    return "%.2f s" % x if x < 10 else ("%.0f s" % x if x < 600 else "%.1f h" % (x / 3600.0))


def load_runs(ds):
    runs = []
    for path in sorted(glob.glob(os.path.join(ds["dir"], "baseline", "*.json")) + glob.glob(os.path.join(ds["dir"], "search", "*.json"))):
        try:
            with open(path) as f:
                j = json.load(f)
        except ValueError:
            continue
        r = {"dataset": ds["name"], "json": path, "seed": j.get("seed"), "score": j.get("score"), "elapsed": j.get("elapsed"),
             "finished": bool(j.get("finished")), "tree": j.get("tree_file"), "reported": j.get("reported_score"),
             "mismatch": bool(j.get("score_mismatch")), "error": j.get("error", "")}
        if j.get("tool") == "mqc":
            tags = dict(t.split("=", 1) for t in j.get("tags", "").split(",") if "=" in t)
            r.update(kind="search", track=tags.get("track", "cold"), strategy=j["strategy"], start=tags.get("startname", j["start"]),
                     time_to_best=j.get("time_to_best"), start_score=j.get("start_score"), converged=bool(j.get("converged")))
            r["method"] = "%s / %s" % (r["strategy"], r["start"])
            if r["score"] is None:
                r["finished"] = False
        else:
            r.update(kind="baseline", track="baseline", strategy="", start="", method=BASE_LABEL.get(j.get("tool"), j.get("tool")),
                     tool=j.get("tool"), time_to_best=None, start_score=None, converged=True)
            if not r["finished"]:
                r["score"] = None
        if r["tree"] and not os.path.isabs(r["tree"]):
            r["tree"] = os.path.join(ROOT, r["tree"])
        runs.append(r)
    return runs


def best(runs):
    ok = [r for r in runs if r["score"] is not None]
    return max(ok, key=lambda r: r["score"]) if ok else None


def astral_q(run_, genes):
    """ASTRAL-III's own score for a tree (cached next to the result)."""
    cache = run_["json"][:-5] + ".astralq"
    if os.path.exists(cache):
        return int(open(cache).read().split()[0])
    tmp = cache + ".tre"
    code, out, err = run([java(), "-jar", astral3_jar(), "-q", run_["tree"], "-i", genes, "-o", tmp, "-t", "0"], env=clean_env())
    import re
    m = re.findall(r"Final quartet score is:\s*(\d+)", err + out)
    if os.path.exists(tmp):
        os.remove(tmp)
    if not m:
        return None
    with open(cache, "w") as f:
        f.write(m[0] + "\n")
    return int(m[0])


def rf(genes, t1, t2):
    code, out, err = run([MQC, "rf", "--genes", genes, "--tree1", t1, "--tree2", t2])
    return int(out.split()[0]) if code == 0 and out.split() else None


class Doc:
    """Collects sections and renders them as Markdown and as a self-contained HTML page."""

    def __init__(self, title):
        self.title, self.parts = title, []

    def h(self, text):
        self.parts.append(("h", text))

    def p(self, text):
        self.parts.append(("p", text))

    def table(self, head, rows):
        self.parts.append(("t", head, [[("" if c is None else str(c)) for c in r] for r in rows]))

    def markdown(self):
        out = ["# " + self.title, ""]
        for part in self.parts:
            if part[0] == "h":
                out += ["## " + part[1], ""]
            elif part[0] == "p":
                out += [part[1], ""]
            else:
                head, rows = part[1], part[2]
                w = [max(len(head[i]), max([len(r[i]) for r in rows] or [0])) for i in range(len(head))]
                out.append("| " + " | ".join(head[i].ljust(w[i]) for i in range(len(head))) + " |")
                out.append("|" + "|".join("-" * (w[i] + 2) for i in range(len(head))) + "|")
                out += ["| " + " | ".join(r[i].ljust(w[i]) for i in range(len(head))) + " |" for r in rows]
                out.append("")
        return "\n".join(out)

    def html(self):
        css = ("body{font:15px/1.5 -apple-system,Segoe UI,Helvetica,Arial,sans-serif;margin:32px auto;max-width:1150px;padding:0 16px;color:#1f2328}"
               "h1{font-size:24px}h2{font-size:18px;margin-top:36px;border-bottom:1px solid #d0d7de;padding-bottom:4px}"
               "table{border-collapse:collapse;margin:12px 0 20px;font-size:13.5px}th,td{border:1px solid #d0d7de;padding:4px 9px;text-align:right}"
               "th{background:#f6f8fa}td:first-child,th:first-child{text-align:left}"
               ".BEAT{background:#dafbe1;font-weight:600}.TIE{background:#f6f8fa}.BEHIND{background:#ffebe9}.ERROR{background:#ff8182;font-weight:600}")
        out = ["<!doctype html><html><head><meta charset='utf-8'><title>%s</title><style>%s</style></head><body><h1>%s</h1>" % (html.escape(self.title), css, html.escape(self.title))]
        for part in self.parts:
            if part[0] == "h":
                out.append("<h2>%s</h2>" % html.escape(part[1]))
            elif part[0] == "p":
                out.append("<p>%s</p>" % html.escape(part[1]))
            else:
                out.append("<table><tr>" + "".join("<th>%s</th>" % html.escape(c) for c in part[1]) + "</tr>")
                for r in part[2]:
                    cells = "".join("<td%s>%s</td>" % (" class='%s'" % c.split()[0] if c.split() and c.split()[0] in ("BEAT", "TIE", "BEHIND", "ERROR") else "", html.escape(c)) for c in r)
                    out.append("<tr>%s</tr>" % cells)
                out.append("</table>")
        out.append("</body></html>")
        return "\n".join(out)


def verdict(ours, ref):
    if ours is None or ref is None:
        return ""
    if ours > ref:
        return "BEAT +%s" % num(ours - ref)
    return "TIE" if ours == ref else "BEHIND -%s" % num(ref - ours)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("config")
    ap.add_argument("--astral-q", default="best", choices=["best", "all", "none"], help="which of our trees to re-score with ASTRAL-III -q")
    ap.add_argument("--details", default="auto", choices=["auto", "all", "none"], help="per-dataset tables (auto: skip subsampled datasets)")
    a = ap.parse_args()
    cfg = load_config(a.config)
    datasets = expand_datasets(cfg)
    have_jar = os.path.exists(astral3_jar())
    doc = Doc("Benchmark report: %s" % cfg["name"])
    allruns, per, checks = [], {}, []

    for ds in datasets:
        runs = load_runs(ds)
        allruns += runs
        base = [r for r in runs if r["kind"] == "baseline"]
        ours = [r for r in runs if r["kind"] == "search"]
        d = {"ds": ds, "runs": runs}
        d["a3"] = best([r for r in base if r.get("tool") == "astral3"])
        d["a4"] = best([r for r in base if r.get("tool") in ("astral4", "astral4-R")])
        d["exact"] = best([r for r in base if r.get("tool") == "astral3-exact"])
        d["warm"] = best([r for r in ours if r["track"] == "warm"])
        d["cold"] = best([r for r in ours if r["track"] == "cold"])
        refs = [x["score"] for x in (d["a3"], d["a4"]) if x]
        d["astral"] = max(refs) if refs else None
        known = [r["score"] for r in runs if r["score"] is not None]
        d["known"] = max(known) if known else None
        per[ds["name"]] = d
        for r in base:
            if r["mismatch"]:
                checks.append("SCORE MISMATCH: %s on %s reported %s but our scorer gives %s" % (r["method"], ds["name"], r["reported"], r["score"]))
        if d["exact"]:
            for r in runs:
                if r["score"] is not None and r["score"] > d["exact"]["score"]:
                    checks.append("IMPOSSIBLE: %s on %s scores above the exact optimum" % (r["method"], ds["name"]))
        if a.astral_q != "none" and have_jar:
            todo = ours if a.astral_q == "all" else [x for x in (d["warm"], d["cold"]) if x]
            for r in todo:
                if r["score"] is None or not r["tree"] or not os.path.exists(r["tree"]):
                    continue
                q = astral_q(r, ds["genes"])
                r["astral_q"] = q
                if q is not None and q != r["score"]:
                    checks.append("SCORE MISMATCH: ASTRAL -q gives %s for %s on %s, we report %s" % (q, r["method"], ds["name"], r["score"]))

    nruns = len(allruns)
    nfin = sum(1 for r in allruns if r["finished"])
    nq = sum(1 for r in allruns if r.get("astral_q") is not None)
    nrep = sum(1 for r in allruns if r["kind"] == "baseline" and r["reported"] is not None and r["score"] is not None)
    doc.p("Generated %s. %d datasets, %d runs (%d finished, %d unfinished or failed)." % (time.strftime("%Y-%m-%d %H:%M"), len(datasets), nruns, nfin, nruns - nfin))
    doc.p("Every score is the quartet score from one scorer (mqc score). Cross-checks: %d ASTRAL runs compared with the score ASTRAL printed, "
          "%d of our trees re-scored with ASTRAL-III -q; %d disagreements." % (nrep, nq, len(checks)))

    # ---- 1. overview ---------------------------------------------------------------------------------------
    doc.h("1. Overview: best score per dataset")
    doc.p("Warm = our search started from ASTRAL's tree. Cold = started from our own orders, no ASTRAL input. "
          "Each ASTRAL column is its best run over seeds. 'yes' under optimal means the exact optimum was reached.")
    rows, tally = [], {}
    for ds in datasets:
        d = per[ds["name"]]
        ex = d["exact"]["score"] if d["exact"] else None
        a3 = d["a3"]["score"] if d["a3"] else None
        a4 = d["a4"]["score"] if d["a4"] else None
        ow = d["warm"]["score"] if d["warm"] else None
        oc = d["cold"]["score"] if d["cold"] else None
        both = [x for x in (ow, oc) if x is not None]
        ob = max(both) if both else None
        row = [ds["name"], ds["n"], ds["k"], num(ex), num(a3), num(a4), num(ow), num(oc), verdict(ob, a3), verdict(ob, a4)]
        for tr, o in (("warm", ow), ("cold", oc)):
            for nm, ref in (("ASTRAL-III", a3), ("ASTRAL-IV", a4)):
                v = verdict(o, ref)
                if v:
                    tally.setdefault("%s vs %s" % (tr, nm), [0, 0, 0])[0 if v.startswith("BEAT") else 1 if v == "TIE" else 2] += 1
        opt = ""
        if ex is not None:
            flags = [("ASTRAL-III", d["a3"]), ("ASTRAL-IV", d["a4"]), ("warm", d["warm"]), ("cold", d["cold"])]
            opt = ", ".join("%s %s" % (nm, "yes" if x["score"] == ex else "no") for nm, x in flags if x)
        row.append(opt)
        rows.append(row)
    doc.table(["dataset", "taxa", "genes", "exact optimum", "ASTRAL-III", "ASTRAL-IV", "ours warm", "ours cold", "our best vs ASTRAL-III", "our best vs ASTRAL-IV", "optimal?"], rows)
    doc.p("Datasets won, tied and lost by each track against each ASTRAL (best run of each):")
    doc.table(["comparison", "BEAT", "TIE", "BEHIND"], [[k] + tally[k] for k in sorted(tally)])

    # ---- 2. subsampled groups ------------------------------------------------------------------------------
    groups = {}
    for ds in datasets:
        if ds["parent"]:
            groups.setdefault("%s, %d taxa" % (ds["parent"], ds["n"]), []).append(per[ds["name"]])
    if groups:
        doc.h("2. Subsampled datasets with known optimum")
        doc.p("Each cell counts the instances where that method's best run reached the exact optimum.")
        rows = []
        for g in sorted(groups):
            ds_ = [d for d in groups[g] if d["exact"]]

            def cnt(key):
                have = [d for d in ds_ if d[key]]
                return "%d / %d" % (sum(1 for d in have if d[key]["score"] == d["exact"]["score"]), len(have)) if have else ""
            beat = sum(1 for d in groups[g] if d["astral"] is not None and max([x["score"] for x in (d["warm"], d["cold"]) if x] or [-1]) > d["astral"])
            rows.append([g, len(groups[g]), len(ds_), cnt("a3"), cnt("a4"), cnt("warm"), cnt("cold"), beat])
        doc.table(["group", "instances", "with exact optimum", "ASTRAL-III optimal", "ASTRAL-IV optimal", "ours warm optimal", "ours cold optimal", "instances where we beat both ASTRALs"], rows)

    # ---- 3. methods across datasets ------------------------------------------------------------------------
    doc.h("3. Methods across all datasets")
    doc.p("One row per method. W/T/L compares the method's best run on each dataset with the better ASTRAL. "
          "Gap is the average shortfall from the best score any method found, over all runs. Optimal counts runs on datasets with a known optimum.")
    meth = {}
    for r in allruns:
        if r["score"] is None:
            continue
        meth.setdefault((r["track"], r["method"]), []).append(r)
    rows = []
    order = {"baseline": 0, "warm": 1, "cold": 2}
    for key in sorted(meth, key=lambda k: (order[k[0]], k[1])):
        rs = meth[key]
        w = t = l = 0
        for name in sorted(set(r["dataset"] for r in rs)):
            d = per[name]
            b = max(r["score"] for r in rs if r["dataset"] == name)
            if d["astral"] is None:
                continue
            w, t, l = w + (b > d["astral"]), t + (b == d["astral"]), l + (b < d["astral"])
        gaps = [100.0 * (per[r["dataset"]]["known"] - r["score"]) / per[r["dataset"]]["known"] for r in rs if per[r["dataset"]]["known"]]
        exr = [r for r in rs if per[r["dataset"]]["exact"]]
        opt = "%d / %d" % (sum(1 for r in exr if r["score"] == per[r["dataset"]]["exact"]["score"]), len(exr)) if exr else ""
        ge = [r for r in rs if per[r["dataset"]]["astral"] is not None]
        geq = "%d / %d" % (sum(1 for r in ge if r["score"] >= per[r["dataset"]]["astral"]), len(ge)) if ge else ""
        ttb = [r["time_to_best"] for r in rs if r["time_to_best"] is not None]
        rows.append([key[0], key[1], len(set(r["dataset"] for r in rs)), len(rs), "%d / %d / %d" % (w, t, l), geq, opt,
                     "%.4f%%" % (sum(gaps) / len(gaps)) if gaps else "", secs(statistics.median(ttb)) if ttb else "",
                     secs(statistics.median([r["elapsed"] for r in rs if r["elapsed"] is not None] or [0]))])
    doc.table(["track", "method", "datasets", "runs", "W / T / L vs ASTRAL", "runs >= ASTRAL", "runs optimal", "mean gap to best", "median time to best", "median run time"], rows)

    # ---- 4. per-dataset detail -----------------------------------------------------------------------------
    if a.details != "none":
        shown = [ds for ds in datasets if a.details == "all" or not ds["parent"]]
        if shown:
            doc.h("4. Detail per dataset")
        for ds in shown:
            d = per[ds["name"]]
            doc.p("%s: %d taxa, %d gene trees. Best known score %s; better ASTRAL %s%s." % (
                ds["name"], ds["n"], ds["k"], num(d["known"]), num(d["astral"]), "; exact optimum %s" % num(d["exact"]["score"]) if d["exact"] else ""))
            by = {}
            for r in d["runs"]:
                by.setdefault((order[r["track"]], r["track"], r["method"]), []).append(r)
            rows = []
            for key in sorted(by):
                rs = by[key]
                sc = [r["score"] for r in rs if r["score"] is not None]
                if not sc:
                    rows.append([key[1], key[2], len(rs), "failed: " + (rs[0]["error"] or "no result"), "", "", "", "", "", ""])
                    continue
                b = best(rs)
                rfd = ""
                if key[1] != "baseline" and d["a3"] and b["tree"] and os.path.exists(b["tree"]) and d["a3"]["tree"] and os.path.exists(d["a3"]["tree"]):
                    x = rf(ds["genes"], b["tree"], d["a3"]["tree"])
                    rfd = "" if x is None else str(x)
                ttb = [r["time_to_best"] for r in rs if r["time_to_best"] is not None]
                rows.append([key[1], key[2], len(rs), num(max(sc)), num(int(statistics.median(sc))), num(min(sc)),
                             verdict(max(sc), d["astral"]) if key[1] != "baseline" else "", secs(statistics.median(ttb)) if ttb else "",
                             secs(statistics.median([r["elapsed"] for r in rs if r["elapsed"] is not None] or [0])), rfd])
            doc.table(["track", "method", "runs", "best", "median", "worst", "best vs ASTRAL", "median time to best", "median run time", "RF to ASTRAL-III tree"], rows)

    # ---- 5. checks -----------------------------------------------------------------------------------------
    doc.h("5. Checks")
    unfinished = [r for r in allruns if not r["finished"]]
    if not checks and not unfinished:
        doc.p("All scorers agree, no result exceeds an exact optimum, and every run finished.")
    for c in checks:
        doc.p("ERROR " + c)
    if unfinished:
        doc.p("%d runs are unfinished or failed. Resubmit the same task file to resume them. First few:" % len(unfinished))
        doc.table(["dataset", "method", "seed", "reason"], [[r["dataset"], r["method"], r["seed"], r["error"] or "time limit reached, checkpoint saved"] for r in unfinished[:15]])

    outdir = os.path.join(ROOT, "results", cfg["name"])
    os.makedirs(outdir, exist_ok=True)
    cols = ["dataset", "kind", "track", "method", "strategy", "start", "seed", "score", "start_score", "elapsed", "time_to_best", "finished", "converged", "reported", "astral_q", "tree"]
    with open(os.path.join(outdir, "results.csv"), "w", newline="") as f:
        wr = csv.DictWriter(f, fieldnames=cols, extrasaction="ignore")
        wr.writeheader()
        for r in allruns:
            wr.writerow(r)
    with open(os.path.join(outdir, "report.md"), "w") as f:
        f.write(doc.markdown())
    with open(os.path.join(outdir, "report.html"), "w") as f:
        f.write(doc.html())
    print(doc.markdown())
    print("\nwrote %s/{results.csv, report.md, report.html}" % rel(outdir))
    sys.exit(1 if checks else 0)


if __name__ == "__main__":
    main()
