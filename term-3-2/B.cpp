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

void bfs(std::vector<Node *> & nodes) {
    std::set<std::pair<long long, int>> q;
    q.insert({0, 0});
    while (!q.empty()) {
        Node * node = nodes[q.begin()->second];
        q.erase(q.begin());
        for (auto & e : node->edges) {
            if (dp[e->to->id] > dp[node->id] + e->cost) {
                q.erase({dp[e->to->id], e->to->id});
                dp[e->to->id] = dp[node->id] + e->cost;
                q.insert({dp[e->to->id], e->to->id});
            }
        }
    }
}

int main() {
    std::vector<Node *> nodes = std::vector<Node *>();
    int n, m;
    std::cin >> n >> m;
    dp = std::vector<long long>();
    dp.reserve(n);
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node * node = new Node{i};
        nodes.push_back(node);
        dp.push_back(INT64_MAX);
    }

    dp[0] = 0;

    for (int i = 0; i < m; ++i) {
        int v, u;
        long long cost;
        std::cin >> v >> u >> cost;
        v--; u--;
        nodes[v]->edges.push_back(new Node::Edge{nodes[v], nodes[u], cost});
        nodes[u]->edges.push_back(new Node::Edge{nodes[u], nodes[v], cost});
    }

    bfs(nodes);

    for (int i = 0; i < n; ++i) {
        std::cout << dp[i] << " ";
    }

    return 0;
}
