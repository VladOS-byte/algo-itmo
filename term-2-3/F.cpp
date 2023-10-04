#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> euler;

struct Node{
    int value;
    int h;
    std::vector<Node *> parents;
    std::vector<Node *> childs;
    bool operator < (const Node & node) const
    {
        return euler[value - 1] < euler[node.value - 1];
    }
};

std::vector<Node *> ps;
int o = 0;

void dfsPs(Node * node) {
    for (int i = 0; (1 << i) <= ps.size(); ++i) {
        node->parents.push_back(ps[ps.size() - (1 << i)]);
    }
    ps.push_back(node);
    for (Node * child : node->childs) {
        child->h = node->h + 1;
        dfsPs(child);
    }
    euler[node->value - 1] = o++;
    ps.pop_back();
}

Node * lca(Node * u, Node * v) {
    if (u->h < v->h) {
        std::swap(u, v);
    }
    while (u->h != v->h) {
        int i = 0;
        int k = u->h - v->h;
        while ((1 << i) <= k) {
            i++;
        }
        u = u->parents[i - 1];
    }
    if (u->value == v->value) {
        return u;
    }
    while (u->parents[0]->value != v->parents[0]->value) {
        int k = 0;
        while (u->parents.size() != k && u->parents[k]->value != v->parents[k]->value) {
            k++;
        }
        u = u->parents[k - 1];

        v = v->parents[k - 1];
    }
    return u->parents[0];
}

int main() {
    int n, m;
    std::scanf("%d\n", &n);
    std::vector<Node *> nodes;
    nodes.reserve(n);
    euler.resize(n, 0);

    for (int i = 1; i <= n; ++i) {
        nodes.push_back(new Node{i, 0, {}, {}});
    }

    Node * head = nodes[0];
    for (int i = 0; i < n; ++i) {
        int u;
        std::scanf("%d", &u);
        if (u == -1) {
            head = nodes[i];
        } else {
            nodes[u - 1]->childs.push_back(nodes[i]);
        }
    }

    dfsPs(head);

    std::scanf("\n%d", &m);
    std::vector<Node> query;
    for (int i = 0; i < m; ++i) {
        int k, v;
        std::scanf("\n%d", &k);
        query.clear();
        for (int j = 0; j < k; ++j) {
            std::scanf("%d", &v);
            query.push_back(*nodes[v - 1]);
        }
        sort(query.begin(), query.end());
        Node * l = &query[0];
        int c = l->h + 1;
        for (int j = 1; j < k; ++j) {
            l = lca(&query[j - 1], &query[j]);
            c += query[j].h - l->h;
        }
        std::printf("%d\n", c);
    }

    return 0;
}