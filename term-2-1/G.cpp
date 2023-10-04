#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    int i = 0, j = 0;
    int k = 0;
    bool isOpen = false;
    bool operator < (const Segment & segment) const
    {
        return (k == segment.k ? (isOpen == segment.isOpen ? false : isOpen) : k < segment.k);
    }
};

struct Pair {
    int x = 0, y = 0;
};

struct Node {
    int add = 0;
    int max = 0;
};

void propogate(vector<Node>& tree, int v) {
    if (tree[v].add != 0) {
        tree[2 * v + 1].add += tree[v].add;
        tree[2 * v + 2].add += tree[v].add;
        tree[v].max += tree[v].add;
        tree[v].add = 0;
    }
}

void lazy_propogate(vector<Node>& tree, int v, int left, int right) {
    if (right - left > 1) {
        propogate(tree, v);
    } else {
        tree[v].max += tree[v].add;
        tree[v].add = 0;
    }
}

void upgrate(vector<Node>& tree, int v) {
    while (v > 0) {
        v = (v - 1) >> 1;
        tree[v].max = max(tree[2 * v + 1].max + tree[2 * v + 1].add, tree[2 * v + 2].max + tree[2 * v + 2].add);
    }
}

void add(vector<Node>& tree, int v, int left, int right, int a, int b, int value) {
    lazy_propogate(tree, v, a, b);
    if (b <= left || right <= a) {
        return;
    }
    if (a >= left && right >= b) {
        tree[v].add = value;
        upgrate(tree, v);
        return;
    }
    add(tree, 2 * v + 1, left, right, a, (a + b) / 2, value);
    add(tree, 2 * v + 2, left, right, (a + b) / 2, b, value);
}

int getMax(vector<Node>& tree) {
    lazy_propogate(tree, 0, -(1 << 18), (1 << 18));
    return tree[0].max;
}

int maxIndex(vector<Node>& tree, int v, int left, int right) {
    if (right <= left) {
        return -(1 << 24);
    }
    lazy_propogate(tree, v, left, right);
    if (tree[v].max != tree[0].max) {
        return -(1 << 24);
    }
    if (right - left == 1) {
        return left;
    }
    int p = maxIndex(tree, 2 * v + 1, left, (left + right) / 2);
    if (p == -(1 << 24)) {
        return maxIndex(tree, 2 * v + 2, (left + right) / 2, right);
    }
    return p;
}

Segment createSegment(int * i, int * j, int * k, bool b) {
    Segment segment = * new Segment;
    segment.i = *i;
    segment.j = *j;
    segment.k = *k;
    segment.isOpen = b;
    return segment;
}

int main() {
    int n = 0, power = (1 << 19);
    scanf("%d", &n);
    vector<Node> tree = vector<Node>(power << 1);
    Segment segmentsy[n << 1];
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    for (int i = 0; i < (n << 1); i += 2) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        segmentsy[i] = createSegment(&y1, &y2, &x1, true);
        segmentsy[i + 1] = createSegment(&y1, &y2, &x2, false);
    }
    sort(segmentsy, segmentsy + (n << 1));
    int m = 0, maximum = 0;
    Pair p = * new Pair;
    int i = 0;
    bool flag = false;
    while (i < (n << 1)) {
        x1 = segmentsy[i].k;
        flag = false;
        while(i < (n << 1) && segmentsy[i].k == x1 && segmentsy[i].isOpen) {
            add(tree, 0, segmentsy[i].i, segmentsy[i].j + 1, -(1 << 18), 1 << 18, 1);
            ++i;
            flag = true;
        }
        m = getMax(tree);
        if (m > maximum) {
            maximum = m;
            p.x = x1;
            p.y = maxIndex(tree, 0, -(1 << 18), (1 << 18));
        }
        while(i < (n << 1) && segmentsy[i].k == x1 && !segmentsy[i].isOpen) {
            add(tree, 0, segmentsy[i].i, segmentsy[i].j + 1, -(1 << 18), 1 << 18, -1);
            ++i;
            flag = true;
        }
        if (!flag) {
            ++i;
        }
    }
    printf("%d\n%d %d", maximum, p.x, p.y);
    return 0;
}
