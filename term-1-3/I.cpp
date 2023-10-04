#include <iostream>

using namespace std;


long long getCountDominoWithoutPair(bool a[13][13], int n, int m) {
    long long dp[n + 1][m + 1][1 << m];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int p = 0; p < (1 << m); ++p) {
                dp[i][j][p] = 0;
            }
        }
    }
    dp[0][0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int p = 0; p < (1 << m); ++p) {
                if (p & (1 << j) || !a[i][j]) {
                    dp[i][j + 1][p & (1 << j) ? p - (1 << j) : p] += dp[i][j][p];
                } else {
                    if (a[i + 1][j]) {
                        dp[i][j + 1][p + (1 << j)] += dp[i][j][p];
                    }
                    if (j < m - 1 && !(p & (1 << (j + 1))) && a[i][j + 1]) {
                        dp[i][j + 1][p + (1 << (j + 1))] += dp[i][j][p];
                    }
                }
            }
            for (int p = 0; p < (1 << m); ++p) {
                dp[i + 1][0][p] = dp[i][m][p];
            }
        }
    }
    return dp[n][0][0];
}

int main() {
    int n, m;

    cin >> n >> m;
    bool a[13][13];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            a[i][j] = c != 'X';
        }
    }
    long long answer = getCountDominoWithoutPair(a, n, m);
    cout << answer;
    return 0;
}