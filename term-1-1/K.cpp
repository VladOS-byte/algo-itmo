#include <iostream>

using namespace std;

int uk[1000001];

void qsort(double mas[], int l, int r, bool flag) {
    if (r - l <= 1) {
        if (r - l == 1 && mas[l] > mas[r]) {
            swap(mas[l], mas[r]);
            if (flag) {
                swap(uk[l], uk[r]);
            }
        }
        return;
    }
    double x = mas[(r + l) / 2];
    int i = l;
    int j = r;
    while (i <= j) {
        while (mas[i] < x) {
            i++;
        }
        while (mas[j] > x) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swap(mas[i], mas[j]);
        if (flag) {
            swap(uk[i], uk[j]);
        }
        i++;
        j--;
    }
    if (j > l) {
        qsort(mas, l, j, flag);
    }
    if (i < r) {
        qsort(mas, i, r, flag);
    }
}

bool f(double answer, int v[], int w[], int n, int k, bool flag) {
    double deltas[n];
    for (int i = 0; i < n; ++i) {
        deltas[i] = v[i] - answer * w[i];
    }
    qsort(deltas, 0, n - 1, flag);
    long double s = 0;
    for (int i = n - k; i < n; ++i) {
        s += deltas[i];
    }
    return s < 0;
}

void binSearchAnswers(int v[], int w[], int n, int k) {
    double l = 0;
    double r = INT32_MAX;
    double m = 0;
    while (r - l > 0.00001) {
        m = (r + l) / 2;
        if (f(m, v, w, n, k, false)) {
            r = m;
        } else {
            l = m;
        }
    }
    f(m, v, w, n, k, true);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    int v[n], w[n];
    for (int i = 0; i < n; ++i) {
        cin >> v[i] >> w[i];
        uk[i] = i + 1;
    }
    binSearchAnswers(v, w, n, k);
    double ukAnswer[k];
    for (int i = 0; i < k; ++i) {
        ukAnswer[i] = uk[i + n - k];
    }
    qsort(ukAnswer, 0, k - 1, false);
    for (int i = 0; i < k; ++i) {
        cout << ukAnswer[i] << endl;
    }
    return 0;
}

