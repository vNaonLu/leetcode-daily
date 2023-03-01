// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reorder List
//
// https://leetcode.com/problems/reorder-list/
//
// Question ID: 143
// Difficult  : Medium
// Solve Date : 2021/10/01 12:06

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |143. Reorder List|:
//
// You are given the head of a singly linked-list. The list can be represented
// as: L₀ → L₁ → … → L^{n - 1} → Lₙ Reorder the list to be on the following
// form: L₀ → Lₙ → L₁ → L^{n - 1} → L₂ → L^{n - 2} → … You may not modify the
// values in the list's nodes. Only nodes themselves may be changed.  
//

LEETCODE_BEGIN_RESOLVING(143, ReorderList, Solution);

class Solution {
public:
  void reorderList(ListNode *head) {
    vector<int> arr;
    ListNode   *p = head;
    while (p != nullptr) {
      arr.push_back(p->val);
      p = p->next;
    }
    int i = 1, j = arr.size() - 1, cnt = 0;
    p = head;
    while (i <= j) {
      if (cnt++ % 2 == 0) {
        p->next = new ListNode(arr[j--]);
      } else {
        p->next = new ListNode(arr[i++]);
      }
      p = p->next;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[1, 5 * 10⁴]|.
// * |1 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4]
// Output: [1,4,2,3]
//

LEETCODE_SOLUTION_UNITTEST(143, ReorderList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 4, 2, 3} /*, looped_index*/);
  solution->reorderList(head);
  LCD_EXPECT_EQ(expect, head);
  ListNode::Release(head, expect);
}

// [Example #2]
//  Input: head = [1,2,3,4,5]
// Output: [1,5,2,4,3]
//

LEETCODE_SOLUTION_UNITTEST(143, ReorderList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 5, 2, 4, 3} /*, looped_index*/);
  solution->reorderList(head);
  LCD_EXPECT_EQ(expect, head);
  ListNode::Release(head, expect);
}
