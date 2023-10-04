#include <iostream>
#include <vector>

struct Node {
    int id;
    char visited = 0;
    std::vector<Node *> children{};
};

bool findCicle(Node * node) {
    node->visited = 1;
    bool answer = false;
    for (Node * child : node->children) {
        if (child->visited == 0) {
            answer |= findCicle(child);
        } else if (child->visited == 1) {
            return true;
        }
    }
    node->visited = 2;
    return answer;
}

void fillVisited(std::vector<Node *> & nodes) {
    for (auto & node : nodes) {
        node->visited = 0;
    }
}

bool hasCicle(std::vector<Node *> & nodes) {
    bool answer = false;
    for (auto & node : nodes) {
        if (node->visited != 2) {
            answer |= findCicle(node);
        }
    }
    return answer;
}


void dfs(std::vector<Node *> & vector, Node * pNode) {
    pNode->visited = 1;
    for (auto & child : pNode->children) {
        if (child->visited == 0) {
            dfs(vector, child);
        }
    }
    vector.push_back(pNode);
}

void printTopologicalSort(std::vector<Node *> & nodes) {
    fillVisited(nodes);
    if (hasCicle(nodes)) {
        std::cout << -1;
        return;
    }
    fillVisited(nodes);
    std::vector<Node *> answer;
    answer.reserve(nodes.size());
    for (auto & node : nodes) {
        if (node->visited != 1) {
            dfs(answer, node);
        }
    }
    for (int i = answer.size() - 1; i >= 0; --i) {
        std::cout << answer[i]->id << " ";
    }
}

int main() {
    std::vector<Node *> nodes;
    int m, n;
    std::cin >> n >> m;
    nodes.reserve(n);
    for (int i = 0; i < n; ++i) {
        Node * node = new Node();
        node->id = i + 1;
        nodes.push_back(node);
    }

    for (int i = 0; i < m; ++i) {
        int v, u;
        std::cin >> v >> u;
        v--;
        u--;
        nodes[v]->children.push_back(nodes[u]);
    }

    printTopologicalSort(nodes);

    return 0;
}
