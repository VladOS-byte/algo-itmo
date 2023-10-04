#include<iostream>
#include<vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    std::vector<int> answer = {};
    int u = 2;

    while (u * u <= n) {
        if (n % u == 0) {
            answer.push_back(u);
            n /= u;
        } else {
            u++;
        }
    }

    if (n != 1) {
        answer.push_back(n);
    }

    for (int a : answer) {
        std::cout << a << " ";
    }

    return 0;
}
