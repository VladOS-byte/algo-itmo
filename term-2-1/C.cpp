#include <iostream>

using namespace std;

struct Node {
    long long set;
    long long add;
    long long min;
};

void propogate(Node tree[], int v) {
    if (tree[v].set != 1E18 + 1) {
        tree[2 * v + 1].set = tree[v].set;
        tree[2 * v + 2].set = tree[v].set;
        tree[2 * v + 1].min = tree[v].set;
        tree[2 * v + 2].min = tree[v].set;
        tree[2 * v + 1].add = 0;
        tree[2 * v + 2].add = 0;
        tree[v].min = tree[v].set;
        tree[v].set = 1E18 + 1;
    }
    if (tree[v].add != 0) {
        tree[2 * v + 1].add += tree[v].add;
        tree[2 * v + 2].add += tree[v].add;
        tree[v].min += tree[v].add;
        tree[v].add = 0;
    }
}

void lazy_propogate(Node tree[], int v, int left, int right) {
    if (right - left > 1) {
        propogate(tree, v);
 //       cout << v << ": " << tree[v].min << endl;
    } else {
        tree[v].set += tree[v].add;
        tree[v].add = 0;
        tree[v].min = tree[v].set;
 //       cout << v << ": " << tree[v].min << endl;
    }
}

void upgrate(Node tree[], int v) {
    if (v > 0) {
        do {
            v = (v - 1) >> 1;
            tree[v].min = min(tree[2 * v + 1].min + tree[2 * v + 1].add, tree[2 * v + 2].min + tree[2 * v + 2].add);
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
        tree[v].min = value;
        upgrate(tree, v);
        return;
    }
    set(tree, 2 * v + 1, left, right, a, (a + b) >> 1, value);
    set(tree, 2 * v + 2, left, right, (a + b) >> 1, b, value);
}

void add(Node tree[], int v, int left, int right, int a, int b, int value) {
    lazy_propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return;
    }
    if (a >= left && right >= b) {
        tree[v].add = value;
        upgrate(tree, v);
        return;
    }
    add(tree, 2 * v + 1, left, right, a, (a + b) >> 1, value);
    add(tree, 2 * v + 2, left, right, (a + b) >> 1, b, value);
}

long long minimum(Node tree[], int v, int left, int right, int a, int b) {
    lazy_propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return 1E18 + 1;
    }
    if (a >= left && right >= b) {
        return tree[v].min;
    }
    return min(minimum(tree, 2 * v + 1, left, right, a, (a + b) >> 1),
            minimum(tree, 2 * v + 2, left, right, (a + b) >> 1, b));
}

void buildTree(Node tree[], int n, int power) {
    for (int i = power - 1; i < power + n - 1; ++i) {
        tree[i] = *new Node();
        tree[i].add = 0;
        scanf("%lld", &tree[i].set);
        tree[i].min = tree[i].set;
    }
    for (int i = power + n - 1; i < (power << 1); ++i) {
        tree[i] = *new Node();
        tree[i].set = 1E18 + 1;
        tree[i].add = 0;
        tree[i].min = 1E18 + 1;
    }
    for (int i = power - 2; i >= 0; --i) {
        tree[i] = *new Node();
        tree[i].set = 1E18 + 1;
        tree[i].add = 0;
        tree[i].min = min(tree[2 * i + 1].min, tree[2 * i + 2].min);
    }
}

int main() {
    int n, power = 1;
    scanf("%d\n", &n);
    while(power < n) {
        power <<= 1;
    }
    Node tree[power << 1];
    buildTree(tree, n, power);
    char s[3];
    int left, right, value;
    while(cin >> s) {
        switch (s[0]) {
            case 'm': {
                scanf("%d%d", &left, &right);
                printf("%lld\n", minimum(tree, 0, left - 1, right, 0, power));
                continue;
            }
            case 'a': {
                scanf("%d%d%d", &left, &right, &value);
                add(tree, 0, left - 1, right, 0, power, value);
                continue;
            }
            case 's': {
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