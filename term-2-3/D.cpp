#include <iostream>
#include <vector>
#include <stack>

struct Node{
    int value;
    int h;
    bool isAlive;
    std::vector<Node *> parents;
    Node * aliveP;
};

void add(Node * node, Node * parent) {
    node->parents.push_back(parent);
    for (int i = 0; i < parent->parents.size(); ++i) {
        parent = parent->parents[i];
        node->parents.push_back(parent);
    }
    node->aliveP = node->parents[0];
}

void remove(Node * node) {
    node->isAlive = false;
}

Node * lca(Node * u, Node * v) {
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

Node * plca(Node * l) {
    if (!l->isAlive) {
        l->aliveP = plca(l->aliveP);
        return l->aliveP;
    }
    return l;
}

int alca(Node * u, Node * v) {
    return plca(lca(u, v))->value;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Node *> nodes;
    nodes.reserve(n);

    nodes.push_back(new Node{1, 0, true, {}});

    for (int i = 1; i <= n; ++i) {
        char symbol;
        std::cin >> symbol;
        switch (symbol) {
            case '+': {
                int index;
                std::cin >> index;
                Node * p = nodes[index - 1];
                Node * v = new Node{(int)nodes.size() + 1, p->h + 1, true, {}};
                nodes.push_back(v);
                add(v, p);
                continue;
            }
            case '-': {
                int index;
                std::cin >> index;
                remove(nodes[index - 1]);
                continue;
            }
            case '?': {
                int x, y;
                std::cin >> x >> y;
                std::cout << alca(nodes[x - 1], nodes[y - 1]) << std::endl;
                continue;
            }
            default: return 0;
        }
    }
    return 0;
}