#include <iostream>
#include <stack>
using namespace std;

int main() {
    int n;
    string s, s1;
    cin >> s >> s1;
    int dp[s.length() + 1][s1.length() + 1];
    for (int i = 0; i <= s.length(); ++i) {
        dp[i][0] = i;
    }
    for (int i = 0; i <= s1.length(); ++i) {
        dp[0][i] = i;
    }
    for (int i = 1; i <= s.length(); ++i) {
        for (int j = 1; j <= s1.length(); ++j) {
            if (s[i - 1] == s1[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
            }
        }
    }
    cout << dp[s.length()][s1.length()];
    return 0;
}