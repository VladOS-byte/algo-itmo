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
    z[0] = s.size();

    bool flag;
    int t = s.size();
    for (int i = 1; i <= s.size() / 2; ++i) {
        if (s.size() % i == 0) {
            flag = true;
            for (int j = 0; j < z.size(); j+=i) {
                if (z[j] % i != 0 || z[j] != s.size() - j) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                t = i;
                break;
            }
        }
    }

    std::cout << t;
    return 0;
}