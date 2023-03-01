// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Next Greater Node In Linked List
//
// https://leetcode.com/problems/next-greater-node-in-linked-list/
//
// Question ID: 1019
// Difficult  : Medium
// Solve Date : 2022/03/08 12:36

#include "leetcode/list_node.h"
#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1019. Next Greater Node In Linked List|:
//
// You are given the |head| of a linked list with |n| nodes.
// For each node in the list, find the value of the next greater node. That is,
// for each node, find the value of the first node that is next to it and has a
// strictly larger value than it. Return an integer array |answer| where
// |answer[i]| is the value of the next greater node of the |iᵗʰ| node
// (1-indexed). If the |iᵗʰ| node does not have a next greater node, set
// |answer[i] = 0|.  
//

LEETCODE_BEGIN_RESOLVING(1019, NextGreaterNodeInLinkedList, Solution);

class Solution {
private:
  vector<int> res;
  stack<int>  stk;
  void        helper(ListNode *p) {
    if (nullptr == p)
      return;

    helper(p->next);
    if (nullptr != p->next) {
      stk.push(p->next->val);
    }

    while (!stk.empty() && stk.top() <= p->val) {
      stk.pop();
    }

    if (stk.empty()) {
      res.push_back(0);
    } else {
      res.push_back(stk.top());
    }
  }

public:
  vector<int> nextLargerNodes(ListNode *head) {
    helper(head);
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is |n|.
// * |1 <= n <= 10⁴|
// * |1 <= Node.val <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [2,1,5]
// Output: [5,5,0]
//

LEETCODE_SOLUTION_UNITTEST(1019, NextGreaterNodeInLinkedList, example_1) {
  auto        solution = MakeSolution();
  ListNode   *head     = ListNode::FromVector({2, 1, 5} /*, looped_index*/);
  vector<int> expect   = {5, 5, 0};
  vector<int> actual   = solution->nextLargerNodes(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: head = [2,7,4,3,5]
// Output: [7,0,5,5,0]
//

LEETCODE_SOLUTION_UNITTEST(1019, NextGreaterNodeInLinkedList, example_2) {
  auto        solution = MakeSolution();
  ListNode   *head   = ListNode::FromVector({2, 7, 4, 3, 5} /*, looped_index*/);
  vector<int> expect = {7, 0, 5, 5, 0};
  vector<int> actual = solution->nextLargerNodes(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}
