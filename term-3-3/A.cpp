#include <iostream>
#include <vector>

std::vector<long long> hash;
std::vector<long long> pow;
long long x;

long long getHash(int l, int r) {
    return (hash[r] - hash[l - 1] * pow[r - l + 1]);
}

int main() {
    x = 31;
    std::string s;
    std::cin >> s;

    hash.reserve(s.size() + 1);
    pow.reserve(s.size() + 1);

    hash.push_back(0);
    pow.push_back(1);
    long long back = x;
    for (char i : s) {
        hash.push_back(hash.back() * x + (i - 'a' + 1));
        pow.push_back(back);
        back *= x;
    }

    int m;
    std::cin >> m;

    for (int i = 0; i < m; ++i) {
        int l1, r1, l2, r2;
        std::cin >> l1 >> r1 >> l2 >> r2;
        long long h1 = getHash(l1, r1);
        long long h2 = getHash(l2, r2);
        if (h1 == h2) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }


    return 0;
}