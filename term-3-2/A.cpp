#include <iostream>
#include <vector>

struct Node {
    int id;
    bool used;

    struct Edge {
        Node * to;
        int cost;
    };

    std::vector<Edge *> edges;
};

int main() {
    std::vector<Node *> nodes = std::vector<Node *>();
    int n;
    std::cin >> n;
    int dp[n][n];
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node * node = new Node{i, false};
        nodes.push_back(node);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cost;
            std::cin >> cost;
            if (cost != 0) {
                nodes[i]->edges.push_back(new Node::Edge{nodes[j], cost});
            }
            dp[i][j] = cost;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (u != v) {
                    dp[u][v] = std::min(dp[u][v], dp[u][i] + dp[i][v]);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
