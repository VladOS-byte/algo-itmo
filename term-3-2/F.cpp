#include <iostream>
#include <vector>
#include <set>

struct Node {
    int id = 0;

    struct Edge {
        Node * to;
        int cost;
    };

    std::vector<Edge *> edges;
};

void fb(std::vector<Node *> & nodes, std::vector<long long> & diff) {
    for (int i = 0; i < nodes.size(); ++i) {
        for (auto & n : nodes) {
            for (auto & e : n->edges) {
                diff[e->to->id] = std::min(diff[e->to->id], diff[n->id] + e->cost);
            }
        }
    }
}

std::vector<long long> bfs(std::vector<Node *> & nodes, int start) {
    std::set<std::pair<long long, int>> q;
    std::vector<long long> dp = std::vector<long long>(nodes.size(), INT64_MAX / 2);
    dp[start] = 0;
    q.insert({0, start});
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
    return dp;
}

int main() {
    std::vector<Node *> nodes;

    int n, m;
    std::cin >> n >> m;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node * node = new Node{i};
        nodes.push_back(node);
    }

    for (int i = 0; i < m; ++i) {
        int v, u, c;
        std::cin >> v >> u >> c;
        v--;
        u--;
        nodes[v]->edges.push_back(new Node::Edge{nodes[u], c});
        nodes[u]->edges.push_back(new Node::Edge{nodes[v], c});
    }

    int a, b, c;
    std::cin >> a >> b >> c;
    a--;
    b--;
    c--;

    std::vector<long long> diffA = bfs(nodes, a);
    std::vector<long long> diffB = bfs(nodes, b);

    if (diffA[b] == INT64_MAX / 2 || diffA[c] == INT64_MAX / 2) {
        std::cout << -1;
    } else {
        long long weight = std::min(diffA[b] + std::min(diffA[c], diffB[c]), diffA[c] + diffB[c]);
        std::cout << weight;
    }

    return 0;
}
