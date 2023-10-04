#include <iostream>
#include <vector>
#include <queue>
#include <map>

struct Node {
    int id;
    struct Edge {
        char letter;
        Node * to;
    };

    int h;
    Node * parent;
    Node * link;
    std::vector<Node *> linkBack;

    std::map<char, Edge *> edges;

    std::vector<int> determine;
    int left = INT32_MAX / 2;
    int right = -1;
};

int id = 1;
Node * head = new Node{0, 0, nullptr};

void buildDictionary(std::string & s, int num) {
     int h = 0;
     Node * node = head;
     while (h < s.length()) {
         if (node->edges.count(s[h] - 'a') == 0) {
             node->edges.insert({s[h] - 'a', new Node::Edge{s[h],new Node{id++, h, node}}});
         }
         node = node->edges.find(s[h] - 'a')->second->to;
         if (++h == s.length()) {
             node->determine.push_back(num);
         }
     }
}

Node * getLink(Node::Edge * edge) {
    Node * parent = edge->to->parent;
    char c = edge->letter;
    while (parent != head) {
        if (parent->link->edges.count(c - 'a') != 0) {
            return parent->link->edges.find(c - 'a')->second->to;
        }
        parent = parent->link;
    }
    return head;
}

void buildLinks() {
    head->link = head;
    std::queue<Node::Edge *> Q;
    for (auto & edge : head->edges) {
        Q.push(edge.second);
    }
    while (!Q.empty()) {
        auto & e = Q.front();
        Q.pop();
        e->to->link = getLink(e);
        e->to->link->linkBack.push_back(e->to);
        for (auto & edge : e->to->edges) {
            Q.push(edge.second);
        }
    }
}

void dfs2(Node * node) {
    for (auto & link : node->linkBack) {
        dfs2(link);
        if (link->right >= 0) {
            node->left = std::min(node->left, link->left + (link->h - node->h));
            node->right = std::max(node->right, link->right + (link->h - node->h));
        }
    }
}

void dfs(Node * node, std::vector<std::pair<int, int>> & exists) {
    for (int i : node->determine) {
        exists[i] = {node->left, node->right};
    }
    for (auto & edge : node->edges) {
        if (edge.second->to->right >= 0) {
            dfs(edge.second->to, exists);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    std::string s;
    std::string t;
    int k;
    size_t h = 0;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        std::cin >> s;
        h = std::max(h, s.size());
        buildDictionary(s, i);
    }

    buildLinks();

    std::cin >> t;
    t += char('z' + 1);
    Node * node = head;

    for (int i = 0; i < t.length(); ++i) {
        while (node != head && node->edges.count(t[i] - 'a') == 0) {
            node = node->link;
        }
        if (node->edges.count(t[i] - 'a') != 0) {
            node = node->edges.find(t[i] - 'a')->second->to;
        }
        node->left = std::min(node->left, i - node->h);
        node->right = std::max(node->right, i - node->h);
    }
    std::vector<std::pair<int, int>> exists(k, {-1, -1});
    dfs2(head);
    dfs(head, exists);

    for (auto & exist : exists) {
        std::cout << (exist.second == -1 ? -1 : exist.first) << " " << (exist.second) << std::endl;
    }
    return 0;
}