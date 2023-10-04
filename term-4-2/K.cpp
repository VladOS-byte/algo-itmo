#include<iostream>
#include<vector>
#include <set>
#include <iomanip>

#define ll long long

struct Node {
    Node(int i) {
        this->id = i;
    }

    int id;
    struct Edge {
        Edge(Node *pNode1, ll i, ll w, Edge * back, int id) {
            this->to = pNode1;
            this->c = i;
            this->f = 0;
            this->back = back;
            this->w = w;
            this->id = id;
        }
        Edge * back;
        Node * to;
        ll c;
        ll f;
        ll w;
        int id;
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

void constructEdge(Node * u, Node * v, ll c, ll w, int id) {
    auto edge = new Node::Edge(v, c, w, nullptr, id);
    auto backEdge = new Node::Edge(u, 0, -w, edge, id);
    edge->back = backEdge;
    u->edges.push_back(edge);
    v->edges.push_back(backEdge);
}

void getPath(std::vector<Node::Edge *> & path, Node * node) {
    if (node->id == terminal->id) {
        return;
    }
    for (auto p : node->edges) {
        if (p->c == p->f && p->c != 0) {
            p->f = 0;
            p->back->f = 0;
            path.push_back(p);
            getPath(path, p->to);
            break;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, k;
    std::cin >> n >> m >> k;

    nodes_size = n;
    std::vector<Node *> nodes;
    std::vector<Node::Edge *> edges;
    nodes.reserve(nodes_size);

    for (int i = 0; i < nodes_size; ++i) {
        nodes.push_back(new Node(i));
    }

    start = nodes[0];
    terminal = nodes[nodes_size - 1];

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        constructEdge(nodes[--u], nodes[--v], 1, w, i);
        constructEdge(nodes[v], nodes[u], 1, w, i);
    }

    ll sum = 0;
    for (int i = 0; i < k; ++i)  {
        if (!pathExists()) {
            std::cout << -1;
            return 0;
        }
        ll s = dfs(terminal);

        for (Node * pNode = terminal; pNode->id != start->id; pNode = pNode->path->back->to) {
            pNode->path->f += s;
            pNode->path->back->f -= s;
            sum += pNode->path->w * s;
        }
    }

    std::cout << std::fixed << std::setprecision(5) << (double) sum / k << std::endl;

    for (int i = 0; i < k; ++i) {
        std::vector<Node::Edge *> path = {};
        getPath(path, start);
        std::cout << path.size() << " ";
        for (auto * e : path) {
            std::cout << e->id + 1 << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
