#include <iostream>
#include <vector>

struct Node{
    int value;
    int w;
    std::vector<Node *> links;
    bool use = false;
};

std::vector<int> parents;

int initW(Node * node, Node * parent) {
    node->w = 1;
    for (Node * c : node->links) {
        if ((parent == nullptr || c->value != parent->value) && !c->use) {
            node->w += initW(c, node);
        }
    }
    return node->w;
}

Node * getCentroid(Node * node, Node * parent, int w) {
    Node * m = nullptr;
    for (Node * c : node->links) {
        if (!c->use && (parent == nullptr || c->value != parent->value) &&
            2 * c->w >= w && (m == nullptr || c->w > m->w)) {
            m = c;
        }
    }
    if (m == nullptr) {
        return node;
    } else {
        return getCentroid(m, node, w);
    }
}

Node * dfs(Node * node, Node * parent) {
    Node * c = getCentroid(node, parent, node->w);
    c->use = true;
    initW(c, parent);
    parents[c->value - 1] = parent == nullptr ? 0 : parent->value;
    for (Node * n : c->links) {
        if ((parent == nullptr || n->value != parent->value) && !n->use) {
            dfs(n, c);
        }
    }
    return c;
}

int main() {
    int n;
    std::scanf("%d", &n);
    std::vector<Node *> nodes;
    nodes.reserve(n);
    parents.resize(n, -1);
    for (int i = 1; i <= n; ++i) {
        nodes.push_back(new Node{i, 0, {}});
    }

    for (int i = 1; i < n; ++i) {
        int u, v;
        std::scanf("%d%d", &u, &v);
        nodes[u - 1]->links.push_back(nodes[v - 1]);
        nodes[v - 1]->links.push_back(nodes[u - 1]);
    }

    initW(nodes[0], nullptr);
    dfs(nodes[0], nullptr);

    for (Node *node : nodes) {
        std::printf("%d ", parents[node->value - 1]);
    }

    return 0;
}