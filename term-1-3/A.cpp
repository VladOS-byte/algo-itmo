#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int main() {
    int n, k;
    ifstream f;
    f.open("input.txt");
    f >> n >> k;
    int coins[n];
    int dp[n][2];
    dp[0][0] = 0;
    dp[0][1] = 0;
    coins[0] = 0;
    coins[n - 1] = 0;
    for (int i = 1; i < n - 1; i++) {
        f >> coins[i];
    }
    f.close();
    ofstream fout;
    fout.open("output.txt");

    for (int i = 1; i < n; i++) {
        int m = -100000;
        int index = -1;
        for (int j = i - k >= 0 ? i - k : 0; j < i; j++) {
            if(m + coins[i] < dp[j][0] + coins[i]) {
                m = dp[j][0];
                index = j;
            }
        }
        dp[i][0] = m + coins[i];
        dp[i][1] = index;
    }
    fout << dp[n - 1][0] << endl;
    stack<int> stack;
    int h = n - 1;
    while(h > 0) {
        stack.push(h + 1);
        h = dp[h][1];
    }
    fout << stack.size() << endl;
    stack.push(1);
    h = stack.size();
    for (int i = 0; i < h; i++) {
        fout << stack.top() << " ";
        stack.pop();
    }
    fout.close();
    return 0;
}