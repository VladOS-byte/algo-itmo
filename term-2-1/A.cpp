#include <iostream>

using namespace std;

int main() {
    long long n, x, y, m, z, t, h;
    cin >> n >> x >> y;
    long long a[n];
    cin >> a[0];
    long long b[2];
    cin >> m >> z >> t >> b[0];
    b[1] = (z * b[0] + t + (1 << 30)) % (1 << 30);
    h = a[0];
    for (int i = 1; i < n; ++i) {
        h = (x * h + y + (1 << 16)) % (1 << 16);
        a[i] = h + a[i - 1];
    }
    long long sum = 0;
    long long sums = 0;
    for (int i = 0; i < m; ++i) {
        int right = max(b[0] % n, b[1] % n);
        int left = min(b[0] % n, b[1] % n);
        sum = a[right];
        if (left > 0) {
            sum -= a[left - 1];
        }
        sums += sum;
        b[0] = (z * b[1] + t + (1 << 30)) % (1 << 30);
        b[1] = (z * b[0] + t + (1 << 30)) % (1 << 30);
    }
    cout << sums;
    return 0;
}