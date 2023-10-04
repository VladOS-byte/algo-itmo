#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct Node {
    int id = 0;
    char winnable = '?';
    int out = 0;
    bool used = false;

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
            node->used = true;
            q.push(node);
        }
    }
    while (!q.empty()) {
        auto & node = q.front();
        q.pop();
        for (auto & e : node->from) {
            if (node->winnable == '-') {
                e->node->winnable = '+';
                if (!e->node->used) {
                    q.push(e->node);
                    e->node->used = true;
                }
            } else {
                e->node->out++;
                if (e->node->out == e->node->to.size()) {
                    e->node->winnable = '-';
                    q.push(e->node);
                    e->node->used = true;
                }
            }
        }
    }
}

int main() {
    auto fin = fopen("game.in", "r");
    auto fout = fopen("game.out", "w");

    std::vector<Node *> nodes;

    int n, m, s;
    fscanf(fin, "%d%d%d", &n, &m, &s);
    s--;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node * node = new Node{i, '-'};
        nodes.push_back(node);
    }

    for (int i = 0; i < m; ++i) {
        int v, u;
        fscanf(fin, "\n%d%d", &v, &u);
        v--;
        u--;
        nodes[v]->to.push_back(new Node::Edge{nodes[u]});
        nodes[u]->from.push_back(new Node::Edge{nodes[v]});
        nodes[v]->winnable = '?';
    }

    game(nodes);

    fprintf(fout, "%s player wins", (nodes[s]->winnable == '+' ? "First" : "Second"));

    return 0;
}
