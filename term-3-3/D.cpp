#include <iostream>
#include <vector>

int main() {
    std::string s, t;
    std::cin >> t >> s;

    std::vector<int> answer;
    answer.reserve(s.size());
    s = t + s;

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

    for (int i = t.size(); i < z.size(); ++i) {
        if (z[i] >= t.size()) {
            answer.push_back(i - t.size() + 1);
        }
    }

    std::cout << answer.size() << std::endl;
    for (int i : answer) {
        std::cout << i << " ";
    }

    return 0;
}