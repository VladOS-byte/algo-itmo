#include <iostream>
using namespace std;

struct Node {
    long long data;
    Node *next;
};

struct Stack {
    Node *head;
    int size = 0;
};

void push(Stack *s, long long value){
    Node *node = new Node;
    node->data = value;
    if(s->size++ != 0) {
        node->next = s->head;
    }
    s->head = node;
}

long long pop(Stack *s) {
    long long value = s->head->data;
    s->head = s->head->next;
    s->size--;
    return value;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    long long value;
    string str;
    Stack *stack = new Stack;
    while (cin >> str) {
        if(str.length() > 1) {
            value = atoll(str.c_str());
            push(stack, value);
            continue;
        }
        switch (str[0]) {
            case '+': {
                push(stack, pop(stack) + pop(stack));
                continue;
            }
            case '*': {
                push(stack, pop(stack) * pop(stack));
                continue;
            }
            case '-': {
                value = pop(stack);
                push(stack,  pop(stack) - value);
                continue;
            }
            default: {
                value = atoll(str.c_str());
                push(stack, value);
            }
        }

    }
    cout << pop(stack);
    return 0;
}
//700 635 7 1 - / + 1 4 + / z