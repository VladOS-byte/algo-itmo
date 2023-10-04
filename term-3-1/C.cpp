#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

struct Node {
    int id = 0;
    int time = INT32_MAX;
    int parentTime = INT32_MAX;

    struct Edge {
        Node * to;
    };

    std::set<Edge *> edges{};
};


int timer = 0;
std::vector<int> cutpoints = std::vector<int>();
bool isRootCutPoint = false;

int dfs(Node * node, Node * parent) {
    node->time = ++timer;
    int parentTime = INT32_MAX;
    for (auto & edge : node->edges) {
        int temp = INT32_MAX;
        if (parent == nullptr || edge->to->id != parent->id) {
            if (edge->to->time != INT32_MAX) {
                if (edge->to->parentTime != INT32_MAX) {
                    continue;
                }
                temp = edge->to->time;
            } else {
                temp = dfs(edge->to, node);
            }
            if (temp < node->time) {
                parentTime = std::min(temp, parentTime);
            } else if (temp >= node->time) {
                if (parent != nullptr || isRootCutPoint) {
                    cutpoints.push_back(node->id);
                }
                if (parent == nullptr) {
                    isRootCutPoint = true;
                }
            }
        }
    }
    node->parentTime = parentTime;
    return parentTime;
}

Node::Edge * createEdge(Node * u) {
    auto * edge = new Node::Edge();
//    edge->id = id;
    edge->to = u;
    return edge;
}

int main() {
    std::vector<Node *> nodes;
    int m, n;
    std::cin >> n >> m;
    nodes.reserve(n);

    std::set<std::pair<int, int >> edges;

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
        if (v == u || edges.find({u, v}) != edges.end()) {
            continue;
        }
        edges.insert({v, u});
        edges.insert({u, v});
        nodes[v]->edges.insert(createEdge(nodes[u]));
        nodes[u]->edges.insert(createEdge(nodes[v]));
    }

    for (auto & node : nodes) {
        if (node->time == INT32_MAX) {
            isRootCutPoint = false;
            dfs(node, nullptr);
        }
    }
    std::sort(cutpoints.begin(), cutpoints.end());
    int count = 0;
    int prev = -1;
    for (int bridge : cutpoints) {
        if (prev != bridge) {
            count++;
            prev = bridge;
        }
    }

    std::cout << count << std::endl;
    prev = -1;
    for (int bridge : cutpoints) {
        if (prev != bridge) {
            std::cout << bridge << " ";
            prev = bridge;
        }
    }

    return 0;
}
