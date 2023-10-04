#include<iostream>
#include<vector>
#include<complex>
#include<cmath>
#include<string>

double pi = 3.14159265358979323846;

void fourierTransform (std::vector<std::complex<double>> & a, bool invert) {
    if (a.size() == 1)  {
        return;
    }

    int n = a.size();

    std::vector<std::complex<double>> a0,  a1;
    a0.reserve(n / 2);
    a1.reserve(n / 2);

    for (int i = 0; i < n; i += 2) {
        a0.push_back(a[i]);
    }

    for (int i = 0; i < n; i += 2) {
        a1.push_back(a[i + 1]);
    }

    fourierTransform(a0, invert);
    fourierTransform(a1, invert);

    std::complex<double> w(1);

    double degree = 2 * pi / n * (invert ? -1 : 1);
    std::complex<double> wn (cos(degree), sin(degree));

    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

std::vector<int> readV(std::string & s) {
    int m = 1;
    while (m < s.size())  {
        m <<= 1;
    }

    m <<= 1;

    std::vector<int> a;
    a.reserve(m);

    for (char i : s) {
        int d = i - '0';
        a.push_back(d);
    }

    for (int i = s.size(); i < m; ++i) {
        a.push_back(0);
    }

    return a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::string s;
    std::cin >> s;

    std::vector<int> a = readV(s);

    std::vector<int> answer = {};

    std::vector<std::complex<double>> fa (a.begin(), a.end());

    fourierTransform(fa, false);

    for (auto & i : fa) {
        i *= i;
    }

    fourierTransform(fa, true);

    answer.reserve(fa.size());
    for (auto & i : fa) {
        answer.push_back(int(std::floor(i.real() + 0.5)));
    }

    long long ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') {
            ans += answer[i << 1] / 2;
        }
    }

    std::cout << ans;
    return 0;
}
