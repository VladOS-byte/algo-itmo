#include <iostream>

using namespace std;

int size = 0;

struct Head {
    int index = 0;
    int exp = 0;
};

int get(Head heads[], int a) {
    int head = a;
    int experiance = heads[a].exp;
    while(heads[head].index != head) {
        head = heads[head].index;
        experiance += heads[head].exp;
    }
    int h;
    while(a != heads[a].index) {
        h = a;
        experiance -= heads[a].exp;
        heads[a].exp += experiance - heads[head].exp;
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
    heads[y].index = size;
    heads[x].index = size++;
}

void add(Head heads[], int x, int v) {
    x = get(heads, x);
    heads[x].exp += v;
}

int getExp(Head heads[], int x) {
    int y = get(heads, x);
    if(x != y) {
        return heads[y].exp + heads[x].exp;
    } else {
        return heads[x].exp;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    size = n;
    Head heads[2 * n];
    for (int i = 0; i < 2 * n; ++i) {
        heads[i].index = i;
        heads[i].exp = 0;
    }
    string s;
    int x, y;
    while(m-- > 0) {
        cin >> s;
        if(s == "get") {
            cin >> x;
            x = getExp(heads, x - 1);
            cout << x << endl;
            continue;
        }
        if(s == "join") {
            cin >> x >> y;
            if(x != y) {
                _union(heads, x - 1, y - 1);
            }
            continue;
        }
        if(s == "add") {
            cin >> x >> y;
            add(heads, x - 1, y);
        }
    }
    return 0;
}