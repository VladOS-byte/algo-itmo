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

    int n;
    std::scanf("%d\n", &n);
    nodes_size = n + 2;

    std::vector<Node *> nodes;
    nodes.reserve(nodes_size);

    for (int i = 0; i < n; ++i) {
        nodes.push_back(new Node(i));
    }
    start = new Node(nodes.size());
    nodes.push_back(start);
    terminal = new Node(nodes.size());
    nodes.push_back(terminal);

    std::vector<std::vector<char>> map = std::vector<std::vector<char>>();
    map.reserve(n);
    std::vector<std::pair<int, int>> points = std::vector<std::pair<int, int>>(n, {0, 0});

    for (int i = 0; i < n; ++i) {
        std::vector<char> mmap = std::vector<char>();
        mmap.reserve(n);
        for (int j = 0; j < n; ++j) {
            char c;
            std::scanf("%c", &c);
            mmap.push_back(c);
            switch (c) {
                case 'L': {
                    points[i].first += 0;
                    break;
                }
                case 'l': {
                    points[i].first += 1;
                    break;
                }
                case 'w': {
                    points[i].first += 2;
                    break;
                }
                case 'W': {
                    points[i].first += 3;
                    break;
                }
                case '.': {
                    if (i < j) {
                        points[i].second += 3;
                        constructEdge(nodes[i], nodes[j], 3);
                    }
                    break;
                }
                default:
                    break;
            }
        }
        std::scanf("\n");
        map.push_back(mmap);
    }

    for (int i = 0; i < n; ++i) {
        int p;
        std::scanf("%d", &p);
        constructEdge(start, nodes[i], points[i].second);
        constructEdge(nodes[i], terminal, p - points[i].first);
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

    for (int i = 0; i < n; ++i) {
        for (auto * e : nodes[i]->edges) {
            if (map[i][e->to->id] == '.' && e->to->id > i) {
                switch (e->f) {
                    case 0: {
                        map[i][e->to->id] = 'W';
                        map[e->to->id][i] = 'L';
                        break;
                    }
                    case 1: {
                        map[i][e->to->id] = 'w';
                        map[e->to->id][i] = 'l';
                        break;
                    }
                    case 2: {
                        map[i][e->to->id] = 'l';
                        map[e->to->id][i] = 'w';
                        break;
                    }
                    case 3: {
                        map[i][e->to->id] = 'L';
                        map[e->to->id][i] = 'W';
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}
