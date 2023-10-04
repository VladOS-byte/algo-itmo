#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

struct Stack {
    Node *head;
    Node *tail;
    int size = 0;
};

void push(Stack *s, int value){
    Node *node = new Node;
    node->data = value;
    if(s->size++ == 0) {
        s->tail = node;
    } else {
        node->next = s->head;
    }
    s->head = node;
}
int pop(Stack *s) {
    int value = s->head->data;
    s->head = s->head->next;
    s->size--;
    return value;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    if(n < 3) {
        cout << 0;
        return 0;
    }
    Stack *stack = new Stack;
    int index = -1, count = 0, value = -1, x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        push(stack, x);
        if(value == x) {
            count++;
        } else {
            count = 1;
            value = x;
        }
        if(count >= 3) {
            index = n - i;
        }
    }
    Stack *st = new Stack;
    for (int i = 0; i < index; ++i) {
        push(st, pop(stack));
    }
    int k = 0;
    while(stack->size > 0 && st->size > 0) {
        value = pop(stack);
        count = 1;
        while(stack->size > 0) {
            x = pop(stack);
            if(x != value) {
                push(stack, x);
                break;
            }
            count++;
        }
        while(st->size > 0) {
            x = pop(st);
            if(x != value) {
                push(st, x);
                break;
            }
            count++;
        }
        if(count < 3) {
            break;
        }
        k += count;
    }
    cout << k;
    return 0;
}