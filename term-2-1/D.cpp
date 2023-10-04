#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int prefix = 0;
    int centralSum = 0;
    int count = 0;
    int suffix = 0;
};

void propogate(vector<Node>& tree, int v, int left, int right) {
    if (right - left <= 1) {
        return;
    }
    if (tree[v].centralSum == right - left) {
        tree[2 * v + 1].centralSum = tree[v].centralSum >> 1;
        tree[2 * v + 1].prefix = tree[v].centralSum >> 1;
        tree[2 * v + 1].suffix = tree[v].centralSum >> 1;
        tree[2 * v + 1].count = 1;
        tree[2 * v + 2].centralSum = tree[v].centralSum >> 1;
        tree[2 * v + 2].prefix = tree[v].centralSum >> 1;
        tree[2 * v + 2].suffix = tree[v].centralSum >> 1;
        tree[2 * v + 2].count = 1;
    } else if (tree[v].centralSum == 0) {
        tree[2 * v + 1].centralSum = 0;
        tree[2 * v + 1].prefix = 0;
        tree[2 * v + 1].suffix = 0;
        tree[2 * v + 1].count = 0;
        tree[2 * v + 2].centralSum = 0;
        tree[2 * v + 2].prefix = 0;
        tree[2 * v + 2].suffix = 0;
        tree[2 * v + 2].count = 0;
    }
}

void upgrate (vector<Node>& tree, int v) {
    while (v > 0) {
        v = (v - 1) >> 1;
        tree[v].count = tree[2 * v + 1].count + tree[2 * v + 2].count
                        + (tree[2 * v + 1].suffix > 0 && tree[2 * v + 2].prefix > 0 ? -1 : 0);
        tree[v].centralSum = tree[2 * v + 1].centralSum + tree[2 * v + 2].centralSum;
        tree[v].prefix = tree[2 * v + 1].prefix;
        tree[v].suffix = tree[2 * v + 2].suffix;
    }
    tree[0].count += (tree[1].prefix > 0 && tree[1].suffix + tree[1].prefix == tree[1].centralSum ? 1 : 0)
            + (tree[2 * v + 2].suffix > 0 && tree[2].suffix + tree[2].prefix == tree[2].centralSum ? 1 : 0);
}

void set(vector<Node>& tree, int v, int left, int right, int a, int b, int value) {
    propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return;
    }
    if (left <= a && b <= right) {
        tree[v].centralSum = (b - a) * value;
        tree[v].prefix = (b - a) * value;
        tree[v].suffix = (b - a) * value;
        tree[v].count = value == 0 ? 0 : 1;
        upgrate(tree, v);
        return;
    }
    set(tree, 2 * v + 1, left, right, a, (a + b) >> 1, value);
    set(tree, 2 * v + 2, left, right, (a + b) >> 1, b, value);
}

int main() {
    int n;
    scanf("%d\n", &n);
    int power = 524288;
    vector<Node> tree(power << 2);
    char c;
    int left, right;
    for (int i = 0; i < n; ++i) {
        cin >> c;
        scanf("%d%d", &left, &right);
        if (c == 'W') {
            set(tree, 0, left, left + right, -(power), power, 0);
        } else {
            set(tree, 0, left, left + right, -(power), power, 1);
        }
        printf("%d %d\n", tree[0].count, tree[0].centralSum);
    }
    return 0;
}