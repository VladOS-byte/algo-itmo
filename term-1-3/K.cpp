#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    int n, w;
    ifstream fin;
    fin.open("skyscraper.in");
    fin >> n >> w;
    vector<vector<int>> vector(n + 1);
    int dp[1 << n];
    int cows[n + 1];
    bool used[n + 1];
    used[0] = true;
    for (int i = 1; i <= n; ++i) {
        fin >> cows[i];
        used[i] = false;
    }
    cows[0] = 0;
    fin.close();
    int p = 0;
    int flag = 0;
    while (flag < n) {
        dp[0] = 0;
        int m = 0;
        for (int i = 1; i < (1 << n); ++i) {
            dp[i] = dp[i - 1];
            int mask = i;
            int sum = 0;
            if (i == 75) {
                sum = 0;
            }
            int index = 1;
            while (mask > 0) {
                if (mask % 2 == 1 && !used[index]) {
                    sum += cows[index];
                }
                index++;
                mask = mask / 2;
            }
            if (dp[i] <= sum && sum <= w) {
                dp[i] = sum;
                m = i;
            }
        }
        int index = 1;
        while (m > 0) {
            if (m % 2 == 1 && !used[index]) {
                used[index] = true;
                vector[p].push_back(index);
                flag++;
            }
            index++;
            m = m / 2;
        }
        p++;
    }
    ofstream fout;
    fout.open("skyscraper.out");
    fout << p << endl;
    for (int i = 0; i < p; ++i) {
        fout << vector[i].size() << " ";
        for (int j : vector[i]) {
            fout << j << " ";
        }
        fout << endl;
    }
    fout.close();
    return 0;
}