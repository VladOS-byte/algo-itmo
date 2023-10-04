#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int id = 0;
    int component = -1;
};

struct Edge {
    Node * from;
    Node * to;
    int cost;

    bool operator < (const Edge & edge) const
    {
        return cost != edge.cost && cost < edge.cost;
    }
};

bool comp (Edge * e, Edge * f) {
    return (*e < *f);
}

int get(std::vector<Node *> & nodes, int a) {
    int head = nodes[a]->component;
    while(nodes[head]->component != head) {
        head = nodes[head]->component;
    }
    int h;
    while(a != nodes[a]->component) {
        h = a;
        a = nodes[a]->component;
        nodes[h]->component = head;
    }
    return head;
}
void _union(std::vector<Node *> & nodes, int x, int y) {
    x = get(nodes, x);
    y = get(nodes, y);
    if (x == y) {
        return;
    }
    nodes[y]->component = x;
}

Edge * createEdge(Node * v, Node * u, int cost) {
    auto * edge = new Edge();
    edge->from = v;
    edge->to = u;
    edge->cost = cost;
    return edge;
}

int main() {
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    int n, m;
    std::cin >> n >> m;
    nodes.reserve(n);
    edges.reserve(m);

    for (int i = 0; i < n; ++i) {
        Node * node = new Node();
        node->id = i;
        node->component = i;
        nodes.push_back(node);
    }

    for (int i = 0; i < m; ++i) {
        int v, u, c;
        std::cin >> v >> u >> c;
        v--;
        u--;
        edges.push_back(createEdge(nodes[v], nodes[u], c));
    }

    std::sort(edges.begin(), edges.end(), comp);
    long long weight = 0;

    for (auto & edge : edges) {
        if (get(nodes, edge->from->component) != get(nodes, edge->to->component)) {
            weight += edge->cost;
            _union(nodes, edge->from->id, edge->to->id);
        }
    }

    std::cout << weight;

    return 0;
}
