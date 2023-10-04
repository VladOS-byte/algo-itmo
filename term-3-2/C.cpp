#include <iostream>
#include <vector>
#include <algorithm>

int edges[100][100];

std::vector<int> bfs(char size) {
    int d[size];
    char p[size];
    for (int i = 0; i < size; ++i) {
        d[i] = 100001;
        p[i] = -1;
    }
    d[0] = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                if (edges[j][k] != 100000 && d[k] > d[j] + edges[j][k]) {
                    d[k] = d[j] + edges[j][k];
                    p[k] = j;
                }
            }
        }
    }
    std::vector<int> path;
    for (int j = 0; j < size; ++j) {
        for (int k = 0; k < size; ++k) {
            if (edges[j][k] != 100000 && d[k] > d[j] + edges[j][k]) {
                int v = k;
                for (int i = 0; i < size; ++i) {
                    v = p[v];
                }
                int u = v;
                while (u != p[v]) {
                    v = p[v];
                    path.push_back(v);
                }
                path.push_back(u);
                std::reverse(path.begin(), path.end());
                return path;
            }
        }
    }
    return path;
}

int main() {
    int n;
    std::cin >> n;

    int cost;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> cost;
            edges[i][j] = cost;
        }
    }

    std::vector<int> v = bfs(n);
    if (v.empty()) {
        std::cout << "NO";
    } else {
        std::cout << "YES" << std::endl << v.size() << std::endl;
        for (int i : v) {
            std::cout << i + 1 << " ";
        }
    }

    return 0;
}
