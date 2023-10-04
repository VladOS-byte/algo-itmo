#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return x * x + sqrt(x);
}

double lower_bound(double l, double r, double c) {
    double eps = 0.0000001;
    while (r - l > eps) {
        double m = (r + l) / 2;
        if (f(m) < c) {
            l = m;
        } else {
            r = m;
        }
    }
    return (r + l) / 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    double c;
    cin >> c;
    double m = sqrt(c);
    printf("%.7f", lower_bound(floor(m) - 1, ceil(m), c));
    return 0;
}