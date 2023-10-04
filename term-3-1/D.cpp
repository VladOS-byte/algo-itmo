#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int id = 0;
    int time = INT32_MAX;
    int parentTime = INT32_MAX;
    int color = 0;

    struct Edge {
        bool isBridge = false;
        Node * to;
    };

    std::vector<Edge *> edges{};
};


int timer = 0;
Node::Edge * edgeToParent;

int dfs(Node * node, Node * parent) {
    node->time = ++timer;
    int parentTime = INT32_MAX;
    Node::Edge * localEdgeToParent;
    bool isSecondEdgeToParent = false;
    for (auto & edge : node->edges) {
        int temp = INT32_MAX;

        if (parent == nullptr || edge->to->id != parent->id || isSecondEdgeToParent) {
            if (edge->to->time != INT32_MAX) {
                temp = std::min(edge->to->time, edge->to->parentTime);
            } else {
                temp = dfs(edge->to, node);
            }
            if (temp < node->time) {
                parentTime = std::min(temp, parentTime);
            } else if (temp > node->time) {
                edge->isBridge = true;
                if (edgeToParent != nullptr && edgeToParent->to->id == node->id) {
                    edgeToParent->isBridge = true;
                }
            }
        } else if (edge->to->id == parent->id) {
            isSecondEdgeToParent = true;
            localEdgeToParent = edge;
        }
    }
    edgeToParent = parent == nullptr ? nullptr : localEdgeToParent;
    node->parentTime = parentTime;
    return parentTime;
}


void paintNodes(Node * node, Node * parent, int color) {
    node->color = color;
    for (auto & edge : node->edges) {
        if (edge->isBridge || edge->to->color == color || (parent != nullptr && edge->to->id == parent->id)) {
            continue;
        }
        paintNodes(edge->to, node, color);
    }
}


Node::Edge * createEdge(Node * u) {
    auto * edge = new Node::Edge();
    edge->to = u;
    return edge;
}


int main() {
    std::vector<Node *> nodes;
    int m, n;
    std::cin >> n >> m;
    nodes.reserve(n);
    for (int i = 0; i < n; ++i) {
        Node * node = new Node();
        node->id = i + 1;
        nodes.push_back(node);
    }

    for (int i = 0; i < m; ++i) {
        int v, u;
        std::cin >> v >> u;
        v--;
        u--;
        nodes[v]->edges.push_back(createEdge(nodes[u]));
        nodes[u]->edges.push_back(createEdge(nodes[v]));
    }

    for (auto & node : nodes) {
        if (node->time == INT32_MAX) {
            dfs(node, nullptr);
        }
    }

    int color = 0;
    for (auto & node : nodes) {
        if (node->color == 0) {
            paintNodes(node, nullptr, ++color);
        }
    }

    std::cout << color << std::endl;

    for (auto & node : nodes) {
        std::cout << node->color << " ";
    }

    return 0;
}
