#include <iostream>
#include <math.h>
using namespace std;

void mergeSort(int mas[], int n) {
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n; j += 2 * i) {
            int l = j;
            int m = l + i;
            int r = m + i;
            int a = 0;
            int b = 0;
            int masSorted[r-l];
            while (a + l < m || b + m < r) {
                if (a + l == m) {
                    masSorted[a + b] = mas[b + m];
                    b++;
                    continue;
                }
                if (b + m == r) {
                    masSorted[a + b] = mas[a + l];
                    a++;
                    continue;
                }
                if (mas[a + l] > mas[b + m]) {
                    masSorted[a + b] = mas[b + m];
                    b++;
                } else {
                    masSorted[a + b] = mas[a + l];
                    a++;
                }
            }
            for (int k = 0; k < r - l; ++k) {
                mas[l + k] = masSorted[k];
            }
        }
    }
}

int lower_bound(int mas[], int x, int n) {
    int l = -1;
    int r = n;
    while (r - l > 1) {
        int m = (r + l) / 2;
        if (mas[m] < x) {
            l = m;
        } else {
            r = m;
        }
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int lgn = log2(n);
    lgn = 1<<lgn;
    if (lgn < n) {
        lgn *= 2;
    }
    int mas[lgn];
    for (int i = 0; i < n; ++i) {
        cin >> mas[i];
    }
    for (int i = n; i < lgn; ++i) {
        mas[i] = 1000000001;
    }
    mergeSort(mas, lgn);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r;
        cin >> l >> r;
        r++;
        r = lower_bound(mas, r, n);
        l = lower_bound(mas, l, n);
        cout << r - l << " ";
    }
    
    return 0;
}