#include <iostream>
#include <vector>
#include <set>

struct Node {
    int id;
    bool used = false;

    struct Edge {
        Node * from;
        Node * to;
        long long cost;
    };

    std::vector<Edge *> edges{};
};

std::vector<long long> dp;

void bfs(std::vector<Node *> & nodes, int k) {
    for (int i = 0; i < k; ++i) {
        std::vector<long long> d = std::vector<long long>(nodes.size(), INT64_MAX);
        for (auto & node : nodes) {
            if (dp[node->id] != INT64_MAX) {
                for (auto & e : node->edges) {
                    d[e->to->id] = std::min(d[e->to->id], dp[e->from->id] + e->cost);
                }
            }
        }
        dp = d;
    }
}

int main() {
    std::vector<Node *> nodes = std::vector<Node *>();
    int n, m, k, s;
    std::cin >> n >> m >> k >> s;
    s--;
    dp = std::vector<long long>();
    dp.reserve(n);
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node * node = new Node{i};
        nodes.push_back(node);
        dp.push_back(INT64_MAX);
    }

    dp[s] = 0;

    for (int i = 0; i < m; ++i) {
        int v, u;
        long long cost;
        std::cin >> v >> u >> cost;
        v--; u--;
        nodes[v]->edges.push_back(new Node::Edge{nodes[v], nodes[u], cost});
    }

    bfs(nodes, k);

    for (int i = 0; i < n; ++i) {
        std::cout << (dp[i] == INT64_MAX ? -1 : dp[i]) << " ";
    }

    return 0;
}
