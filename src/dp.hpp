// dp.hpp - exact O(M + n^3) dynamic program for a fixed circular order, with O(n^3) incremental swaps.
//
// Positions are 0..n-1; labels are position+1. The taxon at the last position hangs at the root and the
// DP runs over label intervals [i..j] within 1..n-1. For positions p1<p2<p3<p4 with taxa t1..t4:
//   "outer"  topology t1t2|t3t4 is assumed displayed (its weight goes into wout),
//   "middle" topology t1t4|t2t3 replaces it when the node that separates t2 from t3 excludes t1 and t4.
// So each 4-set adds v = w_middle - w_outer to Delta(i,k,j) on the box
//   i in [p1+2, p2+1],  k in [p2+1, p3],  j in [p3+1, p4]        (labels)
// and  score(order) = wout + max over binary interval trees of the sum of Delta(i,k,j) at its nodes.
// D stores the 8-corner difference form of Delta in layout [i][j][k]; a 3-D prefix sum recovers Delta.
#pragma once
#include "table.hpp"

struct State {
    std::vector<int> ord;     // position -> taxon id
    std::vector<i64> D;       // difference array
    i64 wout = 0;
};

struct TreeBin {              // optimal tree for an order: internal nodes as label intervals [i..j] cut after k
    struct Node { int i, k, j; };
    std::vector<int> ord;
    std::vector<Node> nodes;  // nodes[0] is the top interval [1..n-1]
};

struct Engine {
    const QTable& T;
    int n, S;
    size_t S3;
    std::vector<i64> P, f, g;
    std::vector<int> cut;
    i64 nRebuild = 0, nSwap = 0, nEval = 0;

    explicit Engine(const QTable& t) : T(t), n(t.n), S(t.n + 2), S3((size_t)(t.n + 2) * (t.n + 2) * (t.n + 2)) {
        P.assign(S3, 0); f.assign((size_t)S * S, 0); g.assign((size_t)S * S, 0); cut.assign((size_t)S * S, 0);
    }

    inline void add_set(i64* A, const int* ord, int p1, int p2, int p3, int p4, i64 sign, i64& wout) const {
        uint32_t wo, wx, wm;
        T.pairings(ord[p1], ord[p2], ord[p3], ord[p4], wo, wx, wm);     // outer, crossing, middle
        (void)wx;
        wout += sign * (i64)wo;
        i64 v = sign * ((i64)wm - (i64)wo);
        if (!v) return;
        size_t i0 = p1 + 2, i1 = p2 + 2, k0 = p2 + 1, k1 = p3 + 1, j0 = p3 + 1, j1 = p4 + 1;
        i64* r00 = A + (i0 * S + j0) * S; i64* r01 = A + (i0 * S + j1) * S;
        i64* r10 = A + (i1 * S + j0) * S; i64* r11 = A + (i1 * S + j1) * S;
        r00[k0] += v; r00[k1] -= v; r01[k0] -= v; r01[k1] += v;
        r10[k0] -= v; r10[k1] += v; r11[k0] += v; r11[k1] -= v;
    }

    void rebuild(State& s) {                       // O(n^4): every 4-set once
        s.D.assign(S3, 0); s.wout = 0;
        i64* A = s.D.data(); const int* o = s.ord.data();
        for (int p1 = 0; p1 < n; ++p1) for (int p2 = p1 + 1; p2 < n; ++p2)
            for (int p3 = p2 + 1; p3 < n; ++p3) for (int p4 = p3 + 1; p4 < n; ++p4)
                add_set(A, o, p1, p2, p3, p4, 1, s.wout);
        ++nRebuild;
    }

    // Swap the taxa at positions p and q in place. Only 4-sets containing p or q change: O(n^3).
    void apply_swap(State& s, int p, int q) {
        if (p == q) return;
        std::vector<int> o2 = s.ord; std::swap(o2[p], o2[q]);
        i64* A = s.D.data(); const int* o1 = s.ord.data(); const int* on = o2.data();
        for (int pass = 0; pass < 2; ++pass) {
            int r = pass == 0 ? p : q;             // pass 0: sets containing p; pass 1: sets with q but not p
            for (int x = 0; x < n; ++x) {
                if (x == p || (pass == 1 && x == q) || x == r) continue;
                for (int y = x + 1; y < n; ++y) {
                    if (y == p || (pass == 1 && y == q) || y == r) continue;
                    for (int z = y + 1; z < n; ++z) {
                        if (z == p || (pass == 1 && z == q) || z == r) continue;
                        int a, b, c, d;
                        if (r < x) { a = r; b = x; c = y; d = z; }
                        else if (r < y) { a = x; b = r; c = y; d = z; }
                        else if (r < z) { a = x; b = y; c = r; d = z; }
                        else { a = x; b = y; c = z; d = r; }
                        add_set(A, o1, a, b, c, d, -1, s.wout);
                        add_set(A, on, a, b, c, d, +1, s.wout);
                    }
                }
            }
        }
        s.ord.swap(o2);
        ++nSwap;
    }

    // Best tree score for the state's order. Leaves `cut` valid for extract().
    i64 eval(const State& s) {
        std::memcpy(P.data(), s.D.data(), S3 * sizeof(i64));
        i64* A = P.data();
        size_t SS = (size_t)S * S;
        for (size_t r = 0; r < SS; ++r) { i64* row = A + r * S; for (int k = 1; k < S; ++k) row[k] += row[k - 1]; }
        for (int i = 0; i < S; ++i) for (int j = 1; j < S; ++j) {
            i64* row = A + ((size_t)i * S + j) * S; const i64* prev = row - S;
            for (int k = 0; k < S; ++k) row[k] += prev[k];
        }
        for (int i = 1; i < S; ++i) { i64* sl = A + (size_t)i * SS; const i64* prev = sl - SS; for (size_t x = 0; x < SS; ++x) sl[x] += prev[x]; }
        for (int i = 1; i <= n - 1; ++i) { f[(size_t)i * S + i] = 0; g[(size_t)i * S + i] = 0; }
        for (int len = 2; len <= n - 1; ++len)
            for (int i = 1; i + len - 1 <= n - 1; ++i) {
                int j = i + len - 1;
                const i64* fi = &f[(size_t)i * S]; const i64* gj = &g[(size_t)j * S]; const i64* pr = A + ((size_t)i * S + j) * S;
                i64 best = fi[i] + gj[i + 1] + pr[i]; int bk = i;
                for (int k = i + 1; k < j; ++k) { i64 v = fi[k] + gj[k + 1] + pr[k]; if (v > best) { best = v; bk = k; } }
                f[(size_t)i * S + j] = best; g[(size_t)j * S + i] = best; cut[(size_t)i * S + j] = bk;
            }
        ++nEval;
        return s.wout + f[(size_t)1 * S + (n - 1)];
    }

    void extract(const State& s, TreeBin& t) const {     // call right after eval(s)
        t.ord = s.ord; t.nodes.clear();
        std::vector<std::pair<int, int> > st; st.push_back(std::make_pair(1, n - 1));
        while (!st.empty()) {
            int i = st.back().first, j = st.back().second; st.pop_back();
            if (i == j) continue;
            int k = cut[(size_t)i * S + j];
            TreeBin::Node nd; nd.i = i; nd.k = k; nd.j = j; t.nodes.push_back(nd);
            st.push_back(std::make_pair(k + 1, j)); st.push_back(std::make_pair(i, k));
        }
    }
};

// ---- tree helpers --------------------------------------------------------------------------------------
inline std::string treebin_newick(const TreeBin& t, const std::vector<std::string>& names) {
    int n = (int)t.ord.size(), S = n + 2;
    std::vector<int> cut((size_t)S * S, -1);
    for (size_t x = 0; x < t.nodes.size(); ++x) cut[(size_t)t.nodes[x].i * S + t.nodes[x].j] = t.nodes[x].k;
    struct R { static void go(const TreeBin& t, const std::vector<std::string>& nm, const std::vector<int>& cut, int S, int i, int j, std::string& out) {
        if (i == j) { out += nm[t.ord[i - 1]]; return; }
        int k = cut[(size_t)i * S + j];
        out += "("; go(t, nm, cut, S, i, k, out); out += ","; go(t, nm, cut, S, k + 1, j, out); out += ")";
    } };
    int k = cut[(size_t)1 * S + (n - 1)];
    std::string out = "(";
    R::go(t, names, cut, S, 1, k, out); out += ","; R::go(t, names, cut, S, k + 1, n - 1, out);
    out += "," + names[t.ord[n - 1]] + ");";
    return out;
}

// A circular order compatible with the tree: every internal node may list its two children either way.
// flipNode < 0: flip each node at random; otherwise flip exactly that node.
inline std::vector<int> treebin_order(const TreeBin& t, int flipNode, Rng* rng) {
    int n = (int)t.ord.size(), S = n + 2;
    std::vector<int> cut((size_t)S * S, -1), id((size_t)S * S, -1);
    for (size_t x = 0; x < t.nodes.size(); ++x) { cut[(size_t)t.nodes[x].i * S + t.nodes[x].j] = t.nodes[x].k; id[(size_t)t.nodes[x].i * S + t.nodes[x].j] = (int)x; }
    std::vector<int> out; out.reserve(n);
    std::vector<std::pair<int, int> > st; st.push_back(std::make_pair(1, n - 1));
    while (!st.empty()) {
        int i = st.back().first, j = st.back().second; st.pop_back();
        if (i == j) { out.push_back(t.ord[i - 1]); continue; }
        int k = cut[(size_t)i * S + j];
        bool flip = flipNode >= 0 ? (id[(size_t)i * S + j] == flipNode) : (rng->below(2) == 1);
        if (flip) { st.push_back(std::make_pair(i, k)); st.push_back(std::make_pair(k + 1, j)); }      // right child first
        else { st.push_back(std::make_pair(k + 1, j)); st.push_back(std::make_pair(i, k)); }
    }
    out.push_back(t.ord[n - 1]);
    return out;
}

// Random compatible order of an arbitrary (possibly non-binary) tree on all taxa.
inline std::vector<int> ntree_order(const NTree& t, Rng& rng) {
    std::vector<int> out, st; st.push_back(t.root);
    while (!st.empty()) {
        int v = st.back(); st.pop_back();
        if (t.is_leaf(v)) { out.push_back(t.taxon[v]); continue; }
        std::vector<int> c = t.ch[v]; rng.shuffle(c);
        for (size_t x = 0; x < c.size(); ++x) st.push_back(c[x]);
    }
    return out;
}
