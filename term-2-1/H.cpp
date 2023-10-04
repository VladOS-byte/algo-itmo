#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Node {
    long long set;
    long long min;
};

struct Segment {
    int i = 0, j = 0;
    long long k = 0;
};

Segment createSegment(int * i, int * j, long long * k) {
    Segment segment = * new Segment;
    segment.i = *i;
    segment.j = *j;
    segment.k = *k;
    return segment;
}

void propogate(vector<Node>& tree, int v) {
    if (tree[v].set != -1E18) {
        for (int i = 1; i <= 2; ++i) {
            if (tree[2 * v + i].min < tree[v].set) {
                tree[2 * v + i].min = tree[v].set;
                tree[2 * v + i].set = tree[v].set;
            }
        }
        tree[v].min = max(tree[v].set, tree[v].min);
        tree[v].set = -1E18;
    }
}

void lazy_propogate(vector<Node>& tree, int v, int left, int right) {
    if (right - left > 1) {
        propogate(tree, v);
    }
}

void upgrate(vector<Node>& tree, int v) {
    if (v > 0) {
        do {
            v = (v - 1) >> 1;
            tree[v].min = min(tree[2 * v + 1].min, tree[2 * v + 2].min);
        } while (v > 0);
    }
}

void set(vector<Node>& tree, int v, int left, int right, int a, int b, long long value) {
    lazy_propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return;
    }
    if (a >= left && right >= b) {
        if (tree[v].min < value) {
            tree[v].set = value;
            tree[v].min = value;
            upgrate(tree, v);
        }
        return;
    }
    set(tree, 2 * v + 1, left, right, a, (a + b) >> 1, value);
    set(tree, 2 * v + 2, left, right, (a + b) >> 1, b, value);
}

long long minimum(vector<Node>& tree, int v, int left, int right, int a, int b) {
    lazy_propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return 1E18;
    }
    if (a >= left && right >= b) {
        return tree[v].min;
    }
    return min(minimum(tree, 2 * v + 1, left, right, a, (a + b) >> 1),
               minimum(tree, 2 * v + 2, left, right, (a + b) >> 1, b));
}

long long getElement(vector<Node>& tree, int i, int power) {
    long long element = minimum(tree, 0, i, i + 1, 0, power);
    if (element == -1E18) {
        return 0;
    } else {
        return element;
    }
}

void buildTree(vector<Node>& tree, int n, int power) {
    for (int i = power - 1; i < power + n - 1; ++i) {
        tree[i].set = -1E18;
        tree[i].min = tree[i].set;
    }
    for (int i = power + n - 1; i < (power << 1); ++i) {
        tree[i].set = 1E18;
        tree[i].min = 1E18;
    }
    for (int i = power - 2; i >= 0; --i) {
        tree[i].set = -1E18;
        tree[i].min = min(tree[2 * i + 1].min, tree[2 * i + 2].min);
    }
}

int main() {
    int n, power = 1, m;
    FILE * fin;
    FILE * of;
    fin = fopen("rmq.in", "r");
    of = fopen("rmq.out", "w");
    fscanf(fin, "%d%d\n", &n, &m);
    while(power < n) {
        power <<= 1;
    }
    vector<Node> tree = vector<Node>(power << 1);
    Segment mas[m];
    buildTree(tree, n, power);
    int left, right;
    long long value;
    for (int i = 0; i < m; ++i) {
        fscanf(fin, "%d%d%lld", &left, &right, &value);
        mas[i] = createSegment(&left, &right, &value);
        set(tree, 0, left - 1, right, 0, power, value);
    }
    for (int i = 0; i < m; ++i) {
        if (minimum(tree, 0, mas[i].i - 1, mas[i].j, 0, power) != mas[i].k) {
            fprintf(of, "inconsistent");
            fclose(fin);
            fclose(of);
            return 0;
        }
    }
    fprintf(of, "consistent\n");
    for (int i = 0; i < n; ++i) {
        fprintf(of, "%lld ", getElement(tree, i, power));
    }
    fclose(fin);
    fclose(of);
    return 0;
}