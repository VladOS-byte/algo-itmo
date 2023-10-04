#include<iostream>
#include<vector>
#include <queue>

struct Node {
    Node(int i) {
        this->id = i;
    }

    int id;
    int p = 0;
    struct Edge {
        Edge(Node *pNode1, int i, Edge * back) {
            this->to = pNode1;
            this->c = i;
            this->f = 0;
            this->back = back;
        }
        Edge * back;
        Node * to;
        int c;
        int f;
    };

    std::vector<Edge *> edges = {};
};

int n;
Node * terminal;
Node * start;
std::vector<int> levels;

bool pathExists(Node * node) {
    std::queue<Node *> nodes;
    nodes.push(node);
    levels = std::vector<int>(n, -1);
    levels[start->id] = 0;
    while (!nodes.empty()) {
        auto * n = nodes.front();
        nodes.pop();
        for (auto p : n->edges) {
            if (p->f < p->c && levels[p->to->id] == -1) {
                levels[p->to->id] = levels[n->id] + 1;
                nodes.push(p->to);
            }
        }
    }
    return levels[terminal->id] != -1;
}

int dfs(Node * node, int cMin) {
    if (node->id == terminal->id || cMin == 0) {
        return cMin;
    }
    for (; node->p < node->edges.size(); ++node->p)  {
        auto p = node->edges[node->p];
        if (p->f < p->c && levels[node->id] + 1 == levels[p->to->id]) {
            int d = dfs(p->to, std::min(p->c - p->f, cMin));
            if (d > 0) {
                p->f += d;
                p->back->f -= d;
                return d;
            }
        }
    }
    return 0;
}

std::vector<Node *> getPath(std::vector<Node *> & nodes, Node * node) {
    nodes.push_back(node);
    if (node->id == terminal->id) {
        return nodes;
    }
    for (auto p : node->edges) {
        if (p->c == p->f && p->c != 0) {
            p->f = 0;
            p->back->f = 0;
            getPath(nodes, p->to);
            break;
        }
    }
    return nodes;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int m, st, t;
    std::cin >> n >> m >> st >> t;

    std::vector<Node *> nodes;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        nodes.push_back(new Node(i));
    }
    st--; t--;
    terminal = nodes[t];
    start = nodes[st];

    for (int i = 0; i < m; ++i) {
        int u, v, c = 1;
        std::cin >> u >> v;
        u--; v--;
        auto * pEdge = new Node::Edge(nodes[u], 0, nullptr);
        auto * edge = new Node::Edge(nodes[v], c, pEdge);
        pEdge->back = edge;
        nodes[u]->edges.emplace_back(edge);
        nodes[v]->edges.emplace_back(pEdge);
    }

    int sum = 0;
    while (pathExists(start)) {
        int s;
        for (auto * node : nodes) {
            node->p = 0;
        }
        while ((s = dfs(start, INT32_MAX)) != 0) {
            sum += s;
        }
    }

    std::cout << (sum >= 2 ? "YES" : "NO") << std::endl;

    if (sum >= 2) {
        for (int i = 0; i < 2; ++i) {
            std::vector<Node *> path = std::vector<Node *>();
            for (auto * node : getPath(path, start)) {
                std::cout << (node->id + 1) << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
