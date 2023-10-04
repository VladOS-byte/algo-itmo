#include <iostream>
#include <fstream>
using namespace std;

struct matrix {
    int data[2][2];
};

matrix E = {1, 0, 0, 1};

void multiply(matrix * m, matrix m1, matrix m2, int * r) {
    m->data[0][0] = (m1.data[0][0] * m2.data[0][0] + m1.data[0][1] * m2.data[1][0]) % *r;
    m->data[0][1] = (m1.data[0][0] * m2.data[0][1] + m1.data[0][1] * m2.data[1][1]) % *r;
    m->data[1][0] = (m1.data[1][0] * m2.data[0][0] + m1.data[1][1] * m2.data[1][0]) % *r;
    m->data[1][1] = (m1.data[1][0] * m2.data[0][1] + m1.data[1][1] * m2.data[1][1]) % *r;
}

void buildTree(matrix tree[], int * power, int * n, int * r) {
    for (int i = *n; i < *power; ++i) {
        tree[*power + i - 1] = E;
    }
    for (int i = *power - 2; i >= 0; --i) {
        multiply(&tree[i], tree[2 * i + 1], tree[2 * i + 2], r);
    }
}

matrix getMulty(matrix tree[], int v, int left, int right, int a, int b, int * r) {
    if (left <= a && b <= right) {
        return tree[v];
    }
    if (b <= left || right <= a) {
        return E;
    }
    matrix m;
    multiply(&m, getMulty(tree, 2 * v + 1, left, right, a, (a + b) >> 1, r), getMulty(tree, 2 * v + 2, left, right, (a + b) >> 1, b, r), r);
    return m;
}

int main() {
    int r, n, m;
    FILE * fin;
    FILE * of;
    fin = fopen("crypto.in", "r");
    of = fopen("crypto.out", "w");
    fscanf(fin, "%d%d%d", &r, &n, &m);
    int power = 1;
    int logn = 0;
    while (power < n) {
        power <<= 1;
        logn++;
    }
    matrix tree[power << 1];
    for (int i = 0; i < n; ++i) {
        fscanf(fin, "%d%d\n%d%d\n\n", &tree[power + i - 1].data[0][0], &tree[power + i - 1].data[0][1],
            &tree[power + i - 1].data[1][0], &tree[power + i - 1].data[1][1]);
    }
    buildTree(tree, &power, &n, &r);
    int left, right;
    for (int i = 0; i < m; ++i) {
        fscanf(fin, "%d%d\n", &left, &right);
        matrix m = getMulty(tree, 0, left - 1, right, 0, power, &r);
        fprintf(of,"%d %d\n%d %d\n\n", m.data[0][0], m.data[0][1], m.data[1][0], m.data[1][1]);
    }
    fclose(fin);
    fclose(of);
    return 0;
}