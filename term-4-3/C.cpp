#include<iostream>

long long gcd(long long a, long long b, std::pair<long long, long long> & xy){
    if (a == 0) {
        xy = {0, 1};
        return b;
    }
    long long d = gcd(b % a, a, xy);
    xy = {xy.second - (b / a) * xy.first, xy.first};
    return d;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    long long a, b, n, m;
    std::cin >> a >> b >> n >> m;
    // ny + mz = g(n, m)
    // x = a + yn
    std::pair<long long, long long> xy = {};
    gcd(n, m, xy);

    long long x = a + xy.first * (b - a) * n;

    while (x < 0) {
        x += n * m;
    }

    while (x > n * m) {
        x -= n * m;
    }

    std::cout << x;

    return 0;
}
