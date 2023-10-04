#include <iostream>
#include <set>
#include <vector>

long long pow[10001];
int x = 31;

void setHash(std::vector<long long> & hash, std::string & s) {
    hash.clear();
    hash.reserve(s.length());
    hash.push_back(0);
    for (char i : s) {
        hash.push_back(hash.back() * x + (i - 'a' + 1));
    }
}

long long getHash(std::vector<long long> & hash, int i, int length) {
    return (hash[i + length - 1] - hash[i - 1] * pow[length]);
}

std::string getCommonSubstr(std::vector<std::string> & ss, int length) {
    std::set<long long> bhashset;
    std::vector<long long> hash;
    long long lhash;
    setHash(hash, ss[0]);
    int l = 1;
    for (int i = 1; i <= ss[0].length() - length + 1; ++i) {
        lhash = getHash(hash, i, length);
        bhashset.insert(lhash);
    }
    for (int i = 1; i < ss.size(); ++i) {
        std::set<long long> hashset;
        setHash(hash, ss[i]);
        for (int j = 1; j <= ss[i].size() - length + 1; ++j) {
            lhash = getHash(hash, j, length);
            if (bhashset.count(lhash) > 0) {
                l = j;
                hashset.insert(lhash);
            }
        }
        bhashset = hashset;
    }
    if (bhashset.empty()) {
        return "!";
    }
    return ss[ss.size() - 1].substr(l - 1, length);
}

int main() {
    int k;
    std::cin >> k;
    std::vector<std::string> ss;
    ss.reserve(k);

    int r = INT32_MAX - 1;
    pow[0] = 1;
    for (int i = 1; i < 10001; ++i) {
        pow[i] = x * pow[i - 1];
    }

    for (int i = 0; i < k; ++i) {
        std::string s;
        std::cin >> s;
        ss.push_back(s);
        if (r > s.length()) {
            r = s.length();
        }
    }

    r++;
    int l = 0;
    std::string answer, lanswer;

    while (r - l > 1) {
        unsigned long m = (r + l) / 2;
        if ((lanswer = getCommonSubstr(ss, m)) == "!") {
            r = m;
        } else {
            l = m;
            answer = lanswer;
        }
    }

    std::cout << answer;

    return 0;
}