#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <set>
#include <algorithm>

struct Node {
    int id = 0;
    int time = INT32_MAX;
    int up = INT32_MAX;
    int component = -1;

    struct Edge {
        Node * to;
        int cost;
    };

    std::vector<Edge *> edges{};
};

std::stack<Node * > stack{};
std::set<Node * > sstack{};

int timer = 0;
std::vector<std::vector<Node *>> components{};

void dfs(Node * node, int maxCost) {
    stack.push(node);
    sstack.insert(node);
    node->time = ++timer;
    node->up = timer;
    for (auto & edge : node->edges) {
        if (edge->cost > maxCost) {
            continue;
        }
        if (edge->to->time == INT32_MAX) {
            dfs(edge->to, maxCost);
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

Node::Edge * createEdge(Node * u, int cost) {
    auto * edge = new Node::Edge();
    edge->to = u;
    edge->cost = cost;
    return edge;
}

void clearAll(std::vector<Node *> & nodes) {
    sstack.clear();
    components.clear();
    timer = 0;
    for (auto & node : nodes) {
        node->time = INT32_MAX;
        node->up = INT32_MAX;
        node->component = -1;
    }
}

bool checkComponents(std::vector<Node *> & nodes) {
    return std::all_of(nodes.cbegin(), nodes.cend(), [](Node * node){ return node->component == 0; });
}

int main() {
    std::vector<Node *> nodes;
    int n;
    auto fin = fopen("avia.in", "r");
    auto fout = fopen("avia.out", "w");
    fscanf(fin, "%d", &n);
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node * node = new Node();
        node->id = i + 1;
        nodes.push_back(node);
    }

    for (int v = 0; v < n; ++v) {
        fscanf(fin, "\n");
        for (int u = 0; u < n; ++u) {
            int c;
            fscanf(fin, "%d", &c);
            if (v == u) {
                continue;
            }
            nodes[v]->edges.push_back(createEdge(nodes[u], c));
        }
    }

    int l = -1, r = INT32_MAX / 2, m;
    while (r - l > 1) {
        m = (r + l) / 2;
        dfs(nodes[0], m);
        if (checkComponents(nodes)) {
            r = m;
        } else {
            l = m;
        }
        clearAll(nodes);
    }

    fprintf(fout, "%d", r);

    return 0;
}
