"""Independent Python reference for the tests. Shares no code or method with the C++ engine:
quartets are read off bipartitions (the engine uses distances) and optima come from enumerating every tree."""
import itertools
import random


# ---- random gene trees written in deliberately messy Newick ------------------------------------------------
def random_binary(leaves, rng):
    items = list(leaves)
    rng.shuffle(items)
    while len(items) > 1:
        a = items.pop(rng.randrange(len(items)))
        b = items.pop(rng.randrange(len(items)))
        items.append([a, b])
    return items[0]


def contract(t, rng, p):
    """Randomly merge internal nodes into their parent to create polytomies."""
    if not isinstance(t, list):
        return t
    kids = []
    for c in t:
        c = contract(c, rng, p)
        if isinstance(c, list) and rng.random() < p:
            kids.extend(c)
        else:
            kids.append(c)
    return kids


def to_newick(t, rng, messy=True):
    def rec(x):
        if not isinstance(x, list):
            s = x
        else:
            s = "(" + ",".join(rec(c) for c in x) + ")"
            if messy and rng.random() < 0.5:
                s += "%.2f" % rng.random()                 # support value as internal label
        if messy and rng.random() < 0.7:
            s += ":%.4f" % (rng.random() * 2)              # branch length
        return s
    body = "(" + ",".join(rec(c) for c in t) + ")" if isinstance(t, list) else t
    return ("[&U] " if messy and rng.random() < 0.2 else "") + body + ";"


def make_gene_trees(taxa, k, rng, p_missing=0.15, p_contract=0.2):
    lines = []
    for _ in range(k):
        keep = [x for x in taxa if rng.random() > p_missing]
        if len(keep) < 4:
            keep = list(taxa)
        lines.append(to_newick(contract(random_binary(keep, rng), rng, p_contract), rng))
    lines[0] = to_newick(random_binary(list(taxa), rng), rng)   # at least one complete tree
    return lines


# ---- reference quartet weights -----------------------------------------------------------------------------
def parse(s):
    """Tiny recursive Newick parser -> nested lists of labels."""
    s = s.strip().rstrip(";")
    if s.startswith("["):
        s = s[s.index("]") + 1:].strip()
    pos = [0]

    def node():
        if s[pos[0]] == "(":
            pos[0] += 1
            kids = [node()]
            while s[pos[0]] == ",":
                pos[0] += 1
                kids.append(node())
            pos[0] += 1                                    # ')'
            skip()
            return kids
        start = pos[0]
        while pos[0] < len(s) and s[pos[0]] not in ",():":
            pos[0] += 1
        lab = s[start:pos[0]]
        skip()
        return lab

    def skip():                                            # internal label and branch length
        while pos[0] < len(s) and s[pos[0]] not in ",()":
            pos[0] += 1
    return node()


def clusters(t):
    """Leaf sets below every internal node, plus the full leaf set."""
    out = []

    def rec(x):
        if not isinstance(x, list):
            return frozenset([x])
        c = frozenset().union(*[rec(k) for k in x])
        out.append(c)
        return c
    allv = rec(t)
    return out, allv


def displayed(cl, q):
    """Topology index of the 4-set q=(a,b,c,d) in a tree with clusters cl, or None if unresolved."""
    a, b, c, d = q
    pairs = [((a, b), (c, d)), ((a, c), (b, d)), ((a, d), (b, c))]
    for i, (x, y) in enumerate(pairs):
        for C in cl:
            inx = (x[0] in C) + (x[1] in C)
            iny = (y[0] in C) + (y[1] in C)
            if (inx == 2 and iny == 0) or (inx == 0 and iny == 2):
                return i
    return None


def weights(newicks, taxa):
    """W[(a,b,c,d)][topology] for sorted taxa a<b<c<d."""
    W = {q: [0, 0, 0] for q in itertools.combinations(sorted(taxa), 4)}
    for s in newicks:
        cl, allv = clusters(parse(s))
        for q in itertools.combinations(sorted(allv), 4):
            t = displayed(cl, q)
            if t is not None:
                W[q][t] += 1
    return W


def score(W, tree):
    cl, _ = clusters(tree)
    total = 0
    for q, w in W.items():
        t = displayed(cl, q)
        if t is not None:
            total += w[t]
    return total


# ---- every unrooted binary tree, every circular order ------------------------------------------------------
def all_trees(taxa):
    """All unrooted binary trees on taxa, as nested lists rooted at taxa[0]: [taxa[0], subtree]."""
    def insert(t, x):                                      # all ways to attach leaf x to an edge of rooted tree t
        yield [t, x]
        if isinstance(t, list):
            for i in range(len(t)):
                for sub in insert(t[i], x):
                    yield t[:i] + [sub] + t[i + 1:]
    trees = [[taxa[1], taxa[2]]]
    for x in taxa[3:]:
        trees = [n for t in trees for n in insert(t, x)]
    return [[taxa[0], t] for t in trees]


def all_orders(taxa):
    first = taxa[0]
    return [(first,) + p for p in itertools.permutations(taxa[1:]) if p[0] < p[-1]]


def compatible(tree, order):
    """True when every cluster of the tree is one contiguous arc of the circular order."""
    cl, allv = clusters(tree)
    n = len(order)
    pos = {x: i for i, x in enumerate(order)}
    for C in cl:
        if len(C) in (0, n):
            continue
        marks = [0] * n
        for x in C:
            marks[pos[x]] = 1
        if sum(1 for i in range(n) if marks[i] != marks[(i + 1) % n]) != 2:
            return False
    return True


def newick_of(tree):
    def rec(x):
        return x if not isinstance(x, list) else "(" + ",".join(rec(c) for c in x) + ")"
    return rec(tree) + ";"
