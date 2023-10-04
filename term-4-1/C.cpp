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
    bool isMarked = false;

    std::vector<Edge *> edges;
    Edge * revert = nullptr;
};

void revertEdge(Node::Edge * edge) {
    edge->to->revert = edge;
    edge->from->isMarked = true;
    edge->to->isMarked = true;
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

void invite(Node * node) {
    if (node->visit) {
        return;
    }
    node->visit = true;
    for (Node::Edge *edge : node->edges) {
        edge->to->visit = true;
        if (edge->to->revert != nullptr) {
            invite(edge->to->revert->from);
        }
    }
}

int main() {
    int n, m, k;

    std::cin >> k;

    for (int ir = 0; ir < k; ++ir) {
        std::cin >> n >> m;
        std::vector<Node *> A; A.reserve(n);
        std::vector<Node *> B; A.reserve(m);
        std::vector<std::vector<bool>> graph = std::vector<std::vector<bool>>(n, std::vector<bool>(m, true));

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
                graph[i][j - 1] = false;
            }
        }

        for (int i = 0; i < graph.size(); ++i) {
            for (int j = 0; j < graph[i].size(); ++j) {
                if (graph[i][j]) {
                    auto * edge = new Node::Edge(A[i], B[j]);
                    A[i]->edges.push_back(edge);
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

        for (Node * v : A) {
            v->visit = false;
        }

        for (Node * v : A) {
            if (!v->isMarked) {
                invite(v);
            }
        }

        std::vector<Node *> invitedA = {};
        for (Node * v : A) {
            if (v->visit) {
                invitedA.push_back(v);
            }
        }

        std::vector<Node *> invitedB = {};
        for (Node * v : B) {
            if (!v->visit) {
                invitedB.push_back(v);
            }
        }

        std::cout << invitedA.size() + invitedB.size() << std::endl;
        std::cout << invitedA.size() << " " << invitedB.size() << std::endl;
        for (Node * v : invitedA) {
            std::cout << v->id << " ";
        }
        std::cout << std::endl;
        for (Node * v : invitedB) {
            std::cout << v->id - n << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    return 0;
}