#include <iostream>
#define ll long long
using namespace std;

struct Node {
    pair<ll, ll> value;
    int height;
    Node * left;
    Node * right;
    Node * parent;
    Node(Node * parent, pair<ll, ll> value) {
        this->value = value;
        this->height = 0;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = parent;
    }
};

Node * head = nullptr;

void rotateS(Node * node, char mode) {
    Node * n;
    if (mode == 'L') {
        n = node->left;
        if (n == nullptr) return;
        node->left = n->right;
        if (node->left != nullptr) node->left->parent = node;
        n->right = node;
    } else {
        n = node->right;
        if (n == nullptr) return;
        node->right = n->left;
        if (node->right != nullptr) node->right->parent = node;
        n->left = node;
    }
    node->value.second = (node->right == nullptr ? 0 : node->right->value.second) +
                         (node->left == nullptr ? 0 : node->left->value.second) +
                         node->value.first;
    node->height = max(node->right == nullptr ? -1 : node->right->height,
                       node->left == nullptr ? -1 : node->left->height) + 1;
    n->value.second = (n->right == nullptr ? 0 : n->right->value.second) +
                        (n->left == nullptr ? 0 : n->left->value.second) +
                        n->value.first;
    n->height = max(n->right == nullptr ? -1 : n->right->height,
                    n->left == nullptr ? -1 : n->left->height) + 1;
    if (node->parent != nullptr) {
        if (node->parent->left == node) {
            node->parent->left = n;
        } else {
            node->parent->right = n;
        }
    } else {
        head = n;
    }
    n->parent = node->parent;
    node->parent = n;
}

void bigRotate(Node * node, char mode) {
    if (mode == 'L' || mode == 'R') {
        mode == 'L' ? rotateS(node->left, 'R') : rotateS(node->right, 'L');
        rotateS(node, mode);
    }
}

void insert(Node * node, ll value) {
    if (value == node->value.first) {
        return;
    }
    if (value < node->value.first) {
        if (node->left != nullptr) {
            return insert(node->left, value);
        } else {
            node->left = new Node(node, * new pair<ll, ll> (value, value));
        }
    } else {
        if (node->right != nullptr) {
            return insert(node->right, value);
        } else {
            node->right = new Node(node, * new pair<ll, ll> (value, value));
        }
    }
    node->value.second = (node->right == nullptr ? 0 : node->right->value.second) +
                            (node->left == nullptr ? 0 : node->left->value.second) +
                            node->value.first;
    node->height = max(node->right == nullptr ? -1 : node->right->height,
                       node->left == nullptr ? -1 : node->left->height) + 1;
    while(node != head) {
        Node * n = node;
        node = node->parent;
        node->value.second = (node->right == nullptr ? 0 : node->right->value.second) +
                                (node->left == nullptr ? 0 : node->left->value.second) +
                                node->value.first;
        node->height = max(node->right == nullptr ? -1 : node->right->height,
                           node->left == nullptr ? -1 : node->left->height) + 1;
        if ((node->left == nullptr ? -1 : node->left->height) -
            (node->right == nullptr ? -1 : node->right->height) == 2) {
            if ((n->right == nullptr ? -1 : n->right->height) -
                (n->left == nullptr ? -1 : n->left->height) == 1) {
                bigRotate(node, 'L');
            } else {
                rotateS(node, 'L');
            }
        } else if ((node->right == nullptr ? -1 : node->right->height) -
                   (node->left == nullptr ? -1 : node->left->height) == 2) {
            if ((n->left == nullptr ? -1 : n->left->height) -
                (n->right == nullptr ? -1 : n->right->height) == 1) {
                bigRotate(node, 'R');
            } else {
                rotateS(node, 'R');
            }
        }
        if (n->parent != node) {
            node = node->parent;
        }
    }
}

ll sum(ll l, ll r) {
    if (head == nullptr) {
        return 0;
    }
    ll result = head->value.second;
    Node * node = head;
    while (node != nullptr) {
        if (node->value.first > l) {
            node = node->left;
        } else if (node->value.first < l) {
            result -= node->value.first + (node->left == nullptr ? 0 : node->left->value.second);
            node = node->right;
        } else {
            result -= (node->left == nullptr ? 0 : node->left->value.second);
            break;
        }
    }
    node = head;
    while (node != nullptr) {
        if (node->value.first < r) {
            node = node->right;
        } else if (node->value.first > r) {
            result -= node->value.first + (node->right == nullptr ? 0 : node->right->value.second);
            node = node->left;
        } else {
            result -= (node->right == nullptr ? 0 : node->right->value.second);
            break;
        }
    }
    return result;
}

int main() {
    std::string command;
    ll n, y = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> command;
        if (command == "+") {
            ll key;
            cin >> key;
            key = (key + y) % (1000000000);
            y = 0;
            if (head == nullptr) {
                head = new Node(nullptr, * new pair<ll, ll> (key, key));
            } else {
                insert(head, key);
            }
        } else if (command == "?") {
            ll key1, key2;
            cin >> key1 >> key2;
            y = sum(key1, key2);
            cout << y << endl;
        }
    }
    return 0;
}