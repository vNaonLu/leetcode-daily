// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Merge Two Sorted Lists
//
// https://leetcode.com/problems/merge-two-sorted-lists/
//
// Question ID: 21
// Difficult  : Easy
// Solve Date : 2021/09/11 08:00

#include "leetcode/list_node.h"
#include <iosfwd>
#include <list>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |21. Merge Two Sorted Lists|:
//
// You are given the heads of two sorted linked lists |list1| and |list2|.
// Merge the two lists in a one sorted list. The list should be made by splicing
// together the nodes of the first two lists. Return the head of the merged
// linked list.  
//

LEETCODE_BEGIN_RESOLVING(21, MergeTwoSortedLists, Solution);

class Solution {
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    auto dummy = ListNode{};
    auto p     = &dummy;

    while (nullptr != list1 && nullptr != list2) {
      auto &smaller = list1->val > list2->val ? list2 : list1;
      p->next       = smaller;
      p             = p->next;
      smaller       = smaller->next;
    }

    if (nullptr != list1) {
      p->next = list1;
    }
    if (nullptr != list2) {
      p->next = list2;
    }

    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in both lists is in the range |[0, 50]|.
// * |-100 <= Node.val <= 100|
// * Both |list1| and |list2| are sorted in non-decreasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: list1 = [1,2,4], list2 = [1,3,4]
// Output: [1,1,2,3,4,4]
//

LEETCODE_SOLUTION_UNITTEST(21, MergeTwoSortedLists, example_1) {
  auto      solution = MakeSolution();
  ListNode *list1    = ListNode::FromVector({1, 2, 4} /*, looped_index*/);
  ListNode *list2    = ListNode::FromVector({1, 3, 4} /*, looped_index*/);
  ListNode *expect =
      ListNode::FromVector({1, 1, 2, 3, 4, 4} /*, looped_index*/);
  ListNode *actual = solution->mergeTwoLists(list1, list2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(list1, list2);
}

// [Example #2]
//  Input: list1 = [], list2 = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(21, MergeTwoSortedLists, example_2) {
  auto      solution = MakeSolution();
  ListNode *list1    = ListNode::FromVector({} /*, looped_index*/);
  ListNode *list2    = ListNode::FromVector({} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({} /*, looped_index*/);
  ListNode *actual   = solution->mergeTwoLists(list1, list2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(list1, list2);
}

// [Example #3]
//  Input: list1 = [], list2 = [0]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(21, MergeTwoSortedLists, example_3) {
  auto      solution = MakeSolution();
  ListNode *list1    = ListNode::FromVector({} /*, looped_index*/);
  ListNode *list2    = ListNode::FromVector({0} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({0} /*, looped_index*/);
  ListNode *actual   = solution->mergeTwoLists(list1, list2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(list1, list2);
}
