#include <iostream>
#include <stack>
#include <vector>
#include <set>

struct Node {
    int id = 0;
    int time = INT32_MAX;
    int up = INT32_MAX;
    int component = -1;

    struct Edge {
        Node * to;
    };

    std::vector<Edge *> edges{};
};

std::stack<Node * > stack{};
std::set<Node * > sstack{};

int timer = 0;
std::vector<std::vector<Node *>> components{};

void dfs(Node * node) {
    stack.push(node);
    sstack.insert(node);
    node->time = ++timer;
    node->up = timer;
    for (auto & edge : node->edges) {
        if (edge->to->time == INT32_MAX) {
            dfs(edge->to);
            node->up = std::min(node->up, edge->to->up);
        } else if (sstack.find(edge->to) != sstack.end()) {
            node->up = std::min(node->up, edge->to->time);
        }
    }
    if (node->up == node->time) {
        std::vector<Node *> temp{};
        while (!stack.empty()) {
            temp.push_back(stack.top());
            stack.top()->component = components.size();
            sstack.erase(stack.top());
            if (stack.top()->id == node->id) {
                stack.pop();
                break;
            }
            stack.pop();
        }
        components.push_back(temp);
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
    }

    for (auto & node : nodes) {
        if (node->time == INT32_MAX) {
            dfs(node);
        }
    }

    std::set<std::pair<int, int>> matrix;

    for (auto & node : nodes) {
        for (auto & edge : node->edges) {
            if (node->component != edge->to->component) {
                matrix.insert({node->component, edge->to->component});
            }
        }
    }

    int count = matrix.size();

    std::cout << count;

    return 0;
}
