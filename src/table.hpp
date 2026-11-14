// table.hpp - quartet weight table.
// W[4-set][topology] = number of gene trees that display that quartet topology.
// For taxa a<b<c<d (by id): topology 0 = ab|cd, 1 = ac|bd, 2 = ad|bc.
#pragma once
#include "newick.hpp"

struct QTable {
    int n = 0;
    i64 ntrees = 0, total = 0;
    std::vector<std::string> names;
    std::vector<uint32_t> w;                 // 3 * C(n,4) counts
    std::vector<i64> c2, c3, c4;             // binomials C(x,2), C(x,3), C(x,4)

    void init(int n_, const std::vector<std::string>& names_) {
        n = n_; names = names_;
        c2.assign(n + 1, 0); c3.assign(n + 1, 0); c4.assign(n + 1, 0);
        for (i64 x = 0; x <= n; ++x) { c2[x] = x * (x - 1) / 2; c3[x] = x * (x - 1) * (x - 2) / 6; c4[x] = x * (x - 1) * (x - 2) * (x - 3) / 24; }
        w.assign((size_t)(3 * c4[n]), 0);
    }
    inline size_t idx(int a, int b, int c, int d) const { return (size_t)(c4[d] + c3[c] + c2[b] + a); }   // needs a<b<c<d

    // Weights of the three pairings of t1 with each other taxon:
    //   w12 = t1t2|t3t4, w13 = t1t3|t2t4, w14 = t1t4|t2t3      (taxa in any order)
    inline void pairings(int t1, int t2, int t3, int t4, uint32_t& w12, uint32_t& w13, uint32_t& w14) const {
        int s0 = t1, s1 = t2, s2 = t3, s3 = t4;
        if (s0 > s1) std::swap(s0, s1);
        if (s2 > s3) std::swap(s2, s3);
        if (s0 > s2) std::swap(s0, s2);
        if (s1 > s3) std::swap(s1, s3);
        if (s1 > s2) std::swap(s1, s2);
        const uint32_t* p = &w[3 * idx(s0, s1, s2, s3)];
        // topology index of the pairing {x,y}|rest = rank of s0's partner - 1
        int p12 = (s0 == t1) ? t2 : (s0 == t2) ? t1 : (s0 == t3) ? t4 : t3;
        int p13 = (s0 == t1) ? t3 : (s0 == t3) ? t1 : (s0 == t2) ? t4 : t2;
        int p14 = (s0 == t1) ? t4 : (s0 == t4) ? t1 : (s0 == t2) ? t3 : t2;
        w12 = p[(p12 == s1) ? 0 : (p12 == s2) ? 1 : 2];
        w13 = p[(p13 == s1) ? 0 : (p13 == s2) ? 1 : 2];
        w14 = p[(p14 == s1) ? 0 : (p14 == s2) ? 1 : 2];
    }

    void add_tree(const NTree& t) {
        std::vector<int> L = t.leaves();
        std::sort(L.begin(), L.end(), [&](int x, int y) { return t.taxon[x] < t.taxon[y]; });
        int m = (int)L.size();
        if (m < 4) return;
        std::vector<uint16_t> D = leaf_distances(t, L);
        std::vector<int> g(m);
        for (int a = 0; a < m; ++a) g[a] = t.taxon[L[a]];
        const uint16_t* Dp = D.data();
        // different d -> disjoint index ranges, so the loop over d is safe to run in parallel
        #pragma omp parallel for schedule(dynamic, 1)
        for (int d = 3; d < m; ++d)
            for (int c = 2; c < d; ++c)
                for (int b = 1; b < c; ++b) {
                    size_t base = (size_t)(c4[g[d]] + c3[g[c]] + c2[g[b]]);
                    for (int a = 0; a < b; ++a) {
                        int tp = quartet_topology(Dp, m, a, b, c, d);
                        if (tp >= 0) ++w[3 * (base + g[a]) + tp];
                    }
                }
        ++ntrees;
    }
    void finish() { total = 0; for (size_t i = 0; i < w.size(); ++i) total += w[i]; }

    void build(const GeneSet& G) {
        init(G.n(), G.names);
        for (size_t i = 0; i < G.trees.size(); ++i) add_tree(G.trees[i]);
        finish();
    }

    void save(const std::string& path) const {
        std::string tmp = path + ".tmp" + std::to_string((long long)std::rand());
        FILE* f = std::fopen(tmp.c_str(), "wb");
        if (!f) die("cannot write " + tmp);
        std::fwrite("MQCT1\n", 1, 6, f);
        i64 hdr[3] = { n, ntrees, total };
        std::fwrite(hdr, sizeof(i64), 3, f);
        for (int i = 0; i < n; ++i) { i64 len = (i64)names[i].size(); std::fwrite(&len, sizeof(i64), 1, f); std::fwrite(names[i].data(), 1, (size_t)len, f); }
        std::fwrite(w.data(), sizeof(uint32_t), w.size(), f);
        std::fclose(f);
        std::rename(tmp.c_str(), path.c_str());      // atomic: parallel jobs never see a half-written table
    }
    bool load(const std::string& path, const std::vector<std::string>& expectNames) {
        FILE* f = std::fopen(path.c_str(), "rb");
        if (!f) return false;
        char magic[6]; i64 hdr[3];
        bool ok = std::fread(magic, 1, 6, f) == 6 && std::memcmp(magic, "MQCT1\n", 6) == 0 && std::fread(hdr, sizeof(i64), 3, f) == 3;
        std::vector<std::string> nm;
        if (ok) for (int i = 0; i < hdr[0] && ok; ++i) {
            i64 len; ok = std::fread(&len, sizeof(i64), 1, f) == 1 && len >= 0 && len < 100000;
            if (ok) { std::string s((size_t)len, ' '); ok = std::fread(&s[0], 1, (size_t)len, f) == (size_t)len; nm.push_back(s); }
        }
        if (ok && nm != expectNames) { std::fclose(f); die("table " + path + " was built from different taxa; delete it and rebuild"); }
        if (ok) { init((int)hdr[0], nm); ntrees = hdr[1]; total = hdr[2]; ok = std::fread(w.data(), sizeof(uint32_t), w.size(), f) == w.size(); }
        std::fclose(f);
        return ok;
    }
};

// Quartet score of any tree on all n taxa: number of gene-tree quartets it displays. Independent of the DP.
inline i64 score_tree(const QTable& T, const NTree& t) {
    std::vector<int> L = t.leaves();
    std::sort(L.begin(), L.end(), [&](int x, int y) { return t.taxon[x] < t.taxon[y]; });
    int n = T.n;
    if ((int)L.size() != n) die("score_tree: tree must contain every taxon");
    std::vector<uint16_t> D = leaf_distances(t, L);
    i64 s = 0;
    #pragma omp parallel for schedule(dynamic, 1) reduction(+ : s)
    for (int d = 3; d < n; ++d)
        for (int c = 2; c < d; ++c)
            for (int b = 1; b < c; ++b)
                for (int a = 0; a < b; ++a) {
                    int tp = quartet_topology(D.data(), n, a, b, c, d);
                    if (tp >= 0) s += T.w[3 * T.idx(a, b, c, d) + tp];
                }
    return s;
}
