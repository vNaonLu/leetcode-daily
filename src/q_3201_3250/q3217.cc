// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Delete Nodes From Linked List Present in Array
//
// https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/
//
// Question ID: 3217
// Difficult  : Medium
// Solve Date : 2024/09/06 23:03

#include "leetcode/list_node.h"
#include <iosfwd>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3217. Delete Nodes From Linked List Present in Array|:
//
// You are given an array of integers |nums| and the |head| of a linked list.
// Return the |head| of the modified linked list after removing all nodes from
// the linked list that have a value that exists in |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(3217, DeleteNodesFromLinkedListPresentInArray,
                         Solution);

class Solution {
public:
  ListNode *modifiedList(vector<int> &nums, ListNode *head) {
    unordered_set<int> m(nums.begin(), nums.end());
    ListNode           res;
    auto              *p = &res;
    while (head) {
      if (!m.count(head->val)) {
        p->next = head;
        p       = p->next;
      }
      auto *q = head;
      head    = head->next;
      q->next = nullptr;
    }
    return res.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
// * All elements in |nums| are unique.
// * The number of nodes in the given list is in the range |[1, 10⁵]|.
// * |1 <= Node.val <= 10⁵|
// * The input is generated such that there is at least one node in the linked
// list that has a value not present in |nums|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3], head = [1,2,3,4,5]
// Output: [4,5]
//

LEETCODE_SOLUTION_UNITTEST(3217, DeleteNodesFromLinkedListPresentInArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  ListNode   *head   = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  ListNode   *expect = ListNode::FromVector({4, 5} /*, looped_index*/);
  ListNode   *actual = solution->modifiedList(nums, head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::ReleaseAll();
}

// [Example #2]
//  Input: nums = [1], head = [1,2,1,2,1,2]
// Output: [2,2,2]
//

LEETCODE_SOLUTION_UNITTEST(3217, DeleteNodesFromLinkedListPresentInArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  ListNode *head = ListNode::FromVector({1, 2, 1, 2, 1, 2} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({2, 2, 2} /*, looped_index*/);
  ListNode *actual = solution->modifiedList(nums, head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::ReleaseAll();
}

// [Example #3]
//  Input: nums = [5], head = [1,2,3,4]
// Output: [1,2,3,4]
//

LEETCODE_SOLUTION_UNITTEST(3217, DeleteNodesFromLinkedListPresentInArray,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5};
  ListNode   *head     = ListNode::FromVector({1, 2, 3, 4} /*, looped_index*/);
  ListNode   *expect   = ListNode::FromVector({1, 2, 3, 4} /*, looped_index*/);
  ListNode   *actual   = solution->modifiedList(nums, head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::ReleaseAll();
}

// [Extra Testcase #1]
//  Input: [9,2,5]
// [2,10,9]
// Output: [10]
//

LEETCODE_SOLUTION_UNITTEST(3217, DeleteNodesFromLinkedListPresentInArray,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 2, 5};
  ListNode   *head     = ListNode::FromVector({2, 10, 9} /*, looped_index*/);
  ListNode   *expect   = ListNode::FromVector({10} /*, looped_index*/);
  ListNode   *actual   = solution->modifiedList(nums, head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::ReleaseAll();
}
