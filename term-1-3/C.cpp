#include <iostream>
using namespace std;

int main() {
    int n, k = 0, m = 0;
    cin >> n;
    int coins[n];
    for (int j = 0; j < n; ++j) {
        cin >> coins[j];
    }
    int dp[n][2];
    for (int i = n - 1; i >= 0; --i) {
        dp[i][0] = 0;
        dp[i][1] = i;
        for (int j = i + 1; j < n; ++j) {
            if (coins[j] > coins[i] && dp[j][0] > dp[i][0]) {
                dp[i][0] = dp[j][0];
                dp[i][1] = j;
            }
        }
        dp[i][0]++;
        if (dp[i][0] > m) {
            m = dp[i][0];
            k = i;
        }
    }
    cout << m << endl;
    while (k < n) {
        cout << coins[k] << " ";
        if (dp[k][1] == k) {
            break;
        } else {
            k = dp[k][1];
        }
    }
    return 0;
}