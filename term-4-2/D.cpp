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

    bool visited = false;
    std::vector<Edge *> edges = {};
};

int nodes_size;
Node * terminal;
Node * start;
std::vector<int> levels;

bool pathExists(Node * node) {
    std::queue<Node *> nodes;
    nodes.push(node);
    levels = std::vector<int>(nodes_size, -1);
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
    node->visited = true;
    for (; node->p < node->edges.size(); ++node->p)  {
        auto p = node->edges[node->p];
        if (!p->to->visited && p->f < p->c && levels[node->id] + 1 == levels[p->to->id]) {
            int d = dfs(p->to, std::min(p->c - p->f, cMin));
            if (d > 0) {
                p->f += d;
                p->back->f -= d;
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
        if (p->c != p->f) {
            splitDfs(p->to);
        }
    }
}


void constructEdge(Node * u, Node * v, int c) {
    auto edge = new Node::Edge(v, c, nullptr);
    auto backEdge = new Node::Edge(u, 0, edge);
    edge->back = backEdge;
    u->edges.push_back(edge);
    v->edges.push_back(backEdge);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, st, t;
    std::scanf("%d %d", &n, &m);

    nodes_size = 2 * m * n;

    std::vector<Node *> nodes;
    nodes.reserve(nodes_size);

    for (int i = 0; i < nodes_size; ++i) {
        nodes.push_back(new Node(i));
    }

    std::vector<std::vector<char>> map = std::vector<std::vector<char>>();
    map.reserve(n);

    for (int i = 0; i < n; ++i) {
        std::vector<char> mmap = std::vector<char>();
        mmap.reserve(m);
        std::scanf("\n");
        for (int j = 0; j < m; ++j) {
            char c;
            std::scanf("%c", &c);
            mmap.push_back(c);
            int cent = INT32_MAX;
            bool flag = true;
            switch (c) {
                case '.':
                    cent = 1;
                case 'A':
                    start = cent == 1 ? start : nodes[2 * (i * m + j) + 1];
                    flag = false;
                case 'B':
                    terminal = flag ? nodes[2 * (i * m + j)] : terminal;
                case '-': {
                    constructEdge(nodes[2 * (i * m + j)], nodes[2 * (i * m + j) + 1], cent);
                    break;
                }
                default:
                    break;
            }

            if (i + 1 < n) {
                constructEdge(nodes[2 * (i * m + j) + 1], nodes[2 * ((i + 1) * m + j)], INT32_MAX);
            }
            if (i > 0) {
                constructEdge(nodes[2 * (i * m + j) + 1], nodes[2 * ((i - 1) * m + j)], INT32_MAX);
            }
            if (j + 1 < m) {
                constructEdge(nodes[2 * (i * m + j) + 1], nodes[2 * (i * m + (j + 1))], INT32_MAX);
            }
            if (j > 0) {
                constructEdge(nodes[2 * (i * m + j) + 1], nodes[2 * (i * m + (j - 1))], INT32_MAX);
            }
        }
        map.push_back(mmap);
    }

    long long sum = 0;
    while (pathExists(start)) {
        int s;
        for (auto * node : nodes) {
            node->p = 0;
        }
        while ((s = dfs(start, INT32_MAX)) != 0) {
            sum += s;
        }
    }

    splitDfs(start);

    if (sum >= INT32_MAX) {
        std::cout << -1;
        return 0;
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (nodes[2 * (i * m + j)]->visited != nodes[2 * (i * m + j) + 1]->visited && map[i][j] == '.') {
                map[i][j] = '+';
                count++;
            }
        }
    }

    std::cout << count << std::endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}
