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

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Node *> A; A.reserve(n);
    std::vector<Node *> B; A.reserve(m);

    for (int i = 0; i < n; ++i) {
        A.push_back(new Node(i + 1));
    }
    for (int i = 0; i < m; ++i) {
        B.push_back(new Node(n + i + 1));
    }

    for (int i = 0; i < n; i++) {
        int j;
        while (true) {
            std::cin >> j;
            if (j == 0) {
                break;
            }
            auto * edge = new Node::Edge(A[i], B[j - 1]);
            A[i]->edges.push_back(edge);
        }
    }

    for (Node * v : A) {
        if (dfs(v)) {
            for (Node * u : A) {
                u->visit = false;
            }
        }
    }

    std::vector<std::pair<Node *, Node::Edge *>> vector;
    for (Node * v : B) {
        if (v->revert != nullptr) {
            vector.emplace_back(v, v->revert);
        }
    }

    std::cout << vector.size() << std::endl;

    for (auto p : vector) {
        std::cout << p.second->from->id << " " << (p.first->id - n) << std::endl;
    }

    return 0;
}