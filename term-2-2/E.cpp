#include <iostream>

using namespace std;

struct Node {
    int value;
    int weight;
    int hight;
    Node * left;
    Node * right;
    Node * parent;
    void change(Node * node1, Node * node2) {
        if (this->left == node1) {
            this->left = node2;
        }
        if (this->right == node1) {
            this->right = node2;
        }
        if (node2 != nullptr) {
            node2->parent = this;
            node2->hight = max(node2->right == nullptr ? -1 : node2->right->hight,
                                node2->left == nullptr ? -1 : node2->left->hight) + 1;
            node2->weight = (node2->right == nullptr ? 0 : node2->right->weight) +
                    (node2->left == nullptr ? 0 : node2->left->weight) + 1;
        }
        this->hight = max(this->right == nullptr ? -1 : this->right->hight,
                        this->left == nullptr ? -1 : this->left->hight) + 1;
        this->weight = (this->right == nullptr ? 0 : this->right->weight) +
                (this->left == nullptr ? 0 : this->left->weight) + 1;
    }
    Node(Node * parent, int value) {
        this->value = value;
        this->hight = 0;
        this->weight = 1;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = parent;
    }
};

Node * head = nullptr;

Node * search(Node * node, int value) {
    if (node == nullptr) {
        return nullptr;
    }
    if (value == node->value) {
        return node;
    }
    Node * tmp;
    if (value < node->value) {
        tmp = search(node->left, value);
    } else {
        tmp = search(node->right, value);
    }
    return tmp == nullptr ? node : tmp;
}

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
    node->hight = max(node->right == nullptr ? -1 : node->right->hight,
                       node->left == nullptr ? -1 : node->left->hight) + 1;
    node->weight = (node->right == nullptr ? 0 : node->right->weight) + 
            (node->left == nullptr ? 0 : node->left->weight) + 1;
    n->hight = max(n->right == nullptr ? -1 : n->right->hight,
                    n->left == nullptr ? -1 : n->left->hight) + 1;
    n->weight = (n->right == nullptr ? 0 : n->right->weight) +
                   (n->left == nullptr ? 0 : n->left->weight) + 1;
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

void insert(Node * node, int value) {
    if (value == node->value) {
        return;
    }
    if (value < node->value) {
        if (node->left != nullptr) {
            return insert(node->left, value);
        } else {
            node->left = new Node(node, value);
        }
    } else {
        if (node->right != nullptr) {
            return insert(node->right, value);
        } else {
            node->right = new Node(node, value);
        }
    }
    node->hight = max(node->right == nullptr ? -1 : node->right->hight,
                       node->left == nullptr ? -1 : node->left->hight) + 1;
    node->weight = (node->right == nullptr ? 0 : node->right->weight) +
            (node->left == nullptr ? 0 : node->left->weight) + 1;
    while(node != head) {
        Node * n = node;
        node = node->parent;
        node->hight = max(node->right == nullptr ? -1 : node->right->hight,
                           node->left == nullptr ? -1 : node->left->hight) + 1;
        node->weight = (node->right == nullptr ? 0 : node->right->weight) +
                       (node->left == nullptr ? 0 : node->left->weight) + 1;
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

void remove(int value) {
    Node * node = search(head, value);
    if (node == nullptr || value != node->value) {
        return;
    }
    if (node->left == nullptr) {
        if (node == head) {
            head = node->right;
            if (head != nullptr) head->parent = nullptr;
            return;
        } else {
            node->parent->change(node, node->right);
            if (node->parent->left != nullptr) {
                node = node->parent->left;
            } else {
                node = node->parent;
            }
        }
    } else {
        Node * n = node->left;
        while (n->right != nullptr) {
            n = n->right;
        }
        n->parent->change(n, n->left);
        node->value = n->value;
        node = n;
    }
    while(node != head) {
        Node * n = node;
        node = node->parent;
        node->hight = max(node->right == nullptr ? -1 : node->right->hight,
                           node->left == nullptr ? -1 : node->left->hight) + 1;
        node->weight = (node->right == nullptr ? 0 : node->right->weight) +
                       (node->left == nullptr ? 0 : node->left->weight) + 1;
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
            if ((node->left == nullptr ? -1 : node->left->hight) -
                (node->right == nullptr ? -1 : node->right->hight) == 1) {
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

int getKMax(int k) {
    Node * node = head;
    while (k > 0 && node != nullptr) {
        if (k > (node->right == nullptr ? 0 : node->right->weight) + 1) {
            k -= (node->right == nullptr ? 0 : node->right->weight) + 1;
            node = node->left;
        } else if (k < (node->right == nullptr ? 0 : node->right->weight) + 1) {
            node = node->right;
        } else {
            return node->value;
        }
    }
    return 0;
}

void doCommand(std::string command, int key) {
    if (command == "+1" || command == "1") {
        if (head == nullptr) {
            head = new Node(nullptr, key);
        } else {
            insert(head, key);
        }
    } else if (command == "-1") {
        remove(key);
    } else if (command == "0") {
        cout << getKMax(key) << endl;
    }
}

int main() {
    std::string command;
    int key, n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> command >> key;
        doCommand(command, key);
    }
    return 0;
}