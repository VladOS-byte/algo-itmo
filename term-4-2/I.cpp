#include<iostream>
#include<vector>
#include <set>

#define ll long long

struct Node {
    Node(int i) {
        this->id = i;
    }

    int id;
    struct Edge {
        Edge(Node *pNode1, ll i, ll w, Edge * back) {
            this->to = pNode1;
            this->c = i;
            this->f = 0;
            this->back = back;
            this->w = w;
        }
        Edge * back;
        Node * to;
        ll c;
        ll f;
        ll w;
    };

    Edge * path;
    std::vector<Edge *> edges = {};
};

int nodes_size;
Node * terminal;
Node * start;
std::vector<ll> levels;

bool pathExists() {
    std::set<std::pair<ll, Node *>> nodes;
    nodes.insert({0, start});
    levels = std::vector<ll>(nodes_size, INT64_MAX);
    levels[start->id] = 0;
    while (!nodes.empty()) {
        auto n = *(nodes.begin());
        nodes.erase(n);
        for (auto p : n.second->edges) {
            if (p->f != p->c && levels[p->to->id] > levels[n.second->id] + p->w) {
                if (levels[p->to->id] != INT64_MAX) {
                    nodes.erase({levels[p->to->id], p->to});
                }
                levels[p->to->id] = levels[n.second->id] + p->w;
                p->to->path = p;
                nodes.insert({levels[p->to->id], p->to});
            }
        }
    }
    return levels[terminal->id] != INT64_MAX;
}

ll dfs(Node * node) {
    if (node->id == start->id) {
        return INT64_MAX;
    }
    auto * e = node->path;
    return std::min(e->c - e->f, dfs(e->back->to));
}

void constructEdge(Node * u, Node * v, ll c, ll w) {
    auto edge = new Node::Edge(v, c, w, nullptr);
    auto backEdge = new Node::Edge(u, 0, -w, edge);
    edge->back = backEdge;
    u->edges.push_back(edge);
    v->edges.push_back(backEdge);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n = 3;
    int r1, s1, p1;
    int r2, s2, p2;
    std::cin >> r1 >> s1 >> p1;
    std::cin >> r2 >> s2 >> p2;

    std::vector<int> rsp1 = {r1, s1, p1};
    std::vector<int> rsp2 = {r2, s2, p2};

    nodes_size = 2 * n + 2;
    std::vector<Node *> nodes;
    nodes.reserve(nodes_size);

    for (int i = 0; i < nodes_size; ++i) {
        nodes.push_back(new Node(i));
    }

    start = nodes[nodes_size - 2];
    terminal = nodes[nodes_size - 1];

    std::vector<int> wins = {1, 2, 0};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            constructEdge(nodes[i], nodes[n + j], INT64_MAX, wins[i] == j ? 1 : 0);
        }
    }

    for (int i = 0; i < n; ++i) {
        constructEdge(start, nodes[i], rsp1[i], 0);
    }

    for (int i = 0; i < n; ++i) {
        constructEdge(nodes[n + i], terminal, rsp2[i], 0);
    }

    ll sum = 0;
    while (pathExists()) {
        ll s = dfs(terminal);

        for (Node * i = terminal; i->id != start->id; i = i->path->back->to) {
            i->path->f += s;
            i->path->back->f -= s;
            sum += i->path->w * s;
        }
    }

    std::cout << sum;

    return 0;
}
