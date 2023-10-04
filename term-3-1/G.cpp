#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

struct Node {
    std::string id;
    int time = INT32_MAX;
    int up = INT32_MAX;
    int component = INT32_MIN;
    int numInSort = -1;

    std::vector<Node *> edges{};
    std::vector<Node *> back{};
};

std::vector<Node *> sorted{};

void topSort(Node * node) {
    node->component = -1;
    for (auto & to : node->edges) {
        if (to->component == INT32_MIN) {
            topSort(to);
        }
    }
    node->numInSort = sorted.size();
    sorted.push_back(node);
}

void fillComponents(Node * node, int comp) {
    node->component = comp;
    for (auto & to : node->back) {
        if (to->component == -1) {
            fillComponents(to, comp);
        }
    }
}

int main() {
    std::map<std::string, int> nodesMap;
    std::vector<Node *> nodes;
    int n, m;
    std::cin >> n >> m;
    nodes.reserve(n);

    for (int i = 0; i < n; ++i) {
        Node * node = new Node();
        Node * notNode = new Node();
        std::string name;
        std::cin >> name;
        node->id = '+' + name;
        notNode->id = '-' + name;
        nodesMap.insert({name, i});
        nodes.push_back(node);
        nodes.push_back(notNode);
    }

    for (int i = 0; i < m; ++i) {
        char s1[12], s2[12];
        char c1, c2;
        std::scanf("\n%c%s => %c%s", &c1, &s1, &c2, &s2);
        Node * v = nodes[2 * nodesMap.find(s1)->second + (c1 == '-' ? 1 : 0)];
        Node * nv = nodes[2 * nodesMap.find(s1)->second + (c1 == '-' ? 0 : 1)];
        Node * u = nodes[2 * nodesMap.find(s2)->second + (c2 == '-' ? 1 : 0)];
        Node * nu = nodes[2 * nodesMap.find(s2)->second + (c2 == '-' ? 0 : 1)];
        v->edges.push_back(u);
        nv->back.push_back(nu);
        u->back.push_back(v);
        nu->edges.push_back(nv);
    }

    for (auto & node : nodes) {
        if (node->component == INT32_MIN) {
            topSort(node);
        }
    }

    int comp = 0;
    while (!sorted.empty()) {
        Node * node = sorted.back();
        if (node->component == -1) {
            fillComponents(node, comp++);
        }
        sorted.pop_back();
    }

    std::vector<std::string> answer{};

    for (int i = 0; i < nodes.size(); i += 2) {
        if (nodes[i]->component > nodes[i + 1]->component) {
            answer.push_back(nodes[i]->id.substr(1));
        }
    }

    if (answer.empty()) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << answer.size() << std::endl;
    }

    for (auto a : answer) {
        std::cout << a << std::endl;
    }

    return 0;
}
