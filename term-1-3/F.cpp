#include <iostream>
#include <stack>
using namespace std;

int main() {
    int n, m = 0;
    cin >> n;
    int coins[n + 1];
    for (int i = 1; i <= n; ++i) {
        cin >> coins[i];
    }
    int dp[n + 1][n + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = 1E6;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        m += coins[i] > 100 ? 1 : 0;
        for (int j = 0; j <= m; ++j) {
            if (coins[i] > 100) {
                if (0 < j && j < m) {
                    dp[i][j] = min(dp[i - 1][j + 1], dp[i - 1][j - 1] + coins[i]);
                } else if (j == m) {
                    dp[i][j] = dp[i - 1][j - 1] + coins[i];
                } else {
                    dp[i][j] = min(dp[i - 1][j + 1], dp[i - 1][j] + coins[i]);
                }
            } else {
                if (j < m) {
                    dp[i][j] = min(dp[i - 1][j + 1], dp[i - 1][j] + coins[i]);
                } else {
                    dp[i][j] = dp[i - 1][j] + coins[i];
                }
            }
        }
    }
    int answer = 1E6;
    int index = -1;
    for (int i = n; i >= 0; --i) {
        if (answer > dp[n][i]) {
            answer = dp[n][i];
            index = i;
        }
    }
    stack<int> stack;
    int k = index;
    for (int i = n; i > 0; --i) {
        if (dp[i][k] != 1E6) {
            if (coins[i] > 100 && k > 0 && dp[i][k] == dp[i - 1][k - 1] + coins[i]) {
                k--;
            } else if (k < n && dp[i][k] == dp[i - 1][k + 1]) {
                stack.push(i);
                k++;
            }
        }
    }
    cout << answer << endl << index << " " << stack.size() << endl;
    while (!stack.empty()) {
        cout << stack.top() << endl;
        stack.pop();
    }
    return 0;
}