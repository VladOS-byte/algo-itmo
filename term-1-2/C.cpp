#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next, *prev;
};

struct Stack {
    Node *head, *tail;
    int size = 0;
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
        s->head->prev = node;
    }
    s->head = node;
}

void popBack(Stack *s) {
    s->head = s->head->next;
    s->size--;
}

void popFront(Stack *s) {
    s->tail = s->tail->prev;
    s->size--;
}

void indexInQueue(Stack *s) {
    int id, index = 0;
    cin >> id;
    Node *node = s->tail;
    while(node->data != id && node != s->head) {
        node = node->prev;
        index++;
    }
    cout << index << endl;
}

void getId(Stack *s) {
    cout << s->tail->data << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, operation;
    cin >> n;
    Stack *stack = new Stack;
    for (int i = 0; i < n; ++i) {
        cin >> operation;
        switch(operation) {
            case 1: {
                push(stack);
                continue;
            }
            case 2: {
                popFront(stack);
                continue;
            }
            case 3: {
                popBack(stack);
                continue;
            }
            case 4: {
                indexInQueue(stack);
                continue;
            }
            case 5: {
                getId(stack);
                continue;
            }
            default: {
                continue;
            }
        }
    }

    return 0;
}
