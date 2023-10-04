#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

struct Node {
    int id;
    int cost;

    Node(int id, int cost) {
        this->id = id;
        this->cost = cost;
    }

    struct Edge {
        Node * from;
        Node * to;
        int id;

        Edge(Node * from, Node * to, int id) {
            this->from = from;
            this->to = to;
            this->id = id;
        }
    };
    bool visit = false;

    std::vector<Edge *> edges;
    Edge * revert = nullptr;
};

bool compareN (const Node * n1, const Node * n2) {
    return n1->cost > n2->cost;
}

bool compareE (const Node::Edge * e1, const Node::Edge * e2) {
    return e1->from->cost + e1->to->cost > e2->from->cost + e2->to->cost;
}

void revertEdge(Node::Edge * edge) {
    edge->to->revert = edge;
}

int h, c;

bool dfs(Node * node) {
    if (node->visit) {
        return false;
    }
    
    node->visit = true;
    
    for (auto edge : node->edges) {
        if (edge->to->revert == nullptr) {
            if (edge->to->cost > c) {
                h = edge->to->id;
                c = edge->to->cost;
            }
            return true;
        } 
        
        dfs(edge->to->revert->from);
    }
    
    return false;
}

std::stack<Node::Edge *> S = {};

bool dfs2(Node * node) {
    if (node->visit) {
        return false;
    }
    
    node->visit = true;
    
    for (auto edge : node->edges) {
        S.push(edge);
        if (edge->to->revert == nullptr) {
            if (edge->to->id == h) {
                return true;
            }
            S.pop();
            return false;
        } else if (dfs2(edge->to->revert->from)) {
            return true;
        }
        S.pop();
    }
    
    return false;
}

int main() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    int n, m, e;
    std::cin >> n >> m >> e;
    std::vector<Node *> A; A.reserve(n);
    std::vector<Node *> B; A.reserve(m);

    for (int i = 0; i < n; ++i) {
        int j;
        std::cin >> j;
        A.push_back(new Node(i + 1, j));
    }
    for (int i = 0; i < m; ++i) {
        int j;
        std::cin >> j;
        B.push_back(new Node(n + i + 1, j));
    }

    for (int i = 0; i < e; i++) {
        int j, k;
        std::cin >> j >> k;
        auto * edge = new Node::Edge(A[j - 1], B[k - 1], i + 1);
        A[j - 1]->edges.push_back(edge);
    }
    
    std::sort(A.begin(), A.end(), compareN);
    
    for (int i = 0; i < n; ++i) {
        std::sort(A[i]->edges.begin(), A[i]->edges.end(), compareE);
    }

    for (Node * v : A) {
        h = -1;
        c = -1;
        dfs(v); 
        
        for (Node * u : A) {
            u->visit = false;
        }
        
        if (h != -1) {
            dfs2(v);
            
            while (!S.empty()) {
                revertEdge(S.top());
                S.pop();
            }
            
            for (Node * u : A) {
                u->visit = false;
            }
        }
    }

    int weight = 0;
    std::vector<int> vector;
    for (Node * v : B) {
        if (v->revert != nullptr) {
            weight += v->cost + v->revert->from->cost;
            vector.emplace_back(v->revert->id);
        }
    }
    
    std::sort(vector.begin(), vector.end());

    std::cout << weight << std::endl << vector.size() << std::endl;

    for (int p : vector) {
        std::cout << p << " ";
    }

    return 0;
}
