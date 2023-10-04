#include <iostream>
#include <vector>
#include <stack>

struct Node{
    int value;
    std::vector<Node *> parents;
    std::vector<Node *> childs;
};

Node * head;
std::vector<Node *> parents{};

void dfs(Node * node) {
    for (int i = 0; (1 << i) <= parents.size(); ++i) {
        node->parents.push_back(parents[parents.size() - (1 << i)]);
    }
    parents.push_back(node);
    for (Node * child : node->childs) {
        dfs(child);
    }
    parents.pop_back();
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Node *> nodes;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        nodes.push_back(new Node{i + 1, {}, {}});
    }

    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        if (value == 0) {
            head = nodes[i];
        } else {
            nodes[value - 1]->childs.push_back(nodes[i]);
        }
    }

    dfs(head);

    for (int i = 0; i < n; ++i) {
        Node * node = nodes[i];
        std::cout << (i + 1) << ':';
        for (Node * p : node->parents) {
            std::cout << ' ' << p->value;
        }
        std::cout << std::endl;
    }

    return 0;
}

