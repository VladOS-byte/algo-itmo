#include <fstream>
#include <vector>
#include <map>

struct Node{
    int value;
    int h;
    std::vector<Node *> parents;
    std::vector<int> mincosts;
    std::map<Node *, int> childs;
};

struct Vert {
    int set;
    int min;
};

Node * head;
std::vector<Node *> parents{};
int power;

void propogate(Vert tree[], int v) {
    if (tree[v].set != INT32_MAX) {
        tree[2 * v + 1].set = tree[v].set;
        tree[2 * v + 2].set = tree[v].set;
        tree[2 * v + 1].min = tree[v].set;
        tree[2 * v + 2].min = tree[v].set;
        tree[v].min = tree[v].set;
        tree[v].set = INT32_MAX;
    }
}

void lazy_propogate(Vert tree[], int v, int left, int right) {
    if (right - left > 1) {
        propogate(tree, v);
    } else {
        tree[v].min = tree[v].set;
    }
}

void upgrate(Vert tree[], int v) {
    if (v > 0) {
        do {
            v = (v - 1) >> 1;
            tree[v].min = std::min(tree[2 * v + 1].min, tree[2 * v + 2].min);
        } while (v > 0);
    }
}

void set(Vert tree[], int v, int left, int right, int a, int b, int value) {
    lazy_propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return;
    }
    if (a >= left && right >= b) {
        tree[v].set = value;
        tree[v].min = value;
        upgrate(tree, v);
        return;
    }
    set(tree, 2 * v + 1, left, right, a, (a + b) >> 1, value);
    set(tree, 2 * v + 2, left, right, (a + b) >> 1, b, value);
}

int minimum(Vert tree[], int v, int left, int right, int a, int b) {
    lazy_propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return INT32_MAX;
    }
    if (a >= left && right >= b) {
        return tree[v].min;
    }
    return std::min(minimum(tree, 2 * v + 1, left, right, a, (a + b) >> 1),
                    minimum(tree, 2 * v + 2, left, right, (a + b) >> 1, b));
}

void buildTree(Vert tree[]) {
    for (int i = power - 1; i < (power << 1); ++i) {
        tree[i] = *new Vert();
        tree[i].set = INT32_MAX;
        tree[i].min = INT32_MAX;
    }
    for (int i = power - 2; i >= 0; --i) {
        tree[i] = *new Vert();
        tree[i].set = INT32_MAX;
        tree[i].min = std::min(tree[2 * i + 1].min, tree[2 * i + 2].min);
    }
}

void dfs(Node * node, int h, Vert tree[]) {
    for (int i = 0; (1 << i) <= parents.size(); ++i) {
        node->parents.push_back(parents[parents.size() - (1 << i)]);
        node->mincosts.push_back(minimum(tree, 0, parents.size() - (1 << i), parents.size(), 0, power));
    }
    parents.push_back(node);
    node->h = h++;
    for (std::pair<Node *, int> child : node->childs) {
        set(tree, 0, parents.size() - 1, parents.size(), 0, power, child.second);
        dfs(child.first, h, tree);
    }
    set(tree, 0, parents.size() - 1, parents.size(), 0, power, INT32_MAX);
    parents.pop_back();
}

int lca(Node * u, Node * v) {
    int m = INT32_MAX;
    if (u->h < v->h) {
        std::swap(u, v);
    }
    while (u->h != v->h) {
        int c = 0;
        int k = u->h - v->h;
        while ((1 << c) <= k) {
            c++;
        }
        m = std::min(m, u->mincosts[c - 1]);
        u = u->parents[c - 1];
    }
    if (u->value == v->value) {
        return m == INT32_MAX ? 0: m;
    }
    while (u->parents[0]->value != v->parents[0]->value) {
        int c = 0;
        while (u->parents.size() != c && u->parents[c]->value != v->parents[c]->value) {
            c++;
        }
        m = std::min(m, u->mincosts[c - 1]);
        m = std::min(m, v->mincosts[c - 1]);
        u = u->parents[c - 1];
        v = v->parents[c - 1];
    }
    m = std::min(m, u->mincosts[0]);
    m = std::min(m, v->mincosts[0]);
    return m;
}

int main() {
    int n;
    std::ifstream f("minonpath.in");
    std::ofstream of("minonpath.out");
    f >> n;
    std::vector<Node *> nodes;
    nodes.reserve(n);

    power = 0;
    while ((1 << power) < n) {
        power++;
    }
    power = 1 << power;
    Vert tree[power << 1];
    buildTree(tree);

    for (int i = 0; i < n; ++i) {
        nodes.push_back(new Node{i + 1, 0, {}, {}, {}});
    }

    head = nodes[0];

    for (int i = 1; i < n; ++i) {
        int value, cost;
        f >> value >> cost;
        nodes[value - 1]->childs.insert({nodes[i], cost});
    }

    dfs(head, 0, tree);

    int m;
    f >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        f >> u >> v;
        int p = lca(nodes[u - 1], nodes[v - 1]);
        of << p << std::endl;
    }
    f.close();
    of.close();

    return 0;
}