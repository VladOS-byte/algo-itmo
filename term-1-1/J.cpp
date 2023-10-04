#include <iostream>
#include <cmath>
using namespace std;

double time(int up, int uf, double a, double x) {
    return sqrt((1 - a) * (1 - a) + x * x) / up + sqrt((1 - x) * (1 - x) + a * a) / uf;
}

double root(int up, int uf, double a) {
    double l = 0;
    double r = 1;
    for (int i = 0; i < 35; ++i) {
        double m1 = (r - l) / 3 + l;
        double m2 = 2 * (r - l) / 3 + l;
        double t1 = time(up, uf, a, m1);
        double t2 = time(up, uf, a, m2);
        if (t1 < t2) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return (r + l) / 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int up, uf;
    double a;
    cin >> up >> uf >> a;
    printf("%.5f", root(up, uf, a));
    return 0;
}