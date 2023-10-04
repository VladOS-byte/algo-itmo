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
    std::string s, t;
    std::cin >> s >> t;

    int len = s.length();

    s += char('a' - 1) + t + char('a' - 2);
    int n = s.length();

    pow = 0;
    while (n > (1 << pow)) {
        pow++;
    }

    std::vector<std::vector<int>> map = std::vector<std::vector<int>>(30, std::vector<int>());
    std::vector<std::vector<int>> classes(pow + 1, std::vector<int>(n));
    std::vector<int> position(n);
    int cl = 0, count = 0;

    for (int i = 0; i < n; ++i) {
        map[s[i] - 'a' + 2].push_back(i);
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

    int answer = INT32_MIN;
    int lanswer = INT32_MIN;
    int prev_j = 0;
    int poz = 0;
    for (int i = 0, j = 0; i < n && j < n;) {
        while (i < n && position[i] >= len) {
            i++;
        }
        while (j < n && position[j] <= len) {
            j++;
        }
        if (i < n && j < n) {
            int tmp = lcp(classes, position[i], position[j]);
            if (tmp > lanswer || (tmp == lanswer && s[position[i] + tmp] > s[position[j] + tmp])) {
                lanswer = tmp;
                if (lanswer > answer) {
                    answer = lanswer;
                    poz = position[i];
                }
                prev_j = j;
                j++;
            } else {
                j = prev_j;
                i++;
                lanswer = INT32_MIN;
            }
        }
    }

//    std::cout << answer;
    std::cout << s.substr(poz, answer);

    return 0;
}