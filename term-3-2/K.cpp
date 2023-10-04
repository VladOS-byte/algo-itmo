#include <iostream>
#include <vector>

struct Node {
    int id = 0;

    unsigned grandi = 0;
    unsigned must = 0;

    std::vector<std::pair<Node *, int>> children;
};

void setGrandi(Node * node, Node * parent) {
    unsigned grandi = 0;
    for (auto & child : node->children) {
        if (child.first == parent) {
            continue;
        }
        setGrandi(child.first, node);
        grandi ^= (child.first->grandi + 1);
    }
    node->grandi = grandi;
}

int getFisrtMove(Node * node, Node * parent) {
    for (auto & child : node->children) {
        if (child.first == parent) {
            continue;
        }
        child.first->must = (node->grandi ^ (child.first->grandi + 1) ^ node->must);
        if (child.first->must == 0) {
            return child.second;
        }
        child.first->must--;
        int p = getFisrtMove(child.first, node);
        if (p != -1) {
            return p;
        }
    }
    return -1;
}

int main() {

    int n, s;

    std::cin >> n >> s;
    s--;

    std::vector<Node *> nodes;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node *node = new Node{i};
        nodes.push_back(node);
    }

    for (int i = 1; i < n; ++i) {
        int v, u;
        std::cin >> v >> u;
        v--;
        u--;
        nodes[v]->children.emplace_back(nodes[u], i);
        nodes[u]->children.emplace_back(nodes[v], i);
    }

    setGrandi(nodes[s], nullptr);

    if (nodes[s]->grandi == 0) {
        std::cout << 2;
    } else {
        std::cout << 1 << std::endl << getFisrtMove(nodes[s], nullptr);
    }

    return 0;
}
