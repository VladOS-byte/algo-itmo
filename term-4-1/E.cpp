#include<iostream>
#include<vector>

struct Node {
    int id;

    Node(int id) {
        this->id = id;
    }

    struct Edge {
        Node * from;
        Node * to;

        Edge(Node * from, Node * to) {
            this->from = from;
            this->to = to;
        }
    };
    bool visit = false;

    std::vector<Edge *> edges;
    Edge * revert = nullptr;
};

void revertEdge(Node::Edge * edge) {
    edge->to->revert = edge;
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

int n, m, a, b;
void addEdge(std::vector<std::vector<Node *>> & nodes, int i, int j, int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= m || nodes[i][j] == nullptr || nodes[x][y] == nullptr) {
        return;
    }
    nodes[i][j]->edges.push_back(new Node::Edge(nodes[i][j], nodes[x][y]));
}

int main() {
    std::cin >> n >> m >> a >> b;
    int size = 0;
    std::vector<std::vector<Node *>> emptyPlace;
    emptyPlace.reserve(n);

    std::vector<Node *> A;
    std::vector<Node *> B;

    for (int i = 0; i < n; i++) {
        std::vector<Node *> emptyPlacesRow;
        emptyPlacesRow.reserve(m);
        for (int j = 0; j < m; ++j) {
            char c;
            std::cin >> c;
            emptyPlacesRow.push_back(c == '*' ? new Node(size) : nullptr);
            size += c == '*' ? 1 : 0;
        }
        emptyPlace.push_back(emptyPlacesRow);
    }

    int sum = size * b;
    if (2 * b <= a) {
        std::cout << sum;
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (emptyPlace[i][j] != nullptr) {
                if ((j + (i % 2)) % 2 == 0) {
                    addEdge(emptyPlace, i, j, i, j - 1);
                    addEdge(emptyPlace, i, j, i, j + 1);
                    addEdge(emptyPlace, i, j, i - 1, j);
                    addEdge(emptyPlace, i, j, i + 1, j);
                    A.push_back(emptyPlace[i][j]);
                } else {
                    B.push_back(emptyPlace[i][j]);
                }
            }
        }
    }

    for (Node * v : A) {
        if (dfs(v)) {
            for (Node * u : A) {
                u->visit = false;
            }
        }
    }

    for (Node * v : B) {
        if (v->revert != nullptr) {
            sum = sum - 2 * b + a;
        }
    }

    std::cout << sum;

    return 0;
}
