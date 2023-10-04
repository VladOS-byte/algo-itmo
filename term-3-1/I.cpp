#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Node {
    int id = 0;
    bool componentA = false;
    int minCost = INT32_MAX;

    struct Point {
        int x, y;
    };

    Point p;
};

double weight = 0;

void primeMST(std::vector<Node *> & nodes) {
    nodes[0]->minCost = 0;
    for (int i = 0; i < nodes.size(); ++i) {
        Node * v = nullptr;
        for (auto & node : nodes) {
            if (!node->componentA && (v == nullptr || node->minCost < v->minCost)) {
                v = node;
            }
        }
        v->componentA = true;
        
        for (auto & node : nodes) {
            if (!node->componentA) {
                int dist = (v->p.x - node->p.x) * (v->p.x - node->p.x) + (v->p.y - node->p.y) * (v->p.y - node->p.y);
                if (dist < node->minCost) {
                    node->minCost = dist;
                }
            }
        }
    }
}

int main() {
    std::vector<Node *> nodes;
    int n;
    std::cin >> n;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node * node = new Node();
        node->id = i;
        int x, y;
        std::cin >> x >> y;
        node->p.x = x;
        node->p.y = y;
        nodes.push_back(node);
    }

    primeMST(nodes);

    for (auto & node : nodes) {
//        std::cout << node->p.x << "," << node->p.y << ": " << sqrt(node->minCost) << std::endl;
        weight += sqrt(node->minCost);
    }
    
    printf("%.10f", weight);

    return 0;
}
