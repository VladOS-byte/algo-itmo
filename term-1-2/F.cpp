#include <iostream>
using namespace std;

struct Node {
    long long data;
    Node *next, *prev;
};

struct Stack {
    Node *head;
    Node *tail;
    long long size = 0;
};

void push(Stack *s, long long value){
    Node *node = new Node;
    node->data = value;
    if(s->size++ == 0) {
        s->tail = node;
    } else {
        node->next = s->head;
        s->head->prev = node;
    }
    s->head = node;
}

long long popFront(Stack *s) {
    long long value = s->head->data;
    s->head = s->head->next;
    s->size--;
    return value;
}

long long popBack(Stack *s) {
    long long value = s->tail->data;
    s->tail = s->tail->prev;
    s->size--;
    return value;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    Stack *queue = new Stack;
    cin >> n;
    Stack *stack = new Stack;
    Stack *answer = new Stack;
    long long value = INT64_MAX, x, value1 = INT64_MAX;
    for (long long i = 0; i < n; ++i) {
        cin >> x;
        if(x <= value) {
            push(answer, x);
            push(queue, 1);
            value = x;
        } else {
            while(answer->size > 0) {
                value1 = answer->head->data;
                if(value1 > x) {
                    break;
                }
                push(stack, popFront(answer));
                push(queue, 0);
            }
            push(answer, x);
            push(queue, 1);
            value = x;
        }
    }
    value1 = INT64_MAX;
    while(answer->size > 0) {
        push(stack, popFront(answer));
        push(queue, 0);
    }
    while(stack->size > 0) {
        if(value1 < stack->head->data) {
            cout << "impossible";
            return  0;
        }
        value1 = popFront(stack);
        push(answer, value1);
    }
    while(queue->size > 0) {
        cout << (popBack(queue) == 0 ? "pop" : "push") << endl;
    }
    return 0;
}