#include <iostream>
using namespace std;

const int N = 1e6 + 1;

struct Node {
    int data;
    Node *next;
};

struct Stack {
    Node *head;
    Node *tail;
    int size = 0;
    Node *mins[N];
    int sizeMin = 0;
};

void push(Stack *s){
    Node *node = new Node;
    int value;
    cin >> value;
    node->data = value;
    if(s->size++ == 0) {
        s->tail = node;
    } else {
        node->next = s->head;
    }
    s->head = node;
    if(s->sizeMin == 0) {
        s->mins[s->sizeMin++] = node;
    } else if(s->mins[s->sizeMin - 1]->data > value) {
        s->mins[s->sizeMin++] = node;
    }
}
void pop(Stack *s) {
    if(s->head == s->mins[s->sizeMin - 1]) {
        s->sizeMin--;
    }
    s->head = s->head->next;
    s->size--;
}
int getMin(Stack *s) {
    return s->mins[s->sizeMin - 1]->data;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, operation, x;
    cin >> n;
    int size = 0;
    Stack *stack = new Stack;
    for (int i = 0; i < n; ++i) {
        cin >> operation;
        if(operation == 1) {
            push(stack);
            continue;
        }
        if(operation == 2) {
            pop(stack);
            continue;
        }
        if(operation == 3) {
            cout << getMin(stack) << endl;
        }
    }
    return 0;
}