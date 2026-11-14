// search.hpp - local search over circular orders. Every candidate order is scored exactly by the DP.
#pragma once
#include "starts.hpp"
#include <cmath>
#include <csignal>
#include <functional>

static volatile std::sig_atomic_t g_stop = 0;
inline void on_signal(int) { g_stop = 1; }

struct Search {
    Engine& E; const QTable& T; Rng& rng; int n;
    State cur, tmp;
    i64 curVal = 0; TreeBin curTree;
    i64 bestVal = -1, startVal = -1; std::vector<int> bestOrd; TreeBin bestTree;
    Timer timer;
    double budget = 60, elapsedBefore = 0, maxRun = 1e18;   // total budget, time used by earlier runs, cap for this run
    double temp = 0;                                        // 0: accept only strict improvements; >0: Metropolis
    bool stoppedEarly = false;                              // true when a time limit or a signal cut the run
    std::vector<std::pair<double, i64> > traj;              // (elapsed seconds, best score) at every improvement
    std::function<void()> tick;                             // called now and then, used for checkpoints
    std::function<std::vector<int>()> newStart;             // fresh starting order (multi-start)

    Search(Engine& e, Rng& r) : E(e), T(e.T), rng(r), n(e.n) {}

    double elapsed() const { return elapsedBefore + timer.sec(); }
    bool time_up() {
        if (g_stop || elapsed() >= budget || timer.sec() >= maxRun) { stoppedEarly = true; return true; }
        if (tick) tick();
        return false;
    }
    void note_best() {
        if (curVal > bestVal) { bestVal = curVal; bestOrd = cur.ord; bestTree = curTree; traj.push_back(std::make_pair(elapsed(), bestVal)); }
    }
    bool accept(i64 v) {
        if (v > curVal) return true;
        if (temp <= 0) return false;
        if (v == curVal) return true;
        return rng.unif() < std::exp((double)(v - curVal) / temp);
    }
    void commit_tmp(i64 v) {                         // tmp was just evaluated: make it current
        std::swap(cur.ord, tmp.ord); std::swap(cur.D, tmp.D); std::swap(cur.wout, tmp.wout);
        curVal = v; E.extract(cur, curTree); note_best();
    }
    void set_current(const std::vector<int>& o) {    // jump to an arbitrary order
        tmp.ord = o; E.rebuild(tmp); i64 v = E.eval(tmp); commit_tmp(v);
        if (startVal < 0) startVal = v;
    }
    i64 peek_swap(int p, int q) {                    // score after swapping positions p,q; result stays in tmp
        tmp.ord = cur.ord; tmp.D = cur.D; tmp.wout = cur.wout;
        E.apply_swap(tmp, p, q);
        return E.eval(tmp);
    }
    bool try_swap(int p, int q) { i64 v = peek_swap(p, q); if (accept(v)) { commit_tmp(v); return true; } return false; }
    void force_swap(int p, int q) { i64 v = peek_swap(p, q); commit_tmp(v); }
    bool try_order(const std::vector<int>& o) {
        tmp.ord = o; E.rebuild(tmp); i64 v = E.eval(tmp);
        if (accept(v)) { commit_tmp(v); return true; }
        return false;
    }

    // ---- neighbourhoods: one shuffled pass each, taking every improvement found; true if anything improved ----
    bool nb_flip() {                                 // N0: re-orient the current best tree (never worse)
        bool any = false, found = true;
        while (found && !time_up()) {
            found = false;
            std::vector<int> idx(curTree.nodes.size()); for (size_t i = 0; i < idx.size(); ++i) idx[i] = (int)i; rng.shuffle(idx);
            for (size_t x = 0; x < idx.size() && !found; ++x) { if (time_up()) return any; if (try_order(treebin_order(curTree, idx[x], NULL))) found = true; }
            for (int r = 0; r < 8 && !found; ++r) { if (time_up()) return any; if (try_order(treebin_order(curTree, -1, &rng))) found = true; }
            any = any || found;
        }
        return any;
    }
    bool nb_adjacent() {                             // N1
        bool any = false;
        std::vector<int> ps(n); for (int i = 0; i < n; ++i) ps[i] = i; rng.shuffle(ps);
        for (int x = 0; x < n; ++x) { if (time_up()) break; if (try_swap(ps[x], (ps[x] + 1) % n)) any = true; }
        return any;
    }
    std::vector<std::pair<int, int> > all_pairs() {
        std::vector<std::pair<int, int> > pr;
        for (int p = 0; p < n; ++p) for (int q = p + 1; q < n; ++q) pr.push_back(std::make_pair(p, q));
        rng.shuffle(pr); return pr;
    }
    bool nb_pairs() {                                // N2
        bool any = false;
        std::vector<std::pair<int, int> > pr = all_pairs();
        for (size_t x = 0; x < pr.size(); ++x) { if (time_up()) break; if (try_swap(pr[x].first, pr[x].second)) any = true; }
        return any;
    }
    bool bubble(int p) {                             // slide one taxon through every other gap, one adjacent swap at a time
        for (int dir = 1; dir >= -1; dir -= 2) {
            tmp.ord = cur.ord; tmp.D = cur.D; tmp.wout = cur.wout;
            for (int pos = p; pos + dir >= 0 && pos + dir < n; pos += dir) {
                if (time_up()) return false;
                E.apply_swap(tmp, pos, pos + dir);
                i64 v = E.eval(tmp);
                if (accept(v)) { commit_tmp(v); return true; }
            }
        }
        return false;
    }
    bool nb_insert() {                               // N3
        bool any = false;
        std::vector<int> ps(n); for (int i = 0; i < n; ++i) ps[i] = i; rng.shuffle(ps);
        for (int x = 0; x < n; ++x) { if (time_up()) break; if (bubble(ps[x])) any = true; }
        return any;
    }
    bool nb_block(int L) {                           // N4: blocks of 2..L taxa to any other gap
        bool any = false;
        std::vector<std::vector<int> > mv;
        for (int len = 2; len <= L && len <= n - 2; ++len) for (int a = 0; a + len <= n; ++a) for (int gp = 0; gp <= n - len; ++gp)
            if (gp != a) { std::vector<int> m(3); m[0] = a; m[1] = len; m[2] = gp; mv.push_back(m); }
        rng.shuffle(mv);
        for (size_t x = 0; x < mv.size(); ++x) { if (time_up()) break; if (try_order(move_block(cur.ord, mv[x][0], mv[x][1], mv[x][2], false))) any = true; }
        return any;
    }
    bool nb_reverse() {                              // N5: reverse a segment (its complement gives the mirror image)
        bool any = false;
        std::vector<std::pair<int, int> > sg;
        for (int i = 0; i < n - 1; ++i) for (int j = i + 2; j <= n - 2; ++j) sg.push_back(std::make_pair(i, j));
        rng.shuffle(sg);
        for (size_t x = 0; x < sg.size(); ++x) {
            if (time_up()) break;
            std::vector<int> o = cur.ord; std::reverse(o.begin() + sg[x].first, o.begin() + sg[x].second + 1);
            if (try_order(o)) any = true;
        }
        return any;
    }
    bool nb_clade() {                                // N6: move a whole clade of the current tree (SPR-like)
        bool any = false, found = true;
        while (found && !time_up()) {
            found = false;
            std::vector<std::vector<int> > mv;
            for (size_t x = 1; x < curTree.nodes.size(); ++x) {
                int a = curTree.nodes[x].i - 1, len = curTree.nodes[x].j - curTree.nodes[x].i + 1;
                for (int gp = 0; gp <= n - len; ++gp) for (int rev = 0; rev < 2; ++rev)
                    if (gp != a || rev) { std::vector<int> m(4); m[0] = a; m[1] = len; m[2] = gp; m[3] = rev; mv.push_back(m); }
            }
            rng.shuffle(mv);
            for (size_t x = 0; x < mv.size() && !found; ++x) { if (time_up()) return any; if (try_order(move_block(cur.ord, mv[x][0], mv[x][1], mv[x][2], mv[x][3] != 0))) found = true; }
            any = any || found;
        }
        return any;
    }

    // ---- strategies ------------------------------------------------------------------------------------------
    void s_reorient() { temp = 0; nb_flip(); }                                   // DP + re-orientation only
    void s_pairswap_first() { temp = 0; while (!time_up() && nb_pairs()) {} }    // A1
    void s_pairswap_best() {                                                     // A2
        temp = 0;
        while (!time_up()) {
            i64 bv = curVal; int bp = -1, bq = -1;
            for (int p = 0; p < n && !time_up(); ++p) for (int q = p + 1; q < n; ++q) { i64 v = peek_swap(p, q); if (v > bv) { bv = v; bp = p; bq = q; } }
            if (bp < 0 || time_up()) break;
            force_swap(bp, bq);
        }
    }
    void s_vnd() {                                                               // A3: small moves first; restart after any gain
        temp = 0;
        while (!time_up()) {
            if (nb_flip()) continue;
            if (nb_adjacent()) continue;
            if (nb_pairs()) continue;
            if (nb_insert()) continue;
            if (nb_block(3)) continue;
            if (nb_reverse()) continue;
            if (nb_clade()) continue;
            break;
        }
    }
    void s_anneal() {                                                            // A4
        std::vector<double> neg;
        for (int r = 0; r < 60 && !time_up(); ++r) { int p = rng.below(n), q = rng.below(n); if (p == q) continue; i64 v = peek_swap(p, q); if (v < curVal) neg.push_back((double)(curVal - v)); }
        std::sort(neg.begin(), neg.end());
        double T0 = neg.empty() ? 1.0 : std::max(1.0, neg[neg.size() / 2] / std::log(2.0)), T1 = std::max(0.25, T0 * 1e-3);
        double saEnd = 0.9 * budget;                 // last 10% of the budget: greedy polish from the best order
        double pSwap = n > 60 ? 0.94 : 0.85, pEach = (1 - pSwap) / 3;
        while (!time_up() && elapsed() < saEnd) {
            temp = T0 * std::pow(T1 / T0, std::min(1.0, elapsed() / saEnd));
            double r = rng.unif();
            if (r < pSwap) {
                int p = rng.below(n), q = rng.unif() < 0.3 ? (p + 1) % n : rng.below(n);
                if (p != q) try_swap(p, q);
            } else if (r < pSwap + pEach) {
                int a = rng.below(n), gp = rng.below(n); if (gp != a) try_order(move_block(cur.ord, a, 1, gp, false));
            } else if (r < pSwap + 2 * pEach) {
                int i = rng.below(n - 1), j = i + 1 + rng.below(n - 1 - i);
                std::vector<int> o = cur.ord; std::reverse(o.begin() + i, o.begin() + j + 1); try_order(o);
            } else if (curTree.nodes.size() > 1) {
                const TreeBin::Node& nd = curTree.nodes[1 + rng.below((int)curTree.nodes.size() - 1)];
                int a = nd.i - 1, len = nd.j - nd.i + 1, gp = rng.below(n - len + 1);
                if (gp != a) try_order(move_block(cur.ord, a, len, gp, rng.below(2) == 1));
            }
        }
        temp = 0;
        if (!time_up()) { set_current(bestOrd); s_vnd(); }
    }
    void s_ils() {                                                               // A6
        s_vnd();
        while (!time_up()) {
            std::vector<int> keep = cur.ord; i64 keepVal = curVal;
            std::vector<int> o = double_bridge(cur.ord, rng);
            for (int r = 0; r < 2; ++r) std::swap(o[rng.below(n)], o[rng.below(n)]);
            set_current(o); s_vnd();
            if (curVal < keepVal && !time_up()) set_current(keep);
        }
    }
    void s_tabu() {                                                              // A7
        temp = 0;
        std::vector<i64> until((size_t)n * n, 0); i64 iter = 0;
        while (!time_up()) {
            ++iter;
            std::vector<std::pair<int, int> > pr = all_pairs();
            size_t cand = std::min(pr.size(), (size_t)std::max(60, 3 * n));
            i64 bv = 0; int bp = -1, bq = -1;
            for (size_t x = 0; x < cand && !time_up(); ++x) {
                int a = cur.ord[pr[x].first], b = cur.ord[pr[x].second];
                i64 v = peek_swap(pr[x].first, pr[x].second);
                if (until[(size_t)a * n + b] > iter && v <= bestVal) continue;      // tabu unless it beats the best ever
                if (bp < 0 || v > bv) { bv = v; bp = pr[x].first; bq = pr[x].second; }
            }
            if (bp < 0 || time_up()) continue;
            int a = cur.ord[bp], b = cur.ord[bq];
            force_swap(bp, bq);
            until[(size_t)a * n + b] = until[(size_t)b * n + a] = iter + n / 4 + 1 + rng.below(n / 4 + 1);
        }
    }
    void s_multistart() {                                                        // A8
        s_vnd();
        while (!time_up()) { set_current(newStart()); s_vnd(); }
    }
    bool run(const std::string& strategy) {
        if (strategy == "dp") {}
        else if (strategy == "reorient") s_reorient();
        else if (strategy == "pairswap-first") s_pairswap_first();
        else if (strategy == "pairswap-best") s_pairswap_best();
        else if (strategy == "vnd") s_vnd();
        else if (strategy == "anneal") s_anneal();
        else if (strategy == "ils") s_ils();
        else if (strategy == "tabu") s_tabu();
        else if (strategy == "multistart") s_multistart();
        else return false;
        return true;
    }
};
