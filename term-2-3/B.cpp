#include <iostream>
#include <vector>
#include <stack>

struct Node{
    int value;
    int h;
    std::vector<Node *> parents;
    std::vector<Node *> childs;
};

Node * head;
std::vector<Node *> parents{};

void dfs(Node * node, int h) {
    for (int i = 0; (1 << i) <= parents.size(); ++i) {
        node->parents.push_back(parents[parents.size() - (1 << i)]);
    }
    parents.push_back(node);
    node->h = h++;
    for (Node * child : node->childs) {
        dfs(child, h);
    }
    parents.pop_back();
}

int lca(Node * u, Node * v) {
    if (u->h < v->h) {
        std::swap(u, v);
    }
    while (u->h != v->h) {
        int c = 0;
        int k = u->h - v->h;
        while ((1 << c) <= k) {
            c++;
        }
        u = u->parents[c - 1];
    }
    if (u->value == v->value) {
        return u->value;
    }
    while (u->parents[0]->value != v->parents[0]->value) {
        int k = 0;
        while (u->parents.size() != k && u->parents[k]->value != v->parents[k]->value) {
            k++;
        }
        u = u->parents[k - 1];

        v = v->parents[k - 1];
    }
    return u->parents[0]->value;
}

int main() {
    int n;
    std::scanf("%d\n", &n);
    std::vector<Node *> nodes;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        nodes.push_back(new Node{i + 1, {}, {}});
    }

    head = nodes[0];

    for (int i = 1; i < n; ++i) {
        int value;
        std::scanf("%d\n", &value);
        nodes[value - 1]->childs.push_back(nodes[i]);
    }

    dfs(head, 0);

    int m;
    std::scanf("%d\n", &m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::scanf("%d %d", &u, &v);
        int p = lca(nodes[u - 1], nodes[v - 1]);
        std::printf("%d\n", p);
    }

    return 0;
}

