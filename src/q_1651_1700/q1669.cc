// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Merge In Between Linked Lists
//
// https://leetcode.com/problems/merge-in-between-linked-lists/
//
// Question ID: 1669
// Difficult  : Medium
// Solve Date : 2024/03/20 20:16

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1669. Merge In Between Linked Lists|:
//
// You are given two linked lists: |list1| and |list2| of sizes |n| and |m|
// respectively. Remove |list1|'s nodes from the |aᵗʰ| node to the |bᵗʰ| node,
// and put |list2| in their place. The blue edges and nodes in the following
// figure indicate the result:
// ![img](https://assets.leetcode.com/uploads/2020/11/05/fig1.png)
// Build the result list and return its head.
//
//

LEETCODE_BEGIN_RESOLVING(1669, MergeInBetweenLinkedLists, Solution);

class Solution {
public:
  ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2) {
    auto *head = list1;
    auto *curr = list1;
    for (int i = 1; i < a; ++i) {
      curr = curr->next;
    }

    auto *rm_start = curr;
    auto *rm_end   = curr->next;

    for (int i = a; i <= b; ++i) {
      auto *tmp = rm_end;
      rm_end    = rm_end->next;
      delete tmp;
    }

    rm_start->next = list2;
    while (curr->next) {
      curr = curr->next;
    }

    curr->next = rm_end;
    return head;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= list1.length <= 10⁴|
// * |1 <= a <= b < list1.length - 1|
// * |1 <= list2.length <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 =
//  [1000000,1000001,1000002]
// Output: [10,1,13,1000000,1000001,1000002,5]
//

LEETCODE_SOLUTION_UNITTEST(1669, MergeInBetweenLinkedLists, example_1) {
  auto      solution = MakeSolution();
  ListNode *list1 =
      ListNode::FromVector({10, 1, 13, 6, 9, 5} /*, looped_index*/);
  int       a = 3;
  int       b = 4;
  ListNode *list2 =
      ListNode::FromVector({1000000, 1000001, 1000002} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector(
      {10, 1, 13, 1000000, 1000001, 1000002, 5} /*, looped_index*/);
  ListNode *actual = solution->mergeInBetween(list1, a, b, list2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(list1, list2, expect, actual);
}

// [Example #2]
//  Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 =
//  [1000000,1000001,1000002,1000003,1000004]
// Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
//

LEETCODE_SOLUTION_UNITTEST(1669, MergeInBetweenLinkedLists, example_2) {
  auto      solution = MakeSolution();
  ListNode *list1 =
      ListNode::FromVector({0, 1, 2, 3, 4, 5, 6} /*, looped_index*/);
  int       a     = 2;
  int       b     = 5;
  ListNode *list2 = ListNode::FromVector(
      {1000000, 1000001, 1000002, 1000003, 1000004} /*, looped_index*/);
  ListNode *expect =
      ListNode::FromVector({0, 1, 1000000, 1000001, 1000002, 1000003, 1000004,
                            6} /*, looped_index*/);
  ListNode *actual = solution->mergeInBetween(list1, a, b, list2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(list1, list2, expect, actual);
}
