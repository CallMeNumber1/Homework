/*************************************************************************
	> File Name: 6.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年02月13日 星期三 23时10分29秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;
Node *init(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    p->prev = NULL;
    return p;
}
Node *insert(Node *head, int val) {
    if (head == NULL) {
        head = init(val);
        head->next = head;
        head->prev = head;
    } else {
        Node *p = head;
        while (p->next != head) {
            p = p->next;
        }
        p->next = init(val);
        p->next->next = head;
        p->next->prev = p;
        head->prev = p->next;
    }
    return head;
}
Node *search(Node *head, int m) {
    Node *p = head->next;
    if (head->data == m) {
        return head;
    } else {
        while (p && p != head) {
            if (p->data == m) return p;
            p = p->next;
        }
    }
    return NULL;
}
int main() {
    int n, val, m;
    cin >> n;
    Node *head = NULL;
    for (int i = 0; i < n; i++) {
        cin >> val;
        head = insert(head, val);
    }
    cin >> m;
    Node *p = search(head, m), *pre = p;
    while (p->prev != pre) {
        cout << p->data << " ";
        p = p->prev;
    }
    cout << p->data << endl;
    return 0;
}

