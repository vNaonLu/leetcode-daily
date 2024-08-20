// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Linked List Components
//
// https://leetcode.com/problems/linked-list-components/
//
// Question ID: 817
// Difficult  : Medium
// Solve Date : 2024/08/20 20:03

#include "leetcode/list_node.h"
#include <iosfwd>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |817. Linked List Components|:
//
// You are given the |head| of a linked list containing unique integer values
// and an integer array |nums| that is a subset of the linked list values.
// Return the number of connected components in |nums| where two values are
// connected if they appear consecutively in the linked list.
//
//

LEETCODE_BEGIN_RESOLVING(817, LinkedListComponents, Solution);

class Solution {
public:
  int numComponents(ListNode *head, vector<int> &nums) {
    unordered_set<int> ss(nums.begin(), nums.end());
    unordered_set<int> res;
    int                prev = head->val;
    while (head) {
      if (ss.count(head->val)) {
        res.emplace(prev);
        head = head->next;
      } else {
        while (head && !ss.count(head->val)) {
          head = head->next;
        }
        if (head) {
          prev = head->val;
        }
      }
    }
    return res.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the linked list is |n|.
// * |1 <= n <= 10⁴|
// * |0 <= Node.val < n|
// * All the values |Node.val| are unique.
// * |1 <= nums.length <= n|
// * |0 <= nums[i] < n|
// * All the values of |nums| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [0,1,2,3], nums = [0,1,3]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(817, LinkedListComponents, example_1) {
  auto        solution = MakeSolution();
  ListNode   *head     = ListNode::FromVector({0, 1, 2, 3} /*, looped_index*/);
  vector<int> nums     = {0, 1, 3};
  int         expect   = 2;
  int         actual   = solution->numComponents(head, nums);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: head = [0,1,2,3,4], nums = [0,3,1,4]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(817, LinkedListComponents, example_2) {
  auto        solution = MakeSolution();
  ListNode   *head   = ListNode::FromVector({0, 1, 2, 3, 4} /*, looped_index*/);
  vector<int> nums   = {0, 3, 1, 4};
  int         expect = 2;
  int         actual = solution->numComponents(head, nums);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}
