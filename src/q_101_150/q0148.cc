// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort List
//
// https://leetcode.com/problems/sort-list/
//
// Question ID: 148
// Difficult  : Medium
// Solve Date : 2021/10/20 13:51

#include "leetcode/list_node.h"
#include <algorithm>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |148. Sort List|:
//
// Given the |head| of a linked list, return the list after sorting it in
// ascending order.  
//

LEETCODE_BEGIN_RESOLVING(148, SortList, Solution);

class Solution {
private:
  ListNode *merge(ListNode *l1, ListNode *l2) {
    ListNode  dummy(0);
    ListNode *res = &dummy;
    while (l1 != nullptr && l2 != nullptr) {
      if (l1->val < l2->val) {
        res->next = l1;
        l1        = l1->next;
      } else {
        res->next = l2;
        l2        = l2->next;
      }
      res = res->next;
    }
    if (l1 != nullptr)
      res->next = l1;
    if (l2 != nullptr)
      res->next = l2;
    return dummy.next;
  }
  ListNode *sort(ListNode *beg, ListNode *end) {
    if (beg == end)
      return beg;
    ListNode *slow = beg, *fast = beg;
    while (fast != end && fast->next != end) {
      slow = slow->next;
      fast = fast->next->next;
    }
    ListNode *tmp = slow;
    slow          = slow->next;
    tmp->next     = nullptr;
    return merge(sort(beg, tmp), sort(slow, end));
  }

public:
  ListNode *sortList(ListNode *head) {
    if (head == nullptr)
      return nullptr;
    return sort(head, nullptr);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[0, 5 * 10⁴]|.
// * |-10⁵ <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [4,2,1,3]
// Output: [1,2,3,4]
//

LEETCODE_SOLUTION_UNITTEST(148, SortList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({4, 2, 1, 3} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 2, 3, 4} /*, looped_index*/);
  ListNode *actual   = solution->sortList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [-1,5,3,4,0]
// Output: [-1,0,3,4,5]
//

LEETCODE_SOLUTION_UNITTEST(148, SortList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head   = ListNode::FromVector({-1, 5, 3, 4, 0} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({-1, 0, 3, 4, 5} /*, looped_index*/);
  ListNode *actual = solution->sortList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #3]
//  Input: head = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(148, SortList, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({} /*, looped_index*/);
  ListNode *actual   = solution->sortList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}
