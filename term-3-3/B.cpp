#include <iostream>
#include <vector>

int main() {
    std::string s;
    std::cin >> s;

    std::vector<int> pref;
    pref.reserve(s.size());
    int prev = 0;
    pref.push_back(0);

    for (int i = 1; i < s.size(); ++i) {
        prev = pref[i - 1];
        while (prev > 0 && s[i] != s[prev]) {
            prev = pref[prev - 1];
        }
        if (s[i] == s[prev]) {
            prev++;
        }
        pref.push_back(prev);
    }

    for (int i : pref) {
        std::cout << i << " ";
    }

    return 0;
}