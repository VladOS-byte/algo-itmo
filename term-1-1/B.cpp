#include <iostream>
#include <cmath>
using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int masSorted[101]{0};
    int a;
    while (cin.peek() != '\n') {
        cin >> a;
        masSorted[a]++;
    }
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < masSorted[i]; ++j) {
            cout << i << " ";
        }
    }
    return 0;
}