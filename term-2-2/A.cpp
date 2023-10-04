#include <iostream>

using namespace std;

struct Node {
    int value;
    int height;
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
            node2->height = max(node2->right == nullptr ? -1 : node2->right->height,
                                node2->left == nullptr ? -1 : node2->left->height) + 1;
        }
        this->height = max(this->right == nullptr ? -1 : this->right->height,
                        this->left == nullptr ? -1 : this->left->height) + 1;
    }
    Node(Node * parent, int value) {
        this->value = value;
        this->height = 0;
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
    node->height = max(node->right == nullptr ? -1 : node->right->height,
                       node->left == nullptr ? -1 : node->left->height) + 1;
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
    node->height = max(node->right == nullptr ? -1 : node->right->height,
                       node->left == nullptr ? -1 : node->left->height) + 1;
    while(node != head) {
        Node * n = node;
        node = node->parent;
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
        } else if ((node->right == nullptr ? -1 : node->right->height) -
                   (node->left == nullptr ? -1 : node->left->height) == 0) {
            return;
        }
        if (n->parent != node) {
            node = node->parent;
        }
    }
}

void remove(Node * node, int value) {
    node = search(node, value);
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
            if ((node->left == nullptr ? -1 : node->left->height) -
                (node->right == nullptr ? -1 : node->right->height) == 1) {
                bigRotate(node, 'R');
            } else {
                rotateS(node, 'R');
            }
        } else if ((node->right == nullptr ? -1 : node->right->height) -
                   (node->left == nullptr ? -1 : node->left->height) == 0) {
            return;
        }
        if (n->parent != node) {
            node = node->parent;
        }
    }
}

std::string contains(Node * node, int value) {
    Node * tmp = search(node, value);
    return tmp != nullptr && tmp->value == value ? "true" : "false";
}

Node * next(Node * node, int value) {
    node = search(node, value);
    if (node == nullptr) {
        return nullptr;
    }
    if (node->value > value) {
        return node;
    }
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

Node * prev(Node * node, int value) {
    node = search(node, value);
    if (node == nullptr) {
        return nullptr;
    }
    if (node->value < value) {
        return node;
    }
    if (node->left != nullptr) {
        node = node->left;
        while(node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
    Node * n = node->parent;
    while (n != nullptr && node == n->left) {
        node = n;
        n = n->parent;
    }
    return n;
}

int doCommand(std::string command, int key) {
    if (command == "insert") {
        if (head == nullptr) {
            head = new Node(nullptr, key);
        } else {
            insert(head, key);
        }
    } else if (command == "delete") {
        remove(head, key);
    } else if (command == "exists") {
        cout << contains(head, key)  << endl;
    } else if (command == "prev") {
        Node * tmp = prev(head, key);
        cout << (tmp == nullptr ? "none" : to_string(tmp->value)) << endl;
    } else if (command == "next") {
        Node * tmp = next(head, key);
        cout << (tmp == nullptr ? "none" : to_string(tmp->value)) << endl;
    }
    return 0;
}

int main() {
    std::string command;
    int key;
    while (cin >> command) {
        cin >> key;
        doCommand(command, key);
    }
    return 0;
}