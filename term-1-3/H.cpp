#include <iostream>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    n++;
    stack<int> stack;
    int dp[1 << n][n];
    int towns[n][n];
    towns[0][0] = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            cin >> towns[i][j];
        }
        towns[0][i] = 0;
        towns[i][0] = 0;
    }
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = 1E9;
        }
    }
    for (int j = 0; j < n; ++j) {
        dp[1 << j][0] = 0;
    }
    for (int k = 2; k < (1 << n); ++k) {
        for (int i = 0; i < n; ++i) {
            if ((k >> i) % 2 == 1) {
                int mask = k - (1 << i);
                for (int j = 0; j < n; ++j) {
                    if (i != j && (k >> j) % 2 == 1) {
                        dp[k][i] = min(dp[k][i], dp[mask][j] + towns[i][j]);
                    }
                }
            }
        }
    }
    int mindist = INT32_MAX;
    int mask = (1 << n) - 1;
    bool flag = true;
    int lastindex = -1;
    int lastdist = 1E9;
    while (mask > 1) {
        int answer = INT32_MAX;
        int index = -1;
        for (int i = 1; i < n; ++i) {
            if (answer > dp[mask][i] && (mask >> i) % 2 == 1 && (lastindex == -1 || towns[lastindex][i] == lastdist - dp[mask][i])) {
                answer = dp[mask][i];
                index = i;
            }
        }
        if (flag) {
            flag = false;
            mindist = answer;
        }
        lastindex = index;
        lastdist = answer;
        if (index < 1) {
            break;
        }
        stack.push(index);
        mask = mask - (1 << index);
    }
    cout << mindist << endl;
    while (!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    return 0;
}