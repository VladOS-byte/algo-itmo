#include <iostream>

using namespace std;

struct Node {
    long long set;
    long long add;
    long long min;
};

const Node E{1 << 30, 1 << 30, 1 << 30};

void propogate(Node tree[], int v) {
    if (tree[v].set != (1 << 30)) {
        if (tree[2 * v + 1].set == (1 << 30) || tree[2 * v + 1].set < tree[v].set) {
            tree[2 * v + 1].set = tree[v].set;
        }
        if (tree[2 * v + 2].set == (1 << 30) || tree[2 * v + 2].set < tree[v].set) {
            tree[2 * v + 2].set = tree[v].set;
        }
        if (tree[2 * v + 1].min < tree[v].set) {
            tree[2 * v + 1].min = tree[v].set;
        }
        if (tree[2 * v + 2].min < tree[v].set) {
            tree[2 * v + 2].min = tree[v].set;
        }
        if (tree[2 * v + 1].min <= tree[2 * v + 2].min) {
            tree[v].min = tree[2 * v + 1].min;
            tree[v].add = tree[2 * v + 1].add;
        } else {
            tree[v].min = tree[2 * v + 2].min;
            tree[v].add = tree[2 * v + 2].add;
        }
        tree[v].set = (1 << 30);
    }
}

void lazy_propogate(Node tree[], int v, int left, int right) {
    if (right - left > 1) {
        propogate(tree, v);
 //       cout << v << ": " << tree[v].min << endl;
    } else {
        if (tree[v].min > tree[v].set) {
            tree[v].set = tree[v].min;
        } else {
            tree[v].min = tree[v].set;
        }
 //       cout << v << ": " << tree[v].min << endl;
    }
}

void upgrate(Node tree[], int v) {
    if (v > 0) {
        do {
            v = (v - 1) >> 1;
            if (tree[2 * v + 1].min <= tree[2 * v + 2].min) {
                tree[v].min = tree[2 * v + 1].min;
                tree[v].add = tree[2 * v + 1].add;
            } else {
                tree[v].min = tree[2 * v + 2].min;
                tree[v].add = tree[2 * v + 2].add;
            }
        } while (v > 0);
    }
}

void set(Node tree[], int v, int left, int right, int a, int b, long long value) {
    lazy_propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return;
    }
    if (a >= left && right >= b) {
        tree[v].set = value;
        if (tree[v].min < value) {
            tree[v].min = value;
        }
        upgrate(tree, v);
        return;
    }
    set(tree, 2 * v + 1, left, right, a, (a + b) >> 1, value);
    set(tree, 2 * v + 2, left, right, (a + b) >> 1, b, value);
}

Node minimum(Node tree[], int v, int left, int right, int a, int b) {
    lazy_propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return E;
    }
    if (a >= left && right >= b) {
        return tree[v];
    }
    Node n = minimum(tree, 2 * v + 1, left, right, a, (a + b) >> 1);
    Node n1 = minimum(tree, 2 * v + 2, left, right, (a + b) >> 1, b);
    if (n.min <= n1.min) {
        return n;
    } else {
        return n1;
    }
}

void buildTree(Node tree[], int n, int power) {
    for (int i = power - 1; i < power + n - 1; ++i) {
        tree[i] = *new Node();
        tree[i].add = i - power + 1;
        tree[i].set = 0;
        tree[i].min = tree[i].set;
    }
    for (int i = power + n - 1; i < (power << 1); ++i) {
        tree[i] = *new Node();
        tree[i].set = (1 << 30);
        tree[i].add = -1;
        tree[i].min = (1 << 30);
    }
    for (int i = power - 2; i >= 0; --i) {
        tree[i] = *new Node();
        tree[i].set = (1 << 30);
        if (tree[2 * i + 1].min <= tree[2 * i + 2].min) {
            tree[i].min = tree[2 * i + 1].min;
            tree[i].add = tree[2 * i + 1].add;
        } else {
            tree[i].min = tree[2 * i + 2].min;
            tree[i].add = tree[2 * i + 2].add;
        }
    }
}

int main() {
    int n, m, power = 1;
    scanf("%d%d\n", &n, &m);
    while(power < n) {
        power <<= 1;
    }
    Node tree[power << 1];
    buildTree(tree, n, power);
    char s[10];
    int left, right, value;
    for (int i = 0; i < m; ++i) {
        cin >> s;
        switch (s[0]) {
            case 'a': {
                scanf("%d%d", &left, &right);
                Node n = minimum(tree, 0, left - 1, right, 0, power);
                printf("%lld %lld\n", n.min, n.add + 1);
                continue;
            }
            case 'd': {
                scanf("%d%d%d", &left, &right, &value);
                set(tree, 0, left - 1, right, 0, power, value);
                continue;
            }
            default: {
                return 0;
            }
        }
    }
    return 0;
}