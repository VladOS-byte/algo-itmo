#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int id;
    bool cyc = false;
    struct Edge {
        Node * to;
        long long cost;
    };
    std::vector<Edge> edges;
};

long long d[2000];

void findNegativeCycles(int size, int s, std::vector<Node *> nodes) {
    Node * p[size];
    for (int i = 0; i < size; ++i) {
        d[i] = INT64_MAX / 2;
        p[i] = nullptr;
    }
    d[s] = 0;
    for (int i = 0; i < size; ++i) {
        for (auto & node : nodes) {
            for (auto & e : node->edges) {
                if (d[node->id] != INT64_MAX / 2 && d[e.to->id] > d[node->id] + e.cost) {
                    d[e.to->id] = d[node->id] + e.cost;
                    p[e.to->id] = node;
                }
            }
        }
    }
    for (auto & node : nodes) {
        for (auto & e : node->edges) {
            if (d[node->id] != INT64_MAX / 2 && d[e.to->id] > d[node->id] + e.cost) {
                Node * v = e.to;
                for (int i = 0; i < size; ++i) {
                    v = p[v->id];
                }
                Node * u = v;
                while (u->id != p[v->id]->id) {
                    v = p[v->id];
                    v->cyc = true;
                }
                u->cyc = true;
            }
        }
    }
}

void dfs(Node * node) {
    for (auto & e : node->edges) {
        if (!e.to->cyc) {
            e.to->cyc = true;
            dfs(e.to);
        }
    }
}

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    s--;
    std::vector<Node *> nodes;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        nodes.push_back(new Node{i});
    }

    int v, u;
    long long cost;
    for (int i = 0; i < m; ++i) {
        std::cin >> v >> u >> cost;
        v--;
        u--;
        nodes[v]->edges.push_back({nodes[u], cost});
    }

    findNegativeCycles(n, s, nodes);

    for (int i = 0; i < n; ++i) {
        if (d[i] != INT64_MAX / 2 && nodes[i]->cyc) {
            dfs(nodes[i]);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (d[i] == INT64_MAX / 2) {
            std::cout << "*" << std::endl;
        } else if (nodes[i]->cyc) {
            std::cout << "-" << std::endl;
        } else {
            std::cout << d[i] << std::endl;
        }
    }

    return 0;
}
