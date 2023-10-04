#include <iostream>
#include <vector>

using namespace std;

struct Node {
    pair<int, int> value;
    int hight;
    int weight;
    bool hasZero;
    Node * left;
    Node * right;
    Node * parent;
    void culc() {
        this->hight = max(this->right == nullptr ? -1 : this->right->hight,
                          this->left == nullptr ? -1 : this->left->hight) + 1;
        this->weight = (this->right == nullptr ? 0 : this->right->weight) +
                       (this->left == nullptr ? 0 : this->left->weight) +
                       1;
        this->hasZero = (this->right == nullptr ? false : this->right->hasZero) ||
                        (this->left == nullptr ? false : this->left->hasZero) ||
                        this->value.first == 0;
    }
    void change(Node * node1, Node * node2) {
        if (this->left == node1) {
            this->left = node2;
        }
        if (this->right == node1) {
            this->right = node2;
        }
        if (node2 != nullptr) {
            node2->parent = this;
            node2->culc();
        }
        this->culc();
    }
    Node(Node * parent, pair<int, int> value) {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = parent;
        this->culc();
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
    node->culc();
    n->culc();
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

void rotate(Node * node) {
    node->culc();
    while(node != head) {
        Node * n = node;
        node = node->parent;
        node->culc();
        if ((node->left == nullptr ? -1 : node->left->hight) -
            (node->right == nullptr ? -1 : node->right->hight) == 2) {
            if ((n->right == nullptr ? -1 : n->right->hight) -
                (n->left == nullptr ? -1 : n->left->hight) == 1) {
                bigRotate(node, 'L');
            } else {
                rotateS(node, 'L');
            }
        } else if ((node->right == nullptr ? -1 : node->right->hight) -
                   (node->left == nullptr ? -1 : node->left->hight) == 2) {
            if ((n->left == nullptr ? -1 : n->left->hight) -
                (n->right == nullptr ? -1 : n->right->hight) == 1) {
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

Node * next0(Node * node) {
    while (node->right != nullptr && node->right->hasZero) {
        node = node->right;
        while(node->left != nullptr && node->left->hasZero) {
            node = node->left;
        }
        if (node->value.first == 0) {
            return node;
        }
    }
    Node * n = node->parent;
    while (n != nullptr && node == n->right) {
        node = n;
        n = n->parent;
    }
    if (n == nullptr) return nullptr;
    if (n->value.first == 0) {
        return n;
    }
    return next0(n);
}

void remove(Node * node) {
    if (node->value.first == 0) {
        return;
    }
    node = next0(node);
    if (node != nullptr) {
        if (node->left == nullptr) {
            if (node->right != nullptr) node->right->parent = node->parent;
            if (node->parent != nullptr) {
                if (node->parent->left == node) {
                    node->parent->left = node->right;
                } else {
                    node->parent->right = node->right;
                }
                node = node->parent;
            } else {
                head = node->right;
                node = head;
            }
        } else {
            Node * n = node->left;
            while (n->right != nullptr) {
                n = n->right;
            }
            node->value = n->value;
            if (n->parent->right == n) {
                n->parent->right = n->left;
            } else {
                n->parent->left = n->left;
            }
            if (n->left != nullptr) n->left->parent = n->parent;
            node = n->parent;
        }
        rotate(node);
    }
}

void insert(pair<int, int> value, int weight) {
    if (head == nullptr) {
        head = new Node(nullptr, value);
        return;
    }
    Node * node = head;
    while (node != nullptr) {
        int wl = (node->left == nullptr ? 0 : node->left->weight);
        int wr = (node->right == nullptr ? 0 : node->right->weight);
        if (weight == wl + 1 && node->value.first == 0) {
            node->value = value;
            break;
        }
        if (weight > wl + 1) {
            if (wr == 0) {
                if (node->value.first == 0 && value.first != 0 && weight == node->weight) {
                    node->value = value;
                } else {
                    node->right = new Node(node, value);
                    remove(node->right);
                }
                break;
            }
            weight -= wl + 1;
            node = node->right;
        } else {
            if (wl == 0) {
                if (node->value.first == 0 && value.first != 0 && weight == node->weight) {
                    node->value = value;
                } else {
                    node->left = new Node(node, value);
                    remove(node->left);
                }
                break;
            }
            node = node->left;
        }
    }
    rotate(node);
}

Node * next(Node * node) {
    if (node->right != nullptr) {
        node = node->right;
        while(node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    Node * n = node->parent;
    while (n != nullptr && node == n->right) {
        node = n;
        n = n->parent;
    }
    return n;
}

void printKeys() {
    Node * node = head;
    int expect = 1;
    vector<int> v(0);
    while (node->left != nullptr) {
        node = node->left;
    }
    do {
        if (node->value.first == 0) {
            node = next(node);
        } else if (node->value.first <= expect) {
            v.push_back(node->value.second);
            node = next(node);
            expect++;
        } else {
            while (node->value.first > expect) {
                v.push_back(0);
                expect++;
            }
        }
    } while (node != nullptr);
    cout << v.size() << endl;
    for (int i : v) {
        cout << i << " ";
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        insert(pair<int, int>(0, 0), 0);
    }
    for (int i = 1; i <= n; ++i) {
        int key;
        cin >> key;
        insert(pair<int, int>(key, i), key);
    }
    printKeys();
    return 0;
}