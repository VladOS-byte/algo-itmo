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
        Edge(Node *pNode, Node *pNode1, int i) {
            this->from = pNode;
            this->to = pNode1;
            this->c = i;
            this->f = 0;
        }

        Node * from;
        Node * to;
        int c;
        int f;
    };

    bool visited = false;
    std::vector<std::pair<Edge *, Edge *>> edges = {};
};

Node * terminal;
std::vector<int> levels;

bool pathExists(Node * node) {
    std::queue<Node *> nodes;
    nodes.push(node);
    levels = std::vector<int>(terminal->id + 1, -1);
    levels[0] = 0;
    while (!nodes.empty()) {
        auto * n = nodes.front();
        nodes.pop();
        for (auto p : n->edges) {
            if (p.first->f < p.first->c && levels[p.first->to->id] == -1) {
                levels[p.first->to->id] = levels[n->id] + 1;
                nodes.push(p.first->to);
            }
        }
    }
    return levels[terminal->id] != -1;
}

int dfs(Node * node, int cMin) {
    if (node->id == terminal->id || cMin == 0) {
        return cMin;
    }
    node->visited = true;
    for (; node->p < node->edges.size(); ++node->p)  {
        auto p = node->edges[node->p];
        if (!p.first->to->visited && p.first->f < p.first->c && levels[node->id] + 1 == levels[p.first->to->id]) {
            int d = dfs(p.first->to, std::min(p.first->c - p.first->f, cMin));
            if (d > 0) {
                p.first->f += d;
                p.second->f -= d;
                node->visited = false;
                return d;
            }
        }
    }
    node->visited = false;
    return 0;
}

void splitDfs(Node * node) {
    if (node->visited) {
        return;
    }
    node->visited = true;
    for (auto p : node->edges) {
        if (p.first->c != p.first->f && p.second->c != p.second->f) {
            splitDfs(p.first->to);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int m, n;
    std::cin >> n >> m;

    std::vector<Node *> nodes;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        nodes.push_back(new Node(i));
    }

    terminal = nodes.back();

    std::vector<Node::Edge *> edges;
    edges.reserve(m);

    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        u--; v--;
        auto * edge = new Node::Edge(nodes[u], nodes[v], c);
        auto * pEdge = new Node::Edge(nodes[v], nodes[u], c);
        nodes[u]->edges.emplace_back(edge, pEdge);
        nodes[v]->edges.emplace_back(pEdge, edge);
        edges.push_back(edge);
    }

    long long sum = 0;
    while (pathExists(nodes[0])) {
//        int s;
        for (auto * node : nodes) {
            node->p = 0;
        }
        while (dfs(nodes[0], INT32_MAX) != 0) {
//            sum += s;
        }
    }

    splitDfs(nodes[0]);

//    std::cout << sum << std::endl;
    std::vector<int> ans;
    for (int i = 0; i < edges.size(); ++i) {
        if (edges[i]->from->visited != edges[i]->to->visited) {
            ans.push_back(i + 1);
            sum += edges[i]->c;
        }
    }

    std::cout << ans.size() << " " << sum << std::endl;
    for (int edge : ans) {
        std::cout << edge << " ";
    }

    return 0;
}