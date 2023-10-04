#include <iostream>
#include <vector>
using namespace std;

int mas[100001]{0};
int size = 0;
void siftDown() {
    int i = 0;
    while (i * 2 + 1 < size) {
        if (i * 2 + 2 < size && mas[i * 2 + 2] > mas[i] && mas[i * 2 + 2] > mas[i * 2 + 1]) {
            swap(mas[i], mas[i * 2 + 2]);
            i = i * 2 + 2;
        } else {
            if (mas[i * 2 + 1] > mas[i]) {
                swap(mas[i], mas[i * 2 + 1]);
                i = i * 2 + 1;
            } else {
                break;
            }
        }
    }
}
void siftUp() {
    int i = size - 1;
    while (mas[i] > mas[(i - 1) / 2]) {
        swap(mas[i], mas[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
void insert(int x) {
    mas[size] = x;
    size++;
    siftUp();
}
int extract() {
    int x = mas[0];
    mas[0] = mas[size - 1];
    size--;
    siftDown();
    return x;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int command;
        cin >> command;
        if (command == 1) {
            cout << extract() << endl;
        } else {
            int x;
            cin >> x;
            insert(x);
        }
    }

    return 0;
}