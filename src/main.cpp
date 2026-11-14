// mqc - Maximum Quartet Consistency by search over circular orders with an exact O(M + n^3) DP per order.
// Commands: search, score, eval, table, info, subsample, rf, selftest.   Run `mqc help` for usage.
#include "search.hpp"
#include <ctime>
#include <sys/stat.h>

typedef std::map<std::string, std::string> Args;
static Args parse_args(int argc, char** argv, int from) {
    Args a;
    for (int i = from; i < argc; ++i) {
        std::string k = argv[i];
        if (k.size() < 3 || k.substr(0, 2) != "--") die("unexpected argument '" + k + "'");
        k = k.substr(2);
        if (i + 1 < argc && std::string(argv[i + 1]).substr(0, 2) != "--") a[k] = argv[++i]; else a[k] = "1";
    }
    return a;
}
static std::string get(const Args& a, const std::string& k, const std::string& def = "") { Args::const_iterator it = a.find(k); return it == a.end() ? def : it->second; }
static std::string need(const Args& a, const std::string& k) { if (!a.count(k)) die("missing --" + k); return a.find(k)->second; }
static bool file_exists(const std::string& p) { struct stat st; return ::stat(p.c_str(), &st) == 0; }
static std::string read_file(const std::string& p) { std::ifstream in(p.c_str()); std::stringstream ss; ss << in.rdbuf(); return ss.str(); }
static void write_atomic(const std::string& path, const std::string& content) {
    std::string tmp = path + ".part";
    { std::ofstream o(tmp.c_str()); if (!o) die("cannot write " + tmp); o << content; }
    std::rename(tmp.c_str(), path.c_str());
}
static std::string jstr(const std::string& s) {
    std::string o = "\"";
    for (size_t i = 0; i < s.size(); ++i) { if (s[i] == '"' || s[i] == '\\') o += '\\'; o += s[i]; }
    return o + "\"";
}

static double load_table(const GeneSet& G, const Args& a, QTable& T) {
    Timer t; std::string path = get(a, "table");
    if (!path.empty() && T.load(path, G.names)) return t.sec();
    T.build(G);
    if (!path.empty()) T.save(path);
    return t.sec();
}

static NTree read_species_tree(const std::string& newick, const GeneSet& G) {
    NTree t; std::string err;
    if (!load_full_tree(newick, G, t, err)) die(err);
    return t;
}

static std::vector<int> make_start(const std::string& type, const GeneSet& G, const QTable& T, Engine& E, Rng& rng, const Args& a) {
    int n = G.n();
    if (type == "random") return start_random(n, rng);
    if (type == "genetree") return start_genetree(G, rng);
    if (type == "distance") return start_distance(G, rng);
    if (type == "caterpillar") return start_caterpillar(T, rng);
    if (type == "greedy") return start_greedy(T, rng);
    if (type == "tree" || type == "bestrandom") {
        NTree st;
        if (type == "tree") {
            std::vector<std::string> s = read_newick_strings(need(a, "start-tree"));
            if (s.empty()) die("no tree in --start-tree file");
            st = read_species_tree(s[0], G);
        }
        int K = std::atoi(get(a, "start-orients", type == "tree" ? "1" : "32").c_str());
        std::vector<int> best; i64 bv = -1; State s;
        for (int r = 0; r < std::max(1, K); ++r) {
            s.ord = type == "tree" ? ntree_order(st, rng) : start_random(n, rng);
            if (K <= 1) return s.ord;
            E.rebuild(s); i64 v = E.eval(s);
            if (v > bv) { bv = v; best = s.ord; }
        }
        return best;
    }
    die("unknown --start '" + type + "' (random, genetree, distance, caterpillar, greedy, bestrandom, tree)");
}

// ---- search ----------------------------------------------------------------------------------------------
static int cmd_search(const Args& a) {
    std::string genes = need(a, "genes"), out = need(a, "out"), strategy = get(a, "strategy", "vnd"), start = get(a, "start", "random");
    i64 seed = std::atoll(get(a, "seed", "1").c_str());
    double budget = std::atof(get(a, "time", "60").c_str()), maxRun = std::atof(get(a, "max-run", "1e18").c_str());
    const char* dl = std::getenv("MQC_DEADLINE_EPOCH");     // set by the Slurm wrapper: stop (and checkpoint) before the job is killed
    if (dl && !a.count("max-run")) maxRun = std::max(1.0, std::atof(dl) - (double)std::time(NULL));
    double ckptEvery = std::atof(get(a, "checkpoint-every", "60").c_str());
    std::string jsonPath = out + ".json", ckptPath = out + ".ckpt", treePath = out + ".tre";
    if (file_exists(jsonPath) && read_file(jsonPath).find("\"finished\": true") != std::string::npos) {
        std::fprintf(stderr, "mqc: %s already finished; nothing to do\n", jsonPath.c_str()); return 0;
    }
    GeneSet G = load_genes(genes);
    QTable T; double tableSec = load_table(G, a, T);
    int n = G.n();
    Engine E(T);

    int resumes = 0; double elapsedBefore = 0; i64 startVal = -1, evals0 = 0, rebuilds0 = 0, swaps0 = 0;
    std::vector<std::pair<double, i64> > traj0; std::vector<int> resumeOrd;
    if (file_exists(ckptPath)) {                       // resume from the best order found so far
        std::ifstream in(ckptPath.c_str()); std::string key;
        while (in >> key) {
            if (key == "elapsed") in >> elapsedBefore;
            else if (key == "resumes") in >> resumes;
            else if (key == "startscore") in >> startVal;
            else if (key == "counts") in >> evals0 >> rebuilds0 >> swaps0;
            else if (key == "traj") { double t; i64 v; in >> t >> v; traj0.push_back(std::make_pair(t, v)); }
            else if (key == "order") { resumeOrd.resize(n); for (int i = 0; i < n; ++i) in >> resumeOrd[i]; }
        }
        ++resumes;
    }
    Rng rng((uint64_t)(seed * 1000003LL + 7919LL * resumes + 17));
    Search S(E, rng);
    S.budget = budget; S.maxRun = maxRun; S.elapsedBefore = elapsedBefore;
    S.newStart = [&]() { std::string t = (start == "tree" || start == "caterpillar" || start == "distance") ? "random" : start; return make_start(t, G, T, E, rng, a); };
    std::signal(SIGTERM, on_signal); std::signal(SIGINT, on_signal); std::signal(SIGUSR1, on_signal);

    if (!resumeOrd.empty()) { S.set_current(resumeOrd); S.traj = traj0; S.startVal = startVal; }
    else S.set_current(make_start(start, G, T, E, rng, a));

    auto save_ckpt = [&]() {
        std::ostringstream o;
        o << "elapsed " << S.elapsed() << "\nresumes " << resumes << "\nstartscore " << S.startVal
          << "\ncounts " << evals0 + E.nEval << " " << rebuilds0 + E.nRebuild << " " << swaps0 + E.nSwap << "\n";
        for (size_t i = 0; i < S.traj.size(); ++i) o << "traj " << S.traj[i].first << " " << S.traj[i].second << "\n";
        o << "order"; for (int i = 0; i < n; ++i) o << " " << S.bestOrd[i]; o << "\n";
        write_atomic(ckptPath, o.str());
    };
    double lastCkpt = 0;
    S.tick = [&]() { double t = S.timer.sec(); if (t - lastCkpt >= ckptEvery) { lastCkpt = t; save_ckpt(); } };

    if (!S.run(strategy)) die("unknown --strategy '" + strategy + "' (dp, reorient, pairswap-first, pairswap-best, vnd, anneal, ils, tabu, multistart)");

    bool finished = S.elapsed() >= budget || !S.stoppedEarly;
    std::string newick = treebin_newick(S.bestTree, G.names);
    NTree chk = read_species_tree(newick, G);
    i64 indep = score_tree(T, chk);                    // independent re-score of the output tree
    if (indep != S.bestVal) die("internal check failed: DP score " + std::to_string(S.bestVal) + " but tree scores " + std::to_string(indep));
    write_atomic(treePath, newick + "\n");
    if (!finished) save_ckpt();

    std::ostringstream j;
    j.precision(10);
    j << "{\n  \"tool\": \"mqc\",\n  \"genes\": " << jstr(genes) << ",\n  \"n\": " << n << ",\n  \"k\": " << T.ntrees
      << ",\n  \"skipped_trees\": " << G.skipped << ",\n  \"strategy\": " << jstr(strategy) << ",\n  \"start\": " << jstr(start)
      << ",\n  \"seed\": " << seed << ",\n  \"time_budget\": " << budget << ",\n  \"elapsed\": " << S.elapsed()
      << ",\n  \"finished\": " << (finished ? "true" : "false") << ",\n  \"converged\": " << (!S.stoppedEarly ? "true" : "false")
      << ",\n  \"score\": " << S.bestVal << ",\n  \"start_score\": " << S.startVal << ",\n  \"total_weight\": " << T.total
      << ",\n  \"normalized\": " << (T.total ? (double)S.bestVal / (double)T.total : 0.0)
      << ",\n  \"time_to_best\": " << (S.traj.empty() ? 0.0 : S.traj.back().first) << ",\n  \"table_seconds\": " << tableSec
      << ",\n  \"evals\": " << evals0 + E.nEval << ",\n  \"rebuilds\": " << rebuilds0 + E.nRebuild << ",\n  \"swaps\": " << swaps0 + E.nSwap
      << ",\n  \"resumes\": " << resumes << ",\n  \"tags\": " << jstr(get(a, "tags")) << ",\n  \"tree_file\": " << jstr(treePath) << ",\n  \"traj\": [";
    for (size_t i = 0; i < S.traj.size(); ++i) j << (i ? ", " : "") << "[" << S.traj[i].first << ", " << S.traj[i].second << "]";
    j << "],\n  \"order\": [";
    for (int i = 0; i < n; ++i) j << (i ? ", " : "") << jstr(G.names[S.bestOrd[i]]);
    j << "]\n}\n";
    write_atomic(jsonPath, j.str());
    if (finished) std::remove(ckptPath.c_str());
    std::fprintf(stderr, "mqc: %s start=%s seed=%lld  score %lld (start %lld, %.4f of total)  %.1fs%s\n", strategy.c_str(), start.c_str(),
                 (long long)seed, (long long)S.bestVal, (long long)S.startVal, T.total ? (double)S.bestVal / T.total : 0.0, S.elapsed(),
                 finished ? "" : "  [unfinished: rerun the same command to resume]");
    return 0;
}

// ---- small commands ----------------------------------------------------------------------------------------
static int cmd_score(const Args& a) {
    GeneSet G = load_genes(need(a, "genes")); QTable T; load_table(G, a, T);
    std::vector<std::string> trees = read_newick_strings(need(a, "trees"));
    for (size_t i = 0; i < trees.size(); ++i) {
        i64 s = score_tree(T, read_species_tree(trees[i], G));
        std::printf("%lld %lld %.10f\n", (long long)s, (long long)T.total, T.total ? (double)s / T.total : 0.0);
    }
    return 0;
}
static int cmd_eval(const Args& a) {                   // one order per line (taxon names); prints DP score and tree
    GeneSet G = load_genes(need(a, "genes")); QTable T; load_table(G, a, T);
    Engine E(T); State s; TreeBin tb;
    std::ifstream in(need(a, "orders").c_str()); std::string line;
    while (std::getline(in, line)) {
        std::istringstream ls(line); std::string nm; s.ord.clear();
        while (ls >> nm) { if (!G.id.count(nm)) die("unknown taxon " + nm); s.ord.push_back(G.id.find(nm)->second); }
        if (s.ord.empty()) continue;
        if ((int)s.ord.size() != G.n()) die("each order must list every taxon once");
        E.rebuild(s); i64 v = E.eval(s); E.extract(s, tb);
        std::printf("%lld\t%s\n", (long long)v, treebin_newick(tb, G.names).c_str());
    }
    return 0;
}
static int cmd_table(const Args& a) {
    GeneSet G = load_genes(need(a, "genes")); QTable T; Timer t; T.build(G); T.save(need(a, "out"));
    std::fprintf(stderr, "mqc: table for %d taxa, %lld gene trees, total weight %lld, built in %.1fs\n", T.n, (long long)T.ntrees, (long long)T.total, t.sec());
    return 0;
}
static int cmd_info(const Args& a) {
    GeneSet G = load_genes(need(a, "genes")); int complete = 0;
    for (size_t i = 0; i < G.trees.size(); ++i) if ((int)G.trees[i].leaves().size() == G.n()) ++complete;
    std::printf("{\"n\": %d, \"k\": %d, \"complete_trees\": %d, \"skipped_trees\": %d}\n", G.n(), (int)G.trees.size(), complete, G.skipped);
    return 0;
}
static void prune_newick(const NTree& t, int v, const std::vector<char>& keep, std::string& out) {
    if (t.is_leaf(v)) { if (keep[t.taxon[v]]) out = t.label[v]; return; }
    std::vector<std::string> parts;
    for (size_t x = 0; x < t.ch[v].size(); ++x) { std::string s; prune_newick(t, t.ch[v][x], keep, s); if (!s.empty()) parts.push_back(s); }
    if (parts.empty()) return;
    if (parts.size() == 1) { out = parts[0]; return; }
    out = "(";
    for (size_t x = 0; x < parts.size(); ++x) out += (x ? "," : "") + parts[x];
    out += ")";
}
static int cmd_subsample(const Args& a) {              // restrict every gene tree to a random subset of taxa
    GeneSet G = load_genes(need(a, "genes")); int m = std::atoi(need(a, "ntaxa").c_str());
    if (m < 4 || m > G.n()) die("--ntaxa must be between 4 and the number of taxa");
    Rng rng((uint64_t)std::atoll(get(a, "seed", "1").c_str()) * 7477 + 5);
    std::vector<int> o = start_random(G.n(), rng); std::vector<char> keep(G.n(), 0);
    for (int i = 0; i < m; ++i) keep[o[i]] = 1;
    std::ostringstream out; int kept = 0;
    for (size_t i = 0; i < G.trees.size(); ++i) {
        int cnt = 0; std::vector<int> L = G.trees[i].leaves();
        for (size_t x = 0; x < L.size(); ++x) cnt += keep[G.trees[i].taxon[L[x]]];
        if (cnt < 4) continue;
        std::string s; prune_newick(G.trees[i], G.trees[i].root, keep, s); out << s << ";\n"; ++kept;
    }
    write_atomic(need(a, "out"), out.str());
    std::fprintf(stderr, "mqc: kept %d taxa, %d gene trees -> %s\n", m, kept, need(a, "out").c_str());
    return 0;
}
static std::vector<std::string> splits_of(const NTree& t, int n) {
    std::vector<std::string> out; std::vector<std::string> below(t.parent.size());
    for (int v = (int)t.parent.size() - 1; v >= 0; --v) {       // children always have larger ids than parents
        if (t.is_leaf(v)) { below[v] = std::string(n, '0'); below[v][t.taxon[v]] = '1'; }
        else { below[v] = std::string(n, '0'); for (size_t x = 0; x < t.ch[v].size(); ++x) for (int i = 0; i < n; ++i) if (below[t.ch[v][x]][i] == '1') below[v][i] = '1'; }
        int c = (int)std::count(below[v].begin(), below[v].end(), '1');
        if (c < 2 || c > n - 2) continue;
        std::string s = below[v];
        if (s[0] == '1') for (int i = 0; i < n; ++i) s[i] = s[i] == '1' ? '0' : '1';
        out.push_back(s);
    }
    std::sort(out.begin(), out.end()); out.erase(std::unique(out.begin(), out.end()), out.end());
    return out;
}
static int cmd_rf(const Args& a) {                     // Robinson-Foulds distance between two trees on all taxa
    GeneSet G = load_genes(need(a, "genes"));
    std::vector<std::string> s1 = read_newick_strings(need(a, "tree1")), s2 = read_newick_strings(need(a, "tree2"));
    if (s1.empty() || s2.empty()) die("empty tree file");
    std::vector<std::string> A = splits_of(read_species_tree(s1[0], G), G.n()), B = splits_of(read_species_tree(s2[0], G), G.n()), C;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::back_inserter(C));
    std::printf("%d %d\n", (int)(A.size() + B.size() - 2 * C.size()), 2 * (G.n() - 3));
    return 0;
}

// ---- selftest: randomized internal checks on synthetic weights ---------------------------------------------
static void all_interval_trees(int i, int j, const std::vector<int>& ord, const std::vector<std::string>& nm, std::vector<std::string>& out) {
    if (i == j) { out.push_back(nm[ord[i - 1]]); return; }
    for (int k = i; k < j; ++k) {
        std::vector<std::string> L, R; all_interval_trees(i, k, ord, nm, L); all_interval_trees(k + 1, j, ord, nm, R);
        for (size_t x = 0; x < L.size(); ++x) for (size_t y = 0; y < R.size(); ++y) out.push_back("(" + L[x] + "," + R[y] + ")");
    }
}
static int cmd_selftest(const Args& a) {
    int trials = std::atoi(get(a, "trials", "30").c_str()); Rng rng((uint64_t)std::atoll(get(a, "seed", "1").c_str()));
    int fails = 0, checks = 0;
    #define CHECK(cond, what) do { ++checks; if (!(cond)) { ++fails; std::printf("FAIL: %s (n=%d trial=%d)\n", what, n, tr); } } while (0)
    for (int tr = 0; tr < trials; ++tr) {
        int n = 5 + rng.below(tr % 3 == 0 ? 5 : 14);
        GeneSet G; for (int i = 0; i < n; ++i) { char b[16]; std::snprintf(b, 16, "t%02d", i); G.names.push_back(b); G.id[b] = i; }
        QTable T; T.init(n, G.names);
        for (size_t i = 0; i < T.w.size(); ++i) T.w[i] = rng.below(3) == 0 ? 0 : (uint32_t)rng.below(50);
        T.finish();
        Engine E(T); State s, r; TreeBin tb;
        s.ord = start_random(n, rng); E.rebuild(s);
        for (int x = 0; x < 6; ++x) { int p = rng.below(n), q = rng.below(n); E.apply_swap(s, p, q); }
        r.ord = s.ord; E.rebuild(r);
        CHECK(r.D == s.D && r.wout == s.wout, "incremental swap equals full rebuild");
        i64 v = E.eval(s); E.extract(s, tb);
        std::string nw = treebin_newick(tb, G.names);
        CHECK(score_tree(T, read_species_tree(nw, G)) == v, "DP value equals independent score of its tree");
        State rot; rot.ord = s.ord; std::rotate(rot.ord.begin(), rot.ord.begin() + 1 + rng.below(n - 1), rot.ord.end()); E.rebuild(rot);
        CHECK(E.eval(rot) == v, "rotating the order does not change the optimum");
        std::reverse(rot.ord.begin(), rot.ord.end()); E.rebuild(rot);
        CHECK(E.eval(rot) == v, "mirroring the order does not change the optimum");
        State fl; fl.ord = treebin_order(tb, -1, &rng); E.rebuild(fl);
        CHECK(E.eval(fl) >= v, "re-orienting the optimal tree never lowers the score");
        fl.ord = treebin_order(tb, rng.below((int)tb.nodes.size()), NULL); E.rebuild(fl);
        CHECK(E.eval(fl) >= v, "flipping one node never lowers the score");
        State cat; cat.ord = start_caterpillar(T, rng); E.rebuild(cat);
        std::string cn = "(" + G.names[cat.ord[0]] + "," + G.names[cat.ord[1]] + ")";
        for (int i = 2; i < n - 1; ++i) cn = "(" + cn + "," + G.names[cat.ord[i]] + ")";
        cn = "(" + cn + "," + G.names[cat.ord[n - 1]] + ");";
        i64 cs = score_tree(T, read_species_tree(cn, G));
        CHECK(3 * cs >= T.total, "deterministic caterpillar scores at least a third of the total weight");
        CHECK(E.eval(cat) >= cs, "DP on the caterpillar order is at least the caterpillar");
        State gr; gr.ord = start_greedy(T, rng); std::vector<int> srt = gr.ord; std::sort(srt.begin(), srt.end());
        bool perm = true; for (int i = 0; i < n; ++i) perm = perm && srt[i] == i;
        CHECK(perm, "greedy start is a permutation");
        if (n <= 9) {                                   // brute force: every tree compatible with the order
            std::vector<std::string> all; all_interval_trees(1, n - 1, s.ord, G.names, all);
            i64 best = -1;
            for (size_t x = 0; x < all.size(); ++x) best = std::max(best, score_tree(T, read_species_tree("(" + all[x] + "," + G.names[s.ord[n - 1]] + ");", G)));
            CHECK(best == v, "DP equals brute force over all compatible trees");
        }
        Search S(E, rng); S.budget = 0.3; S.set_current(start_random(n, rng)); i64 st = S.curVal; S.run("vnd");
        CHECK(S.bestVal >= st, "search never returns less than its start");
        CHECK(score_tree(T, read_species_tree(treebin_newick(S.bestTree, G.names), G)) == S.bestVal, "search result tree scores what the search reports");
    }
    std::printf("selftest: %d checks, %d failures\n", checks, fails);
    return fails ? 1 : 0;
}

int main(int argc, char** argv) {
    std::string cmd = argc > 1 ? argv[1] : "help";
    if (cmd == "help" || cmd == "--help" || cmd == "-h") {
        std::printf(
            "mqc <command> [--option value ...]\n\n"
            "  search    --genes G --out PREFIX [--strategy vnd] [--start random] [--seed 1] [--time 60]\n"
            "            [--table T] [--start-tree F] [--start-orients K] [--max-run SEC] [--tags a=b,c=d]\n"
            "            strategies: dp reorient pairswap-first pairswap-best vnd anneal ils tabu multistart\n"
            "            starts:     random genetree distance caterpillar greedy bestrandom tree\n"
            "            writes PREFIX.tre and PREFIX.json; rerunning an unfinished run resumes it\n"
            "  score     --genes G --trees F [--table T]     quartet score of each tree in F\n"
            "  eval      --genes G --orders F [--table T]    exact DP for each order (taxon names per line)\n"
            "  table     --genes G --out T                   build and save the quartet-weight table\n"
            "  info      --genes G                           taxa and gene-tree counts\n"
            "  subsample --genes G --ntaxa M --seed S --out F  restrict gene trees to M random taxa\n"
            "  rf        --genes G --tree1 A --tree2 B       Robinson-Foulds distance and its maximum\n"
            "  selftest  [--trials 30] [--seed 1]            internal correctness checks\n");
        return 0;
    }
    Args a = parse_args(argc, argv, 2);
    if (cmd == "search") return cmd_search(a);
    if (cmd == "score") return cmd_score(a);
    if (cmd == "eval") return cmd_eval(a);
    if (cmd == "table") return cmd_table(a);
    if (cmd == "info") return cmd_info(a);
    if (cmd == "subsample") return cmd_subsample(a);
    if (cmd == "rf") return cmd_rf(a);
    if (cmd == "selftest") return cmd_selftest(a);
    die("unknown command '" + cmd + "'; try: mqc help");
}
