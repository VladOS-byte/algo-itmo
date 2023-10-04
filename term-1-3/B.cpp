#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int main() {
    int n, k;
    ifstream f;
    f.open("input.txt");
    f >> n >> k;
    int coins[n][k];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; ++j) {
            f >> coins[i][j];
        }
    }
    f.close();
    int dp[n][k][2];
    dp[0][0][0] = coins[0][0];
    dp[0][0][1] = 0;
    for (int i = 1; i < n; ++i) {
        dp[i][0][0] = dp[i - 1][0][0] + coins[i][0];
        dp[i][0][1] = 1;
    }
    for (int i = 1; i < k; ++i) {
        dp[0][i][0] = dp[0][i - 1][0] + coins[0][i];
        dp[0][i][1] = -1;
    }
    ofstream fout;
    fout.open("output.txt");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < k; j++) {
            if (dp[i - 1][j][0] > dp[i][j - 1][0]) {
                dp[i][j][0] = dp[i - 1][j][0] + coins[i][j];
                dp[i][j][1] = 1;
            } else {
                dp[i][j][0] = dp[i][j - 1][0] + coins[i][j];
                dp[i][j][1] = -1;
            }
        }
    }
    fout << dp[n - 1][k - 1][0] << endl;
    stack<char> stack;
    int x = n - 1;
    int y = k - 1;
    while (x != 0 || y != 0) {
        int c = dp[x][y][1];
        stack.push(c == -1 ? 'R' : 'D');
        if (c == -1) {
            y--;
        } else {
            x--;
        }
    }
    while (!stack.empty()) {
        fout << stack.top();
        stack.pop();
    }
    fout.close();
    return 0;
}