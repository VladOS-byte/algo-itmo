#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

struct Node {
    int id;
    int cost;
    int rating = 0;

    Node(int id, int cost) {
        this->id = id;
        this->cost = cost;
    }

    struct Edge {
        Node * from;
        Node * to;
        bool deprecate = false;

        Edge(Node * from, Node * to) {
            this->from = from;
            this->to = to;
        }
    };
    bool visit = false;

    std::vector<Edge *> edges;
    Edge * revert = nullptr;
};

bool compareN (const Node * n1, const Node * n2) {
    return n1->cost == n2->cost ? n1->rating > n2->rating : n1->cost > n2->cost;
}

bool compareE (const Node::Edge * e1, const Node::Edge * e2) {
    return e1->from->cost + e1->to->cost > e2->from->cost + e2->to->cost;
}

bool compareP (const std::pair<int, int> n1, const std::pair<int, int> n2) {
    return n1.first > n2.first;
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
        if (edge->deprecate) {
            continue;
        }
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
        if (edge->deprecate) {
            continue;
        }
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
    
    int n, m, k, t;
    std::cin >> m >> k >> n;
    std::vector<Node *> A; A.reserve(m);
    std::vector<Node *> B; A.reserve(k);

    for (int i = 0; i < m; ++i) {
        A.push_back(new Node(i + 1, 1));
    }
    for (int i = 0; i < k; ++i) {
        B.push_back(new Node(m + i + 1, 1));
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) { 
            auto * edge = new Node::Edge(A[i], B[j]);
            A[i]->edges.push_back(edge);
        }
    }
    
    std::cerr << "cin OK 1";
    
    std::cin >> t;
    
    for (int i = 0; i < t; ++i) {
        int u, v;
        std::cin >> u >> v;
        A[u - 1]->edges[v - m - 1]->deprecate = true;
    }
    
    std::cerr << "cin OK";
    
    std::cin >> t;
    
    for (int i = 0; i < t; ++i) {
        int u;
        std::cin >> u;
        if (u > m) {
            B[u - m - 1]->cost = 2;
        } else {
            A[u - 1]->cost = 2;
        }
    }
    
    for (Node * v : A) {
        for (auto * edge : v->edges) {
            if (!edge->deprecate) {
                v->rating += edge->to->cost == 2 ? 1 : 0;
            }
        }
    }
    
    std::sort(A.begin(), A.end(), compareN);
    std::sort(B.begin(), B.end(), compareN);
    
    for (int i = 0; i < m; ++i) {
        std::sort(A[i]->edges.begin(), A[i]->edges.end(), compareE);
    }
    
    std::cerr << "sort OK";

    int r = 0;
    for (Node * v : A) {
        h = -1;
        c = -1;
        if (r < n) {
            dfs(v);
        }
        
        for (Node * u : A) {
            u->visit = false;
        }
        
        if (h != -1) {
            r++;
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
    
    std::cerr << "search OK";
    
    std::vector<std::pair<int, int>> vector;
    for (Node * v : B) {
        if (v->revert != nullptr) {
            v->revert->from->visit = true;
            v->visit = true;
            vector.push_back({v->revert->from->id, v->id});
        }
    }
    
    std::sort(vector.begin(), vector.end(), compareP);
    
    if (vector.size() != n) {
        std::cout << "NO";
        return 0;
    }
    
    for (Node * v : A) {
        if (v->cost == 2 && !v->visit) {
            std::cout << "NO";
            return 0;
        }
    }
    
    for (Node * v : B) {
        if (v->cost == 2 && !v->visit) {
            std::cout << "NO";
            return 0;
        }
    }

    std::cout << "YES" << std::endl;

    for (auto p : vector) {
        std::cout << p.first << " " << p.second << std::endl;
    }

    return 0;
}
