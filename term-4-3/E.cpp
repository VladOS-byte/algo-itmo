#include<iostream>
#include<vector>
#include<complex>
#include<cmath>

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

std::vector<int> readV(int n) {
    std::vector<int> a;
    a.reserve(n + 1);

    for (int i = 0; i <= n; ++i) {
        int d;
        std::cin >> d;
        a.push_back(d);
    }

    return a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    std::vector<int> a = readV(n), b = readV(n);

    std::vector<int> answer = {};

    std::vector<std::complex<double>> fa (a.begin(), a.end()),  fb (b.begin(), b.end());

    int m = 1;
    while (m < std::max(a.size(), b.size()))  {
        m <<= 1;
    }

    m <<= 1;

    while (fa.size() < m) {
        fa.emplace_back(0);
    }

    while (fb.size() < m) {
        fb.emplace_back(0);
    }

    fourierTransform(fa, false);
    fourierTransform(fb, false);

    for (int i = 0; i <= m; ++i) {
        fa[i] *= fb[i];
    }

    fourierTransform(fa, true);

    answer.reserve(m);
    for (int i = 0; i < m; ++i) {
        answer.push_back(int(std::floor(fa[i].real() + 0.5)));
    }

    for (int i = 0; i <= 2 * n; ++i) {
        std::cout << answer[i] << " ";
    }

    return 0;
}
