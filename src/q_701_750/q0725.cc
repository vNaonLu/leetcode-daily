// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Split Linked List in Parts
//
// https://leetcode.com/problems/split-linked-list-in-parts/
//
// Question ID: 725
// Difficult  : Medium
// Solve Date : 2021/09/29 17:00

#include "leetcode/list_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |725. Split Linked List in Parts|:
//
// Given the |head| of a singly linked list and an integer |k|, split the linked
// list into |k| consecutive linked list parts. The length of each part should
// be as equal as possible: no two parts should have a size differing by more
// than one. This may lead to some parts being null. The parts should be in the
// order of occurrence in the input list, and parts occurring earlier should
// always have a size greater than or equal to parts occurring later. Return an
// array of the |k| parts.  
//

LEETCODE_BEGIN_RESOLVING(725, SplitLinkedListInParts, Solution);

class Solution {
public:
  vector<ListNode *> splitListToParts(ListNode *head, int k) {
    int       cnt = 0;
    ListNode *p = head, *q = nullptr;
    while (p != nullptr) {
      ++cnt;
      p = p->next;
    }
    vector<ListNode *> res;
    int                split = cnt / k, left = cnt % k;
    p = head;
    for (int i = 0; i < k; ++i) {
      q       = p;
      int cur = split + (left > 0 ? 1 : 0) - 1;
      --left;
      while (p != nullptr && cur > 0) {
        --cur;
        p = p->next;
      }
      res.push_back(q);
      if (p != nullptr) {
        q       = p;
        p       = p->next;
        q->next = nullptr;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[0, 1000]|.
// * |0 <= Node.val <= 1000|
// * |1 <= k <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3], k = 5
// Output: [[1],[2],[3],[],[]]
//
// The first element output[0] has output[0].val = 1, output[0].next = null.
// The last element output[4] is null, but its string representation as a
// ListNode is [].

LEETCODE_SOLUTION_UNITTEST(725, SplitLinkedListInParts, example_1) {
  auto               solution = MakeSolution();
  ListNode          *head = ListNode::FromVector({1, 2, 3} /*, looped_index*/);
  int                k    = 5;
  vector<ListNode *> expect = {ListNode::FromVector({1} /*, looped_index*/),
                               ListNode::FromVector({2} /*, looped_index*/),
                               ListNode::FromVector({3} /*, looped_index*/),
                               ListNode::FromVector({} /*, looped_index*/),
                               ListNode::FromVector({} /*, looped_index*/)};
  vector<ListNode *> actual = solution->splitListToParts(head, k);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
  ListNode::ReleaseRange(expect.begin(), expect.end());
  ListNode::ReleaseRange(actual.begin(), actual.end());
}

// [Example #2]
//  Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
// Output: [[1,2,3,4],[5,6,7],[8,9,10]]
//
// The input has been split into consecutive parts with size difference at most
// 1, and earlier parts are a larger size than the later parts.

LEETCODE_SOLUTION_UNITTEST(725, SplitLinkedListInParts, example_2) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10} /*, looped_index*/);
  int                k      = 3;
  vector<ListNode *> expect = {
      ListNode::FromVector({1, 2, 3, 4} /*, looped_index*/),
      ListNode::FromVector({5, 6, 7} /*, looped_index*/),
      ListNode::FromVector({8, 9, 10} /*, looped_index*/)};
  vector<ListNode *> actual = solution->splitListToParts(head, k);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
  ListNode::ReleaseRange(expect.begin(), expect.end());
  ListNode::ReleaseRange(actual.begin(), actual.end());
}
