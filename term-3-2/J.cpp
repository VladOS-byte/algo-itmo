#include <iostream>
#include <vector>
#include <set>
#include <queue>

struct Node {
    char winnable = '?';
    int out = 0;
    int grandi = -1;

    struct Edge {
        Node * node;
    };

    std::vector<Edge *> to;
    std::vector<Edge *> from;
};

void game(std::vector<Node *> & nodes) {
    std::queue<Node *> q;
    for (auto & node : nodes) {
        if (node->winnable == '-') {
            node->grandi = 0;
            q.push(node);
        }
    }
    while (!q.empty()) {
        auto & node = q.front();
        q.pop();
        if (node->grandi == -1) {
            std::set<int> grandi;
            for (auto & e : node->to) {
                grandi.insert(e->node->grandi);
            }
            node->grandi = 0;
            for (int i : grandi) {
                if (i == node->grandi) {
                    node->grandi++;
                }
            }
        }
        for (auto & e : node->from) {
            e->node->out++;
            if (node->winnable == '-') {
                e->node->winnable = '+';
            }
            if (e->node->out == e->node->to.size()) {
                if (e->node->winnable == '?') {
                    e->node->winnable = '-';
                }
                q.push(e->node);
            }
        }
    }
}

int main() {

    int n, m;

    std::cin >> n >> m;

    std::vector<Node *> nodes;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node *node = new Node{ '-'};
        nodes.push_back(node);
    }

    for (int i = 0; i < m; ++i) {
        int v, u;
        std::cin >> v >> u;
        v--;
        u--;
        nodes[v]->to.push_back(new Node::Edge{nodes[u]});
        nodes[u]->from.push_back(new Node::Edge{nodes[v]});
        nodes[v]->winnable = '?';
    }

    game(nodes);

    for (auto & n : nodes) {
        std::cout << n->grandi << std::endl;
    }

    return 0;
}
