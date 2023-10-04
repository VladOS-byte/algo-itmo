#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

struct Node {
    int id;

    Node(int id) {
        this->id = id;
    }

    struct Edge {
        Node * from;
        Node * to;
        bool deprecate = false;

        Edge(Node * from, Node * to) {
            this->from = from;
            this->to = to;
        }
    };
    bool visit = false;
    bool deprecate = false;

    std::vector<Edge *> edges;
    Edge * revert = nullptr;
};

void revertEdge(Node::Edge * edge) {
    edge->to->revert = edge;
    edge->from->revert = edge;
}

bool dfs(Node * node) {
    if (node->visit) {
        return false;
    }
    node->visit = true;
    
    for (Node::Edge * edge : node->edges) {
        if (edge->to->revert == nullptr || dfs(edge->to->revert->from)) {
            revertEdge(edge);
            return true;
        }
    }
    
    return false;
}

void inviteA(Node * node) {
    if (node->visit) {
        return;
    }
    node->visit = true;
    // std::cerr << node->id;
    
    for (auto edge : node->edges) {
        if (!edge->deprecate) {
            edge->deprecate = true;
            edge->to->deprecate = true;
            inviteA(edge->to->revert->from);
        }
    }
}

void inviteB(Node * node) {
    if (node->visit) {
        return;
    }
    node->visit = true;
    // std::cerr << node->id;
    
    for (auto edge : node->edges) {
        if (!edge->deprecate) {
            edge->deprecate = true;
            edge->from->deprecate = true;
            inviteB(edge->from->revert->to);
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Node *> A;
    std::vector<Node *> B;
    std::vector<Node *> nodes;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> segments;

    for (int i = 0; i < n; i++) {
        int u, v, x, y;
        std::cin >> u >> v >> x >> y;
        if (x < u) {
            int t = x;
            x = u;
            u = t;
        }
        if (y < v) {
            int t = y;
            y = v;
            v = t;
        }
        segments.push_back({{u, v}, {x, y}});
        nodes.push_back(new Node(i));
    }

    for (int i = 0; i < n; i++) {
        if (segments[i].first.first == segments[i].second.first) {
            A.push_back(nodes[i]);
        } else {
            B.push_back(nodes[i]);
        }
    }

    for (auto a : A) {
        for (auto b : B) {
            if (segments[a->id].first.second <= segments[b->id].first.second &&
                    segments[b->id].first.second <= segments[a->id].second.second && 
                    segments[b->id].first.first <= segments[a->id].second.first &&
                    segments[a->id].second.first <= segments[b->id].second.first) {
                auto edge = new Node::Edge(a, b);
                a->edges.push_back(edge);
                b->edges.push_back(edge);
            }
        }
    }

    for (Node * v : A) {
        dfs(v);
        for (Node * u : A) {
            u->visit = false;
        }
    }

    int r = 0;
    
    for (Node * v : B) {
        if (v->revert != nullptr) {
            r++;
        }
    }

    std::cout << (n - r);
    
    return 0;
}
