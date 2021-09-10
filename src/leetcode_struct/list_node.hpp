#ifndef LIST_NODE_H__
#define LIST_NODE_H__
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

inline ListNode *generateListNode(const vector<int> &v) {
  if (v.size() == 0) return nullptr;
  ListNode *res = new ListNode(v[0]);
  ListNode *p = res;
  for (int i = 1; i < v.size(); ++i) {
    p->next = new ListNode(v[i]);
    p = p->next;
  }
  return res;
}

inline bool compareListNode(ListNode *p, ListNode *q) {
  while (p != nullptr && q != nullptr) {
    if (p->val != q->val) return false;
    p = p->next;
    q = q->next;
  }
  return p == nullptr && q == nullptr;
}

void releaseListNode(ListNode *p) {
  if (!p) return;
  releaseListNode(p->next);
  delete p;
}

#endif