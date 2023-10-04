#include <iostream>
#include <vector>

int main() {
    std::string s;
    std::cin >> s;

    std::vector<int> z = std::vector<int>(s.size(), 0);
    int l = 0;

    for (int i = 1; i < s.size(); ++i) {
        z[i] = std::max(0, std::min(z[i - l], l + z[l] - i));
        while (s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (l + z[l] < i + z[i]) {
            l = i;
        }
    }

    for (int i = 1; i < z.size(); ++i) {
        std::cout << z[i] << " ";
    }

    return 0;
}