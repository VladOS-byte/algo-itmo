#include <iostream>
#include <math.h>
using namespace std;

int gcd(int a, int b) {
    int c = b;
    int d = a;
    while (c > 0 && d > 0) {
        if (c > d) {
            c = c % d;
        } else {
            d = d % c;
        }
    }
    return a * b / (c + d);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, x, y;
    int t = 0;
    cin >> n >> x >> y;
    n--;
    t = min(x, y);
    y = max(x, y);
    x = t;
    int gcdXY = gcd(x, y);
    int speedX = gcdXY / x;
    int speedY = gcdXY / y;
    int speed = speedX + speedY;
    t += (n / speed) * gcdXY;
    n = n % speed;
    int t1 = 0;
    int t2 = 0;
    while (n > 0) {
        if (t1 > t2) {
            t2 += y;
            n--;
        } else {
            t1 += x;
            n--;
        }
    }
    t += max(t1, t2);
    cout << t;
    return 0;
}