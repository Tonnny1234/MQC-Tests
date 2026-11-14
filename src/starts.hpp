// starts.hpp - starting circular orders (S1-S10 in the plan) and order-editing moves.
#pragma once
#include "dp.hpp"

// ---- order edits ---------------------------------------------------------------------------------------
// Remove the block [a, a+len) and re-insert it before index `gap` of the remaining sequence.
inline std::vector<int> move_block(const std::vector<int>& o, int a, int len, int gap, bool reversed) {
    std::vector<int> blk(o.begin() + a, o.begin() + a + len), rest;
    rest.reserve(o.size());
    rest.insert(rest.end(), o.begin(), o.begin() + a);
    rest.insert(rest.end(), o.begin() + a + len, o.end());
    if (reversed) std::reverse(blk.begin(), blk.end());
    rest.insert(rest.begin() + gap, blk.begin(), blk.end());
    return rest;
}
inline std::vector<int> double_bridge(const std::vector<int>& o, Rng& rng) {      // A B C D -> A C B D
    int n = (int)o.size();
    if (n < 8) { std::vector<int> r = o; std::swap(r[rng.below(n)], r[rng.below(n)]); return r; }
    int c[3]; do { for (int i = 0; i < 3; ++i) c[i] = 1 + rng.below(n - 1); std::sort(c, c + 3); } while (c[0] == c[1] || c[1] == c[2]);
    std::vector<int> r;
    r.insert(r.end(), o.begin(), o.begin() + c[0]);
    r.insert(r.end(), o.begin() + c[1], o.begin() + c[2]);
    r.insert(r.end(), o.begin() + c[0], o.begin() + c[1]);
    r.insert(r.end(), o.begin() + c[2], o.end());
    return r;
}

// ---- cold starts ---------------------------------------------------------------------------------------
inline std::vector<int> start_random(int n, Rng& rng) {
    std::vector<int> o(n); for (int i = 0; i < n; ++i) o[i] = i; rng.shuffle(o); return o;
}

// S4: leaf order of a random gene tree among those with the most taxa; missing taxa go to random places.
inline std::vector<int> start_genetree(const GeneSet& G, Rng& rng) {
    size_t best = 0; std::vector<int> cand;
    for (size_t i = 0; i < G.trees.size(); ++i) {
        size_t m = G.trees[i].leaves().size();
        if (m > best) { best = m; cand.clear(); }
        if (m == best) cand.push_back((int)i);
    }
    if (cand.empty()) return start_random(G.n(), rng);
    std::vector<int> o = ntree_order(G.trees[cand[rng.below((int)cand.size())]], rng);
    std::vector<char> have(G.n(), 0);
    for (size_t i = 0; i < o.size(); ++i) have[o[i]] = 1;
    for (int t = 0; t < G.n(); ++t) if (!have[t]) o.insert(o.begin() + rng.below((int)o.size() + 1), t);
    return o;
}

// S5: average internode distance over gene trees, then a short cyclic tour (nearest neighbour + 2-opt).
inline std::vector<int> start_distance(const GeneSet& G, Rng& rng) {
    int n = G.n();
    std::vector<double> sum((size_t)n * n, 0), cnt((size_t)n * n, 0);
    for (size_t ti = 0; ti < G.trees.size(); ++ti) {
        const NTree& t = G.trees[ti];
        std::vector<int> L = t.leaves(); int m = (int)L.size();
        std::vector<uint16_t> D = leaf_distances(t, L);
        for (int a = 0; a < m; ++a) for (int b = 0; b < m; ++b) if (a != b) {
            size_t x = (size_t)t.taxon[L[a]] * n + t.taxon[L[b]];
            sum[x] += D[(size_t)a * m + b]; cnt[x] += 1;
        }
    }
    double mx = 0;
    for (size_t x = 0; x < sum.size(); ++x) if (cnt[x] > 0) { sum[x] /= cnt[x]; mx = std::max(mx, sum[x]); }
    for (size_t x = 0; x < sum.size(); ++x) if (cnt[x] == 0) sum[x] = 2 * mx;
    std::vector<int> o; std::vector<char> used(n, 0);
    int cur = rng.below(n); o.push_back(cur); used[cur] = 1;
    for (int s = 1; s < n; ++s) {
        int nb = -1;
        for (int v = 0; v < n; ++v) if (!used[v] && (nb < 0 || sum[(size_t)cur * n + v] < sum[(size_t)cur * n + nb])) nb = v;
        o.push_back(nb); used[nb] = 1; cur = nb;
    }
    bool imp = true; int guard = 0;
    while (imp && guard++ < 200) {
        imp = false;
        for (int i = 0; i < n - 1; ++i) for (int j = i + 2; j < n; ++j) {
            if (i == 0 && j == n - 1) continue;
            int a = o[i], b = o[i + 1], c = o[j], d = o[(j + 1) % n];
            if (sum[(size_t)a * n + c] + sum[(size_t)b * n + d] + 1e-12 < sum[(size_t)a * n + b] + sum[(size_t)c * n + d]) {
                std::reverse(o.begin() + i + 1, o.begin() + j + 1); imp = true;
            }
        }
    }
    return o;
}

// S7: deterministic caterpillar with score >= total/3 (method of conditional expectations).
// g[x] = 3 * (change in expected score if x is placed next). The g of unplaced taxa always sum to 0,
// so the maximum is >= 0 and placing it never lowers the conditional expectation.
inline std::vector<int> start_caterpillar(const QTable& T, Rng& rng) {
    int n = T.n;
    std::vector<i64> g(n, 0); std::vector<char> placed(n, 0); std::vector<int> seq;
    for (int step = 0; step < n; ++step) {
        int x = -1; std::vector<int> ties;
        for (int v = 0; v < n; ++v) if (!placed[v]) {
            if (x < 0 || g[v] > g[x]) { x = v; ties.clear(); }
            if (g[v] == g[x]) ties.push_back(v);
        }
        x = ties[rng.below((int)ties.size())];
        for (int a = 0; a < n; ++a) { if (a == x) continue;
            for (int b = a + 1; b < n; ++b) { if (b == x) continue;
                for (int c = b + 1; c < n; ++c) { if (c == x) continue;
                    int cntp = placed[a] + placed[b] + placed[c];
                    if (cntp > 1) continue;
                    uint32_t wa, wb, wc;
                    if (cntp == 0) {                       // x is the first placed: its partner gains 2w, others lose w
                        T.pairings(x, a, b, c, wa, wb, wc);
                        g[a] += 2 * (i64)wa - wb - wc; g[b] += 2 * (i64)wb - wa - wc; g[c] += 2 * (i64)wc - wa - wb;
                    } else {                               // a second taxon arrives: undo what the first one added
                        int z = placed[a] ? a : placed[b] ? b : c;
                        int u = (z == a) ? b : a, v = (z == c) ? b : c;        // the two unplaced ones besides x
                        uint32_t wx, wu, wv;
                        T.pairings(z, x, u, v, wx, wu, wv);
                        g[u] -= 2 * (i64)wu - wx - wv; g[v] -= 2 * (i64)wv - wx - wu;
                    }
                } } }
        placed[x] = 1; seq.push_back(x);
    }
    return seq;
}

// S8: greedy insertion. Taxa are added one at a time into the gap that keeps the most quartet weight uncrossed.
inline std::vector<int> start_greedy(const QTable& T, Rng& rng) {
    int n = T.n;
    std::vector<int> todo = start_random(n, rng), seq(todo.begin(), todo.begin() + 3);
    for (int s = 3; s < n; ++s) {
        int t = todo[s], m = (int)seq.size();
        std::vector<i64> diff(m + 1, 0);                  // gap g = just before seq[g]; gap 0 also means "after the last"
        for (int x = 0; x < m; ++x) for (int y = x + 1; y < m; ++y) for (int z = y + 1; z < m; ++z) {
            uint32_t wa, wb, wc;
            T.pairings(t, seq[x], seq[y], seq[z], wa, wb, wc);         // t paired with x / y / z
            i64 gxy = (i64)wa + wb, gyz = (i64)wb + wc, gzx = (i64)wc + wa;   // t placed between x,y / y,z / z,x
            diff[x + 1] += gxy; diff[y + 1] -= gxy;
            diff[y + 1] += gyz; diff[z + 1] -= gyz;
            diff[z + 1] += gzx; diff[0] += gzx; diff[x + 1] -= gzx;
        }
        i64 run = 0, best = -1; std::vector<int> ties;
        for (int gp = 0; gp < m; ++gp) { run += diff[gp]; if (run > best) { best = run; ties.clear(); } if (run == best) ties.push_back(gp); }
        seq.insert(seq.begin() + ties[rng.below((int)ties.size())], t);
    }
    return seq;
}
