#include <iostream>

using namespace std;

struct Node {
    int sum;
    int set;
    int min;
    bool create;
    Node *l, *r, *parent;
};

Node head = {1 << 31, 1 << 31, 1 << 31, false, nullptr, nullptr, nullptr};

void lazy_build(Node * node) {
    node->l = new Node; node->l->parent = node; node->l->create = false;
    node->l->sum = 0; node->l->min = 0; node->l->set = (1 << 31);
    node->r = new Node; node->r->parent = node; node->r->create = false;
    node->r->sum = 0; node->r->min = 0; node->r->set = (1 << 31);
}

void propogate(Node * node) {
    if (!node->create) {
        lazy_build(node);
        node->create = true;
    }
    if (node->set != (1 << 31)) {
        node->l->set = node->set / 2;
        node->r->set = node->set / 2;
        node->l->min = node->l->set;
        node->r->min = node->r->set;
        node->l->sum = node->l->set;
        node->r->sum = node->r->set;
        node->sum = node->set;
        node->min = node->sum;
        node->set = 1 << 31;
    }
}

void lazy_propogate(Node * node, int left, int right) {
    if (right - left > 1) {
        propogate(node);
    }
}

void upgrate(Node * node) {
    if (node->parent != nullptr) {
        do {
            node = node->parent;
            node->sum = node->l->sum + node->r->sum;
            node->min = max(node->l->min, node->r->min + node->l->sum);
        } while (node->parent != nullptr);
    }
}

void set(Node * node, int left, int right, int a, int b, int value) {
    if (b <= left || right <= a) {
        return;
    }
    if (a >= left && right >= b) {
        node->set = value * (b - a);
        node->sum = value * (b - a);
        node->min = value * (b - a);
        upgrate(node);
        return;
    }
    lazy_propogate(node, a, b);
    set(node->l, left, right, a, (a + b) >> 1, value);
    set(node->r, left, right, (a + b) >> 1, b, value);
}

int minimum(Node * node, int left, int right, int * value) {
    if (node->set != (1 << 31)) {
        if (node->set <= *value) {
            *value -= node->set;
            return right - left;
        }
        int di = *value / (node->set / (right - left));
        *value = -(1 << 31);
        return di;
    }
    if (node->min <= *value) {
        *value -= node->sum;
        return right - left;
    }
    if (right - left == 1) {
        *value = -(1 << 31);
        return 0;
    }
    lazy_propogate(node, left, right);
    int result = minimum(node->l, left, (left + right) >> 1, value);
    if (*value >= 0) {
        result += minimum(node->r, (left + right) >> 1, right, value);
    }
    return result;
}

int main() {
    int n, power = 1;
    scanf("%d\n", &n);
    while(power < n) {
        power <<= 1;
    }
    char s[3];
    int left, right, value;
    while(cin >> s) {
        switch (s[0]) {
            case 'Q': {
                scanf("%d", &value);
                int distance = minimum(&head, 0, power, &value);
                if (distance > n) {
                    distance = n;
                }
                printf("%d\n", distance);
                continue;
            }
            case 'I': {
                scanf("%d%d%d", &left, &right, &value);
                set(&head, left - 1, right, 0, power, value);
                continue;
            }
            default: {
                return 0;
            }
        }
    }
    return 0;
}