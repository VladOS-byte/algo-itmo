#include <iostream>
#include <vector>

struct Node{
    int value;
    int h;
    std::vector<Node *> parents;
    std::vector<Node *> childs;
    std::vector<Node *> links;
    Node * use;
};

int c;

void dfs(Node * node) {
    while (!node->links.empty()) {
        Node * link = node->links.back();
        if (node->parents.empty() || node->parents[0] != link) {
            link->parents.push_back(node);
            node->childs.push_back(link);
            dfs(link);
        }
        node->links.pop_back();
    }
}

std::vector<Node *> ps;

void dfsPs(Node * node) {
    for (int i = 1; (1 << i) <= ps.size(); ++i) {
        node->parents.push_back(ps[ps.size() - (1 << i)]);
    }
    ps.push_back(node);
    for (Node * child : node->childs) {
        child->h = node->h + 1;
        dfsPs(child);
    }
    ps.pop_back();
}

Node * lca(Node * u, Node * v) {
    if (u->h < v->h) {
        std::swap(u, v);
    }
    while (u->h != v->h) {
        int i = 0;
        int k = u->h - v->h;
        while ((1 << i) <= k) {
            i++;
        }
        u = u->parents[i - 1];
    }
    if (u->value == v->value) {
        return u;
    }
    while (u->parents[0]->value != v->parents[0]->value) {
        int k = 0;
        while (u->parents.size() != k && u->parents[k]->value != v->parents[k]->value) {
            k++;
        }
        u = u->parents[k - 1];

        v = v->parents[k - 1];
    }
    return u->parents[0];
}

void expo(Node * u, Node * v) {
    while (u->h > v->h) {
        while (u->h > v->h && u->use != nullptr) {
            u = u->use;
        }
        while (u->h > v->h && u->use == nullptr) {
            u->use = v;
            c--;
            u = u->parents[0];
        }
    }
}

int main() {
    int n, m;
    std::cin >> n;
    std::vector<Node *> nodes;
    nodes.reserve(n);
    c = n - 1;

    for (int i = 1; i <= n; ++i) {
        nodes.push_back(new Node{i, 0, {}, {}, {}, nullptr});
    }

    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        nodes[v - 1]->links.push_back(nodes[u - 1]);
        nodes[u - 1]->links.push_back(nodes[v - 1]);
    }

    Node * head = nodes[0];
    for (Node * node : nodes) {
        if (node->links.size() > head->links.size()) {
            head = node;
        }
    }

    dfs(head);

    dfsPs(head);

    std::cin >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        Node * l = lca(nodes[u - 1], nodes[v - 1]);
        expo(nodes[u - 1], l);
        expo(nodes[v - 1], l);
    }

    std::cout << c;

    return 0;
}

