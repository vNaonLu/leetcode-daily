#ifndef LIST_NODE_H__
#define LIST_NODE_H__
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class ListNode final {
 public:
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}

 private:
  static vector<vector<ListNode *>> memory_;

 public:
  inline static ListNode *generate(const vector<int> &v, const int repeat = -1) {
    if (v.size() == 0) return nullptr;
    ListNode *res = new ListNode(v[0]);
    ListNode *p = res;
    ListNode *rep = repeat == 0 ? res : nullptr;
    vector<ListNode *> mem(v.size(), nullptr);
    mem[0] = res;
    for (int i = 1; i < v.size(); ++i) {
      p->next = new ListNode(v[i]);
      p = p->next;
      if (repeat == i) rep = p;
      mem[i] = p;
    }

    if (rep != nullptr)
      p->next = rep;

    ListNode::memory_.push_back(mem);
    return res;
  }

  inline static void release(ListNode *p) {
    if (p == nullptr) return;
    for (auto mem = ListNode::memory_.begin(); mem != ListNode::memory_.end(); ++mem) {
      auto f = find((*mem).begin(), (*mem).end(), p);
      if (f != (*mem).end()) {
        for (auto it = (*mem).begin(); it != (*mem).end(); ++it) {
          delete *it;
          *it = nullptr;
        }
        ListNode::memory_.erase(mem);
        break;
      }
    }
  }

  inline static bool compare(ListNode *p, ListNode *q) {
    while (p != nullptr && q != nullptr) {
      if (p->val != q->val) return false;
      p = p->next;
      q = q->next;
    }
    return p == nullptr && q == nullptr;
  }
};

vector<vector<ListNode *>> ListNode::memory_ = {};

#endif