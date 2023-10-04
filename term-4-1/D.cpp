#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

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

struct Place {
    int time;
    std::pair<int, int> coord;

    Place(int time, std::pair<int, int> coord) {
        this->time = time;
        this->coord = coord;
    }
};

int timeDistance(std::pair<int, int> coord1, std::pair<int, int> coord2, int u) {
    return sqrt((coord2.first - coord1.first) * (coord2.first - coord1.first) +
                (coord2.second - coord1.second) * (coord2.second - coord1.second)) * 60 / u;
}

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

bool invite(Node * node) {
    if (node->visit) {
        return false;
    }
    node->visit = true;
    if (node->revert != nullptr) {
        invite(node->revert->from);
    }
    return true;
}

int main() {
    int n, u;
    std::cin >> n >> u;
    std::vector<Node *> A;
    std::vector<Node *> B;
    std::vector<Place> places;
    std::vector<Node *> nodes;

    for (int i = 0; i < n; i++) {
        int h, m, x, y;
        char c;
        std::cin >> h >> c >> m >> x >> y;
        places.push_back({h * 60 + m, {x, y}});
        nodes.push_back(new Node(i));
    }

    std::sort(places.begin(), places.end(), [] (Place place1, Place place2) {
        return place1.time < place2.time;
    });

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (places[i].time + timeDistance(places[i].coord, places[j].coord, u) <= places[j].time) {
                nodes[i]->edges.push_back(new Node::Edge(nodes[i], nodes[j]));
            }
        }
    }

    for (Node * v : nodes) {
        dfs(v);
        for (Node * u : nodes) {
            u->visit = false;
        }
    }
    
    int count = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (invite(nodes[i])) {
            count++;
        }
    }
    std::cout << count;
    
    return 0;
}

