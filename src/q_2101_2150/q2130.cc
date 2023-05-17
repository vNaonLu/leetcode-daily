// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Twin Sum of a Linked List
//
// https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/
//
// Question ID: 2130
// Difficult  : Medium
// Solve Date : 2023/05/17 18:53

#include "leetcode/list_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2130. Maximum Twin Sum of a Linked List|:
//
// In a linked list of size |n|, where |n| is even, the |iᵗʰ| node (0-indexed)
// of the linked list is known as the twin of the |(n-1-i)ᵗʰ| node, if |0 <= i
// <= (n / 2) - 1|.
//
//  • For example, if |n = 4|, then node |0| is the twin of node |3|, and node
//  |1| is the twin of node |2|. These are the only nodes with twins for |n =
//  4|.
// The twin sum is defined as the sum of a node and its twin.
// Given the |head| of a linked list with even length, return the maximum twin
// sum of the linked list.
//
//

LEETCODE_BEGIN_RESOLVING(2130, MaximumTwinSumOfALinkedList, Solution);

class Solution {
public:
  int pairSum(ListNode *head) {
    vector<int> vals;
    while (head) {
      vals.emplace_back(head->val);
      head = head->next;
    }
    auto res = 0;
    auto b   = vals.begin();
    auto r   = vals.rbegin();
    while (b != vals.end()) {
      res = max(res, *b++ + *r++);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is an even integer in the range |[2, 10⁵]|.
// * |1 <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [5,4,2,1]
// Output: 6
//
// Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum
// = 6. There are no other nodes with twins in the linked list. Thus, the
// maximum twin sum of the linked list is 6.

LEETCODE_SOLUTION_UNITTEST(2130, MaximumTwinSumOfALinkedList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({5, 4, 2, 1} /*, looped_index*/);
  int       expect   = 6;
  int       actual   = solution->pairSum(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: head = [4,2,2,3]
// Output: 7
//
// The nodes with twins present in this linked list are:
// - Node 0 is the twin of node 3 having a twin sum of 4 + 3 = 7.
// - Node 1 is the twin of node 2 having a twin sum of 2 + 2 = 4.
// Thus, the maximum twin sum of the linked list is max(7, 4) = 7.

LEETCODE_SOLUTION_UNITTEST(2130, MaximumTwinSumOfALinkedList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({4, 2, 2, 3} /*, looped_index*/);
  int       expect   = 7;
  int       actual   = solution->pairSum(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #3]
//  Input: head = [1,100000]
// Output: 100001
//
// There is only one node with a twin in the linked list having twin sum of 1 +
// 100000 = 100001.

LEETCODE_SOLUTION_UNITTEST(2130, MaximumTwinSumOfALinkedList, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 100000} /*, looped_index*/);
  int       expect   = 100001;
  int       actual   = solution->pairSum(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}
