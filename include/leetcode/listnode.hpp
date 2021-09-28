#ifndef LIST_NODE_H__
#define LIST_NODE_H__
#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

class ListNode final {
 private:
  bool generate_by_test;
  ListNode(int x, const bool &gbt) : val(x),
                                     next(nullptr),
                                     generate_by_test(gbt) {}

 public:
  int val;
  ListNode *next;
  ListNode() : val(0),
               next(nullptr),
               generate_by_test(false) {}
  ListNode(int x) : val(x),
                    next(nullptr),
                    generate_by_test(false) {}
  ListNode(int x, ListNode *next) : val(x),
                                    next(next),
                                    generate_by_test(false) {}

  ~ListNode() {}

 private:
  static vector<vector<ListNode>>
      keep_;

  static ListNode *build_list_(vector<ListNode> &v, const int &repeat) {
    for (int i = 0; i < v.size() - 1; ++i)
      v[i].next = &v[i + 1];
    if (repeat >= 0) v.back().next = &v[repeat];
    return &v.front();
  }

 public:
  bool operator==(const ListNode &rhs) const {
    return val == rhs.val &&
           (next == nullptr ? rhs.next == nullptr : (rhs.next == nullptr ? false : *next == *(rhs.next)));
  }

  inline static ListNode *generate(const vector<int> &v, const int &repeat = -1) {
    assert(repeat == -1 || repeat < v.size());
    if (v.empty()) return nullptr;
    keep_.push_back({});
    vector<ListNode> &dummy = keep_.back();
    for (int i = 0; i < v.size(); ++i)
      dummy.push_back(ListNode(v[i], true));
    return build_list_(dummy, repeat);
  }

  inline static void release(initializer_list<ListNode *> p) {
    for (auto node : p) {
      vector<ListNode *> cand;
      ListNode *q = node;
      while (q != nullptr) {
        if (!q->generate_by_test)
          cand.push_back(q);
        q = q->next;
      }
      for (auto candtodel : cand)
        delete candtodel;
    }
  }
};

vector<vector<ListNode>> ListNode::keep_ = {};

#ifdef EXPECT_EQ
#define EXPECT_LISTNODE_EQ(val1, val2)          \
  ListNode *actual = val1, *expect = val2;      \
  if (actual != nullptr && expect != nullptr) { \
    EXPECT_EQ(*actual, *expect);                \
  } else {                                      \
    EXPECT_EQ(actual, expect);                  \
  }                                             \
  ListNode::release({actual, expect});
#endif

#endif