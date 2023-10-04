#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>

std::pair<long long, long long> get_pow(long long n){
    long long s = n;
    long long pow = 0;
    while (!(s & 1)) {
        s >>= 1;
        pow++;
    }
    return {s, pow};
}

long long gcd(long long a, long long b){
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
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

bool testFerma(long long x){
    if (x == 1) {
        return false;
    }

    if (x == 2) {
        return true;
    }

    srand(time(NULL));

    auto p = get_pow(x - 1);

    for(int i = 0; i < 3; ++i){
        long long a = (rand() % (x - 2)) + 2;
        if (gcd(a, x) != 1) {
            return false;
        }

        auto cur = binary_pow(a, p.first, x);
        if (cur == 1 || cur == x - 1) {
            continue;
        }

        for (int j = 1; j < p.second; j++) {
            cur = binary_pow(cur, 2, x);
            if (cur == x - 1) {
                break;
            }
        }

        if (cur != x - 1) {
            return false;
        }

    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        long long c;
        std::cin >> c;

        if (testFerma(c)) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }

    return 0;
}
