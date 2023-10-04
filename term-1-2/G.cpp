#include <iostream>

using namespace std;

struct Head {
    int index = 0;
    int min = 0;
    int max = 0;
    int count = 0;
};

int get(Head heads[], int a) {
    int head = a;
    while(heads[head].index != head) {
        head = heads[head].index;
    }
    int h;
    while(a != heads[a].index) {
        h = a;
        a = heads[a].index;
        heads[h].index = head;
    }
    return head;
}
void _union(Head heads[], int x, int y) {
    x = get(heads, x);
    y = get(heads, y);
    if(x == y) {
        return;
    }
    heads[x].min = min(heads[x].min, heads[y].min);
    heads[x].max = max(heads[x].max, heads[y].max);
    heads[x].count = heads[x].count + heads[y].count;
    heads[y].index = x;

}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    Head heads[n];
    for (int i = 0; i < n; ++i) {
        heads[i].index = i;
        heads[i].count = 1;
        heads[i].min = i;
        heads[i].max = i;
    }
    string s;
    int x, y;
    Head head;
    while(cin >> s) {
        if(s == "get") {
            cin >> x;
            head = heads[get(heads, x - 1)];
            cout << head.min + 1 << " " << head.max + 1 << " " << head.count << endl;
        } else {
            cin >> x >> y;
            _union(heads, x - 1, y - 1);
        }
    }
    return 0;
}

