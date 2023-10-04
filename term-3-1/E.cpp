#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

struct Node {
    int id = 0;
    int time = INT32_MAX;
    int parentTime = 0;
    int up = INT32_MAX;

    struct Edge {
        Node * to;
        int color = 0;
    };

    std::vector<Edge *> edges{};
};

int maxColor = 0;
void paintEdges(Node *node, int color, Node * parent) {
    node->parentTime = 1;
    for (auto & edge : node->edges) {
        if (parent != nullptr && edge->to->id == parent->id) {
            continue;
        }
        if (edge->to->parentTime == 0) {
            if (edge->to->up >= node->time) {
                edge->color = ++maxColor;
                paintEdges(edge->to, maxColor, node);
            } else {
                edge->color = color;
                paintEdges(edge->to, color, node);
            }
        } else if (edge->to->time < node->time) {
            edge->color = color;
        }
    }
}

int timer = 0;
bool isRootCutPoint = false;

void dfs(Node * node, Node * parent) {
    node->time = ++timer;
    node->up = timer;
    node->parentTime = 1;
    for (auto & edge : node->edges) {
        if (parent == nullptr || edge->to->id != parent->id) {
            if (edge->to->parentTime == 1) {
                node->up = std::min(node->up, edge->to->time);
            } else {
                dfs(edge->to, node);
                node->up = std::min(node->up, edge->to->up);
            }
        }
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

    std::map<std::pair<int, int>, std::pair<Node::Edge * , Node::Edge * >> edges;
    std::vector<std::pair<Node::Edge * , Node::Edge * >> edgesID;


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
        Node::Edge * edge1 = createEdge(nodes[u]);
        Node::Edge * edge2 = createEdge(nodes[v]);
        auto p = edges.find({v, u});
        if (p != edges.end()) {
            edgesID.emplace_back(p->second.first, p->second.second);
            continue;
        }
        edgesID.emplace_back(edge1, edge2);
        edges.insert({{v, u}, {edge1, edge2}});
        edges.insert({{u, v}, {edge1, edge2}});
        nodes[v]->edges.push_back(edge1);
        nodes[u]->edges.push_back(edge2);
    }

    for (auto & node : nodes) {
        if (node->time == INT32_MAX) {
            isRootCutPoint = false;
            dfs(node, nullptr);
        }
    }

    for (auto & node : nodes) {
        node->parentTime = 0;
    }

    for (auto & node : nodes) {
        if (node->parentTime == 0) {
            paintEdges(node, maxColor, nullptr);
        }
    }

    std::cout << maxColor << std::endl;
    for (auto & edge : edgesID) {
        std::cout << std::max(edge.first->color, edge.second->color) << " ";
    }

    return 0;
}
