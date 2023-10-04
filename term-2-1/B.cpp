#include <iostream>

using namespace std;

void build(long long tree[], int * power, int * n) {
    for (int i = 0; i < *n; ++i) {
        cin >> tree[*power + i - 1];
    }
    for (int i = *n; i <= *power; ++i) {
        tree[*power + i - 1] = 0;
    }
    for (int i = *power - 2; i >= 0; --i) {
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

void set(long long tree[], int * power, int * index, int * value) {
    tree[*power + *index - 1] = *value;
    int i = *power + *index - 1;
    if (i > 0) {
        do {
            i = (i - 1) >> 1;
            tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
        } while (i > 0);
    }
}

long long sum(long long tree[], int v, int left, int right, int a, int b) {
    if (left <= a && b <= right) {
        return tree[v];
    }
    if (b <= left || right <= a) {
        return 0;
    }
    return sum(tree, 2 * v + 1, left, right, a, (a + b) >> 1)
    + sum(tree, 2 * v + 2, left, right, (a + b) >> 1, b);
}

int main() {
    int n;
    cin >> n;
    int power = 1;
    while (power < n) {
        power <<= 1;
    }
    long long tree[power << 1];
    build(tree, &power, &n);
    string command;
    while(cin >> command) {
        if (command == "set") {
            int index, value;
            cin >> index >> value;
            --index;
            set(tree, &power, &index, &value);
        } else {
            int left, right;
            cin >> left >> right;
            --left;
            cout << sum(tree, 0, left, right, 0, power) << endl;
        }
    }
    return 0;
}