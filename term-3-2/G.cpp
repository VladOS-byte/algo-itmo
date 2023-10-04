#include <iostream>
#include <vector>
#include <set>

struct Node {
    int id = 0;

    bool used = false;

    struct Edge {
        Node * to;
        int cost;
    };

    std::vector<Edge *> edges;
};

std::vector<std::vector<Node *>> createNewNodes(std::vector<Node *> & nodes, int div) {
    std::vector<std::vector<Node *>> newNodes;
    newNodes.reserve(nodes.size());

    for (int i = 0; i < nodes.size(); ++i) {
        std::vector<Node *> tmp;
        tmp.reserve(div);
        for (int j = 0; j < div; ++j) {
            tmp.push_back(new Node{i * div + j});
        }
        newNodes.push_back(tmp);
    }

    return newNodes;
}


void createNewGraph(std::vector<std::vector<Node *>> & newNodes,
                    Node * node, int div, int s) {
    newNodes[node->id][s]->used = true;
    for (auto & e : node->edges) {
        newNodes[node->id][s]->edges.push_back(new Node::Edge{newNodes[e->to->id][(s + e->cost) % div], e->cost});
        if (!newNodes[e->to->id][(s + e->cost) % div]->used) {
            createNewGraph(newNodes, e->to, div, (s + e->cost) % div);
        }
    }
}


std::vector<std::vector<int>> bfs(std::vector<std::vector<Node *>> & nodes, int div) {
    std::vector<std::vector<int>> dp =
            std::vector<std::vector<int>>(nodes.size(),
                                          std::vector<int>(nodes[0].size(), INT32_MAX));
    dp[0][0] = 0;

    std::set<std::pair<int, std::pair<int, int>>> q;
    q.insert({0, {0, 0}});
    while (!q.empty()) {
        Node * node = nodes[q.begin()->second.first][q.begin()->second.second];
        q.erase(q.begin());
        for (auto & e : node->edges) {
            if (dp[e->to->id / div][e->to->id % div] > dp[node->id / div][node->id % div] + e->cost) {
                q.erase({dp[e->to->id / div][e->to->id % div], {e->to->id / div, e->to->id % div}});
                dp[e->to->id / div][e->to->id % div] = dp[node->id / div][node->id % div] + e->cost;
                q.insert({dp[e->to->id / div][e->to->id % div], {e->to->id / div, e->to->id % div}});
            }
        }
    }

    return dp;
}

int main() {

    int n, m;

    std::cin >> n >> m;

    std::vector<Node *> nodes;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node *node = new Node{i};
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

    long long t;
    std::cin >> t;

    if (nodes[0]->edges.empty() || nodes[n - 1]->edges.empty()) {
        std::cout << "Impossible";
        return 0;
    }

    int minEdge = INT32_MAX;

    for (auto & e : nodes[n - 1]->edges) {
        if (e->cost < minEdge) {
            minEdge = e->cost;
        }
    }

    minEdge *= 2;

    std::vector<std::vector<Node *>> newNodes = createNewNodes(nodes, minEdge);

    createNewGraph(newNodes, nodes[0], minEdge, 0);

    if (newNodes[n - 1][t % minEdge]->used) {
        std::vector<std::vector<int>> dp = bfs(newNodes, minEdge);
        if (dp[n - 1][t % minEdge] <= t) {
            std::cout << "Possible";

            return 0;
        }
    }

    std::cout << "Impossible";

    return 0;
}
