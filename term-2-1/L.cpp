#include <iostream>
#include <vector>

using namespace std;

void modify(vector<vector<vector<int>>> & tree, int i, int j, int k, int d) {
    int u = j;
    int h = k;
    while (i < tree.size()) {
        while (j < tree.size()) {
            while (k < tree.size()) {
                tree[i][j][k] += d;
                k = k | (k + 1);
            }
            k = h;
            j = j | (j + 1);
        }
        j = u;
        i = i | (i + 1);
    }
}

void set(vector<vector<vector<int>>> & array, vector<vector<vector<int>>> & tree, int i, int j, int k, int value) {
    array[i][j][k] += value;
    modify(tree, i, j, k, value);
}

int sum(vector<vector<vector<int>>> & tree, int i, int j, int k) {
    int res = 0;
    int u = j;
    int h = k;
    while (i >= 0) {
        while (j >= 0) {
            while (k >= 0) {
                res += tree[i][j][k];
                k = (k & (k + 1)) - 1;
                if (k == 0) {
                    break;
                }
            }
            k = h;
            j = (j & (j + 1)) - 1;
            if (j == 0) {
                break;
            }
        }
        j = u;
        i = (i & (i + 1)) - 1;
        if (i == 0) {
            break;
        }
    }
    return res;
}

int main() {
    int n;
    scanf("%d\n", &n);
    vector<vector<vector<int>>> array = vector<vector<vector<int>>>(n);
    vector<vector<vector<int>>> tree = vector<vector<vector<int>>>(n);
    for (int i = 0; i < n; ++i) {
        array[i] = vector<vector<int>>(n);
        tree[i] = vector<vector<int>>(n);
        for (int j = 0; j < n; ++j) {
            array[i][j] = vector<int>(n);
            tree[i][j] = vector<int>(n);
        }
    }
    int s;
    int left1, up1, hight1, value;
    int left2, up2, hight2;
    while(cin >> s) {
        switch (s) {
            case 2: {
                scanf("%d%d%d%d%d%d", &left1, &up1, &hight1, &left2, &up2, &hight2);
                int s = sum(tree, left2, up2, hight2) - sum(tree, left1 - 1, up2, hight2) - sum(tree, left2, up1 - 1, hight2) -
                        sum(tree, left2, up2, hight1 - 1) + sum(tree, left1 - 1, up1 - 1, hight2) + sum(tree, left2, up1 - 1, hight1 - 1) +
                        sum(tree, left1 - 1, up2, hight1 - 1) - sum(tree, left1 - 1, up1 - 1, hight1 - 1);
                printf("%d\n", s);
                continue;
            }
            case 1: {
                scanf("%d%d%d%d", &left1, &up1, &hight1, &value);
                set(array, tree, left1, up1, hight1, value);
                continue;
            }
            default: {
                return 0;
            }
        }
    }
    return 0;
}
