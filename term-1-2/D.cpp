#include <iostream>
using namespace std;

struct Node {
    long long data;
    Node *next, *prev;
};

struct Stack {
    Node *head;
    Node *tail, *middle;
    long long size = 0;
};

void push(Stack *s){
    Node *node = new Node;
    long long value;
    cin >> value;
    node->data = value;
    if(s->size++ == 0) {
        s->tail = node;
        s->middle = node;
    } else {
        node->next = s->head;
        s->head->prev = node;
    }
    if(s->size % 2 == 0) {
        s->middle = s->middle->prev;
    }
    s->head = node;
}

void pop(Stack *s) {
    long long value = s->tail->data;
    if(s->size % 2 == 1 && s->size > 1) {
        s->middle = s->middle->prev;
    }
    s->tail = s->tail->prev;
    s->size--;
    cout << value << endl;
}

void pushToMiddle(Stack *s) {
    Node *node = new Node;
    long long value;
    cin >> value;
    node->data = value;
    if(s->size++ == 0) {
        s->tail = node;
        s->middle = node;
    } else if(s->size % 2 == 0) {
        node->next = s->middle;
        node->prev = s->middle->prev;
        s->middle->prev = node;
        if(s->size > 2) {
            node->prev->next = node;
        }
    } else {
        node->prev = s->middle;
        node->next = s->middle->next;
        s->middle->next = node;
        if(s->size > 2) {
            node->next->prev = node;
        }
    }
    if(s->size <= 2) {
        s->head = node;
    }
    s->middle = node;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    Stack *stack = new Stack;
    char x;
    for (long long i = 0; i < n; ++i) {
        cin >> x;
        switch(x) {
            case '-': {
                pop(stack);
                continue;
            }
            case '+': {
                push(stack);
                continue;
            }
            case '*': {
                pushToMiddle(stack);
                continue;
            }
            default:{}
        }
    }

    return 0;
}