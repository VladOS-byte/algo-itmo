#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long w, h, n;
    cin >> w >> h >> n;
    long long square = w * h;
    long long size = ceil(sqrt(square) * sqrt(n));
    size = max(max(size, h), w);
    size = (floor(size / min(w, h))) * min(w, h);
    while (floor(size / w) * floor(size / h) < n) {
        size = min((floor(size / min(w, h)) + 1) * min(w, h), (floor(size / max(w, h)) + 1) * max(w, h));
    }

    cout << size;
    return 0;
}