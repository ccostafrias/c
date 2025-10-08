typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node;

void swap_pair(Node * prev, Node * actual) {
    if (!actual || !actual->next) return;

    Node * next = actual->next;
    Node * rest = next->next;

    if (prev) prev->next = next;

    next->next = actual;
    actual->next = rest;
}

Node * swapPairs(Node * head) {
    Node * realHead = head;
    Node * prev = NULL;
    Node * actual = realHead;
    int isFirst = 1;

    while (actual && actual->next) {
        Node * next = actual->next;
        swap_pair(prev, actual);
        
        if (isFirst) {
            isFirst = 0;
            realHead = next;
        }

        prev = next->next;
        actual = next->next->next;
    }

    return realHead;
}