#include <iostream>
using namespace std;

int main() {
    long long n, m = 0;
    cin >> n;
    long long dp[n + 1][10];
    if (n == 1) {
        cout << 8;
        return 0;
    }
    for (int i = 0; i < 10; ++i) {
        dp[1][i] = 1;
    }
    dp[1][0] = 0;
    dp[1][5] = 0;
    dp[1][8] = 0;
    for (int i = 2; i <= n; ++i) {
        dp[i][0] = dp[i - 1][4] + dp[i - 1][6];
        dp[i][1] = dp[i - 1][8] + dp[i - 1][6];
        dp[i][3] = dp[i - 1][4] + dp[i - 1][8];
        dp[i][7] = dp[i - 1][2] + dp[i - 1][6];
        dp[i][9] = dp[i - 1][4] + dp[i - 1][2];
        dp[i][2] = dp[i - 1][7] + dp[i - 1][9];
        dp[i][8] = dp[i - 1][1] + dp[i - 1][3];
        dp[i][4] = dp[i - 1][3] + dp[i - 1][9] + dp[i - 1][0];
        dp[i][6] = dp[i - 1][1] + dp[i - 1][7] + dp[i - 1][0];
        dp[i][5] = 0;
        for (int j = 0; j < 10; ++j) {
            dp[i][j] = dp[i][j] % 1000000000;
        }
    }
    for (int i = 0; i < 10; ++i) {
        m = (m + dp[n][i]) % 1000000000;
    }
    cout << m % 1000000000;
    return 0;
}