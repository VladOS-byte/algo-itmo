#include <iostream>
#include <vector>

int pow = 0;

int lcp (std::vector<std::vector<int>> & classes, int i, int j) {
    int answer = 0;
    for (int k = pow; k >= 0; --k)
        if (i < classes[k].size() && j < classes[k].size() && classes[k][i] == classes[k][j]) {
            answer += 1 << k;
            i += 1 << k;
            j += 1 << k;
        }
    return answer;
}

int main() {
    std::string s = "";
    std::getline(std::cin, s);

    int n = s.length();
    s += s;
    pow = 0;
    while (n > (1 << pow)) {
        pow++;
    }

    std::vector<std::vector<int>> map = std::vector<std::vector<int>>(100, std::vector<int>());
    std::vector<std::vector<int>> classes(pow + 1, std::vector<int>(n));
    std::vector<int> position(n);
    int cl = 0, count = 0;

    for (int i = 0; i < n; ++i) {
        map[s[i] - 32].push_back(i);
    }

    for (auto & p : map) {
        for (int x : p) {
            classes[0][x] = cl;
            position[count] = x;
            count++;
        }
        cl++;
    }

    for (int k = 0; k < pow; ++k) {
        int pk = 1 << k;
        std::vector<std::vector<int>> lmap = std::vector<std::vector<int>>(cl, std::vector<int>());
        std::vector<int> lclasses(n);
        int lcl = 0, lcount = 0;

        for (int i = 0; i < n; ++i) {
            int x = (position[i] - pk + n) % n;
            lmap[classes[k][x]].push_back(x);
        }

        for (int i = 0; i < cl; ++i) {
            for (int j = 0; j < lmap[i].size(); ++j) {
                if (j == 0 || classes[k][(lmap[i][j] + pk) % n] != classes[k][(lmap[i][j - 1] + pk) % n]) {
                    lcl++;
                }
                lclasses[lmap[i][j]] = lcl - 1;
                position[lcount] = lmap[i][j];
                lcount++;
            }
        }
        classes[k + 1] = lclasses;
        cl = lcl;
    }

    std::vector<int> truthposition;
    truthposition.reserve(n);
    truthposition.push_back(0);
    for (int i = 1; i < n; ++i) {
        if (lcp(classes, position[i], position[i - 1]) < n) {
            truthposition.push_back(i);
        }
    }

    int k;
    std::cin >> k;

    if (truthposition.size() < k || position.size() < truthposition[k - 1]) {
        std::cout << "IMPOSSIBLE";
        return 0;
    }
    
    std::cout << s.substr(position[truthposition[k - 1]], n);

    return 0;
}