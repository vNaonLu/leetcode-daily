// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rotate List
//
// https://leetcode.com/problems/rotate-list/
//
// Question ID: 61
// Difficult  : Medium
// Solve Date : 2021/12/21 14:34

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |61. Rotate List|:
//
// Given the |head| of a linked list, rotate the list to the right by |k|
// places.  
//

LEETCODE_BEGIN_RESOLVING(61, RotateList, Solution);

class Solution {
public:
  ListNode *rotateRight(ListNode *head, int k) {
    if (head == nullptr)
      return head;
    int   n = 0;
    auto *p = head, *last = head;
    while (p) {
      n++;
      last = p;
      p    = p->next;
    }

    int cnt = n - k % n;

    if (cnt == n)
      return head;
    int   cur     = 1;
    auto *newLast = head;
    while (cur < cnt) {
      cur++;
      newLast = newLast->next;
    }
    p             = newLast->next;
    newLast->next = nullptr;
    last->next    = head;

    return p;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[0, 500]|.
// * |-100 <= Node.val <= 100|
// * |0 <= k <= 2 * 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4,5], k = 2
// Output: [4,5,1,2,3]
//

LEETCODE_SOLUTION_UNITTEST(61, RotateList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  int       k        = 2;
  ListNode *expect   = ListNode::FromVector({4, 5, 1, 2, 3} /*, looped_index*/);
  ListNode *actual   = solution->rotateRight(head, k);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [0,1,2], k = 4
// Output: [2,0,1]
//

LEETCODE_SOLUTION_UNITTEST(61, RotateList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({0, 1, 2} /*, looped_index*/);
  int       k        = 4;
  ListNode *expect   = ListNode::FromVector({2, 0, 1} /*, looped_index*/);
  ListNode *actual   = solution->rotateRight(head, k);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}
