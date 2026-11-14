// newick.hpp - minimal Newick reader. Keeps topology and leaf labels only.
// Handles polytomies, branch lengths, internal labels / support values, [comments], 'quoted labels'.
#pragma once
#include "util.hpp"
#include <fstream>
#include <map>
#include <sstream>

struct NTree {
    std::vector<int> parent;
    std::vector<std::vector<int> > ch;
    std::vector<std::string> label;   // leaf label ("" for internal nodes)
    std::vector<int> taxon;           // taxon id for leaves, -1 otherwise (filled by map_taxa)
    int root = 0;
    int add(int par) {
        parent.push_back(par); ch.push_back(std::vector<int>()); label.push_back(""); taxon.push_back(-1);
        int id = (int)parent.size() - 1;
        if (par >= 0) ch[par].push_back(id);
        return id;
    }
    bool is_leaf(int v) const { return ch[v].empty(); }
    std::vector<int> leaves() const {
        std::vector<int> L;
        for (int v = 0; v < (int)parent.size(); ++v) if (is_leaf(v)) L.push_back(v);
        return L;
    }
};

inline bool parse_newick(const std::string& s, NTree& t) {
    t = NTree();
    int cur = t.add(-1);
    size_t i = 0, n = s.size();
    bool any = false;
    while (i < n) {
        char c = s[i];
        if (c == '(') { cur = t.add(cur); ++i; any = true; }
        else if (c == ',') { if (t.parent[cur] < 0) return false; cur = t.add(t.parent[cur]); ++i; }
        else if (c == ')') { if (t.parent[cur] < 0) return false; cur = t.parent[cur]; ++i; }
        else if (c == ';') break;
        else if (c == '[') { while (i < n && s[i] != ']') ++i; ++i; }
        else if (c == ':') { ++i; while (i < n && !std::strchr(",();[", s[i])) ++i; }
        else if (c == '\'') {
            size_t j = s.find('\'', i + 1);
            if (j == std::string::npos) return false;
            if (t.is_leaf(cur)) t.label[cur] = s.substr(i + 1, j - i - 1);
            i = j + 1; any = true;
        }
        else if (std::isspace((unsigned char)c)) ++i;
        else {
            size_t j = i;
            while (j < n && !std::strchr(",():;[", s[j]) && !std::isspace((unsigned char)s[j])) ++j;
            if (t.is_leaf(cur)) t.label[cur] = s.substr(i, j - i);   // internal labels are ignored
            i = j; any = true;
        }
    }
    if (!any) return false;
    // a node that got a label but later received children keeps no label
    for (int v = 0; v < (int)t.parent.size(); ++v) if (!t.is_leaf(v)) t.label[v].clear();
    for (int v = 0; v < (int)t.parent.size(); ++v) if (t.is_leaf(v) && t.label[v].empty()) return false;
    return true;
}

inline std::vector<std::string> read_newick_strings(const std::string& path) {
    std::ifstream in(path.c_str());
    if (!in) die("cannot open " + path);
    std::stringstream ss; ss << in.rdbuf();
    std::string all = ss.str(), cur;
    std::vector<std::string> out;
    for (size_t i = 0; i < all.size(); ++i) {
        cur.push_back(all[i]);
        if (all[i] == ';') {
            bool blank = true;
            for (size_t j = 0; j + 1 < cur.size(); ++j) if (!std::isspace((unsigned char)cur[j])) blank = false;
            if (!blank) out.push_back(cur);
            cur.clear();
        }
    }
    return out;
}

// Leaf-to-leaf distances in edge counts. Rows/cols follow the order of `leafNodes`.
// Any positive edge lengths satisfy the four-point condition, so unit lengths give quartet topologies.
inline std::vector<uint16_t> leaf_distances(const NTree& t, const std::vector<int>& leafNodes) {
    int N = (int)t.parent.size(), m = (int)leafNodes.size();
    std::vector<std::vector<int> > adj(N);
    for (int v = 0; v < N; ++v) if (t.parent[v] >= 0) { adj[v].push_back(t.parent[v]); adj[t.parent[v]].push_back(v); }
    std::vector<int> col(N, -1);
    for (int a = 0; a < m; ++a) col[leafNodes[a]] = a;
    std::vector<uint16_t> D((size_t)m * m, 0);
    std::vector<int> dist(N), q(N);
    for (int a = 0; a < m; ++a) {
        std::fill(dist.begin(), dist.end(), -1);
        int h = 0, e = 0; q[e++] = leafNodes[a]; dist[leafNodes[a]] = 0;
        while (h < e) {
            int v = q[h++];
            if (col[v] >= 0) D[(size_t)a * m + col[v]] = (uint16_t)dist[v];
            for (size_t x = 0; x < adj[v].size(); ++x) { int u = adj[v][x]; if (dist[u] < 0) { dist[u] = dist[v] + 1; q[e++] = u; } }
        }
    }
    return D;
}

// 0: ab|cd, 1: ac|bd, 2: ad|bc, -1: unresolved (polytomy)
inline int quartet_topology(const uint16_t* D, int m, int a, int b, int c, int d) {
    int s1 = D[(size_t)a * m + b] + D[(size_t)c * m + d];
    int s2 = D[(size_t)a * m + c] + D[(size_t)b * m + d];
    int s3 = D[(size_t)a * m + d] + D[(size_t)b * m + c];
    if (s1 < s2 && s1 < s3) return 0;
    if (s2 < s1 && s2 < s3) return 1;
    if (s3 < s1 && s3 < s2) return 2;
    return -1;
}

// Gene trees + global taxon naming (ids = rank of the name in sorted order).
struct GeneSet {
    std::vector<std::string> names;
    std::map<std::string, int> id;
    std::vector<NTree> trees;
    int skipped = 0;
    int n() const { return (int)names.size(); }
};

inline bool map_taxa(NTree& t, const std::map<std::string, int>& id, bool& dup) {
    std::vector<char> seen(id.size(), 0);
    dup = false;
    for (int v = 0; v < (int)t.parent.size(); ++v) if (t.is_leaf(v)) {
        std::map<std::string, int>::const_iterator it = id.find(t.label[v]);
        if (it == id.end()) return false;
        if (seen[it->second]) dup = true;
        seen[it->second] = 1; t.taxon[v] = it->second;
    }
    return true;
}

inline GeneSet load_genes(const std::string& path) {
    GeneSet G;
    std::vector<std::string> strs = read_newick_strings(path);
    std::vector<NTree> raw;
    for (size_t i = 0; i < strs.size(); ++i) {
        NTree t;
        if (!parse_newick(strs[i], t)) { ++G.skipped; continue; }
        raw.push_back(t);
    }
    for (size_t i = 0; i < raw.size(); ++i)
        for (int v = 0; v < (int)raw[i].parent.size(); ++v) if (raw[i].is_leaf(v)) G.id[raw[i].label[v]] = 0;
    int k = 0;
    for (std::map<std::string, int>::iterator it = G.id.begin(); it != G.id.end(); ++it) { it->second = k++; G.names.push_back(it->first); }
    for (size_t i = 0; i < raw.size(); ++i) {
        bool dup = false;
        map_taxa(raw[i], G.id, dup);
        if (dup) { ++G.skipped; continue; }   // multi-copy gene trees are not supported
        G.trees.push_back(raw[i]);
    }
    if (G.n() < 4) die("fewer than 4 taxa in " + path);
    return G;
}

// Species-tree style reader: one tree containing every taxon exactly once.
inline bool load_full_tree(const std::string& newick, const GeneSet& G, NTree& t, std::string& err) {
    if (!parse_newick(newick, t)) { err = "cannot parse tree"; return false; }
    bool dup = false;
    if (!map_taxa(t, G.id, dup)) { err = "tree has a taxon that is not in the gene trees"; return false; }
    if (dup) { err = "tree has a repeated taxon"; return false; }
    if ((int)t.leaves().size() != G.n()) { err = "tree does not contain every taxon"; return false; }
    return true;
}
