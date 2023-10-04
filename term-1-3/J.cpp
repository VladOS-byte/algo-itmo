#include <iostream>
#include <stack>
using namespace std;

bool check (int i, int j, int m) {
    int bitMask = -1;
    bool prefEqual = false;
    for (int k = 0; k < m; ++k) {
        if (prefEqual && ((i >> k) & 1) == ((j >> k) & 1) && ((i >> k) & 1) == bitMask) {
            return false;
        } else if (((i >> k) & 1) == ((j >> k) & 1)) {
            bitMask = (i >> k) % 2;
            prefEqual = true;
        } else {
            bitMask = -1;
            prefEqual = false;
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    if (n < m) {
        swap(n, m);
    }
    int p[1 << m][1 << m];
    for (int i = 0; i < (1 << m); ++i) {
        for (int j = 0; j < (1 << m); ++j) {
            p[i][j] = check(i, j, m) ? 1 : 0;
        }
    }
    int dp[n][1 << m];
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < (1 << m); ++i) {
            dp[j][i] = 0;
        }
    }
    for (int i = 0; i < (1 << m); ++i) {
        dp[0][i] = 1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < (1 << m); ++j) {
            for (int k = 0; k < (1 << m); ++k) {
                dp[i][j] += dp[i - 1][k] * p[j][k];
            }
        }
    }
    long long answer = 0;
    for (int i = 0; i < (1 << m); ++i) {
        answer += dp[n - 1][i];
    }
    cout << answer;
    return 0;
}