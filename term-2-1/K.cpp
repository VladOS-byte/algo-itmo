#include <iostream>

using namespace std;

void buildTree(int tree[], int power, int n) {
    for (int i = 0; i < n; ++i) {
        tree[power + i - 1] = 0;
    }
    for (int i = n; i <= power; ++i) {
        tree[power + i - 1] = 1;
    }
    for (int i = power - 2; i >= 0; --i) {
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

void set(int tree[], int v, int value) {
    tree[v] = value;
    int ind = v;
    if (ind > 0) {
        do {
            ind = (ind - 1) >> 1;
            tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
        } while (ind > 0);
    }
}

void ex(int tree[], int v, int power) {
    int index = power + v - 1;
    set(tree, index, 0);
}

int enter(int tree[], int v, int left, int right, int a, int b) {
    if ((b <= left || right <= a) || (right - left == tree[v])) {
        return -1;
    }
    if (right - left == 1) {
        set(tree, v, 1);
        return v;
    }
    int result = enter(tree, 2 * v + 1, left, (left + right) >> 1, a, b);
    if (result < 0) {
        result = enter(tree, 2 * v + 2, (left + right) >> 1, right, a, b);
    }
    return result;
}

int ent(int tree[], int v, int power) {
    if (tree[power + v - 1] == 0) {
        int index = power + v - 1;
        set(tree, index, 1);
        return v;
    }
    int result = enter(tree, 0, 0, power, v + 1, power);
    if (result < 0) {
        result = enter(tree, 0, 0, power, 0, v);
    }
    return result + 1 - power;
}

int main() {
    int n, m;
    FILE * fin = fopen("parking.in", "r");
    FILE * of = fopen("parking.out", "w");
    fscanf(fin, "%d%d\n", &n, &m);
    int power = 1;
    while (power < n) {
        power <<= 1;
    }
    int tree[power << 1];
    buildTree(tree, power, n);
    char s[6];
    int index;
    for (int i = 0; i < m; i++) {
        fscanf(fin, "%s%d\n", s, &index);
        if (s[1] == 'x') {
            ex(tree, index - 1, power);
        } else {
            fprintf(of,"%d\n", ent(tree, index - 1, power) + 1);
        }
    }
    fclose(fin);
    fclose(of);
    return 0;
}