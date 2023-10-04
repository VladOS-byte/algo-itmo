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

long long mul(long long a, long long b, long long module){
    if(b == 1)
        return a;
    if(b % 2 == 0){
        long long t = mul(a, b / 2, module);
        return (2 * t) % module;
    }
    return (mul(a, b - 1, module) + a) % module;
}

long long binary_pow(long long a, long long degree, long long module){
    if(degree == 0)
        return 1;
    if(degree % 2 == 0){
        long long t = binary_pow(a, degree / 2, module);
        return mul(t, t, module) % module;
    }
    return (mul(binary_pow(a, degree - 1, module), a, module)) % module;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    long long n, e, c;
    std::cin >> n >> e >> c;

    int i = 2;
    for (; i <= n; ++i) {
        if (n % i == 0) {
            break;
        }
    }

    long long module = (i - 1) * ((n / i) - 1);
    std::pair<long long, long long> xy = {};
    long long g = gcd(e, module, xy);

    xy.first /= g;

    if (xy.first < 0) {
        xy.first += module;
    }

    std::cout << binary_pow(c, xy.first, n);

    return 0;
}
