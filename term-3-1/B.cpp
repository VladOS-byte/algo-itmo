#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int id = 0;
    int time = INT32_MAX;
    int parentTime = INT32_MAX;

    struct Edge {
        int id;
        Node * to;
    };

    std::vector<Edge *> edges{};
};


int timer = 0;
std::vector<int> bridges = std::vector<int>();

int dfs(Node * node, Node * parent) {
    node->time = ++timer;
    int parentTime = INT32_MAX;
    for (auto & edge : node->edges) {
        int temp = INT32_MAX;
        if (parent == nullptr || edge->to->id != parent->id) {
            if (edge->to->time != INT32_MAX) {
                temp = std::min(edge->to->time, edge->to->parentTime);
            } else {
                temp = dfs(edge->to, node);
            }
            if (temp < node->time) {
                parentTime = std::min(temp, parentTime);
            } else if (temp > node->time) {
                bridges.push_back(edge->id);
            }
        }
    }
    node->parentTime = parentTime;
    return parentTime;
}

Node::Edge * createEdge(int id, Node * u) {
    auto * edge = new Node::Edge();
    edge->id = id;
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
        nodes[v]->edges.push_back(createEdge(i + 1, nodes[u]));
        nodes[u]->edges.push_back(createEdge(i + 1, nodes[v]));
    }

    for (auto & node : nodes) {
        if (node->time == INT32_MAX) {
            dfs(node, nullptr);
        }
    }
    std::sort(bridges.begin(), bridges.end());
    std::cout << bridges.size() << std::endl;
    for (int bridge : bridges) {
        std::cout << bridge << " ";
    }

    return 0;
}
