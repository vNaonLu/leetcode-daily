// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Add Two Numbers II
//
// https://leetcode.com/problems/add-two-numbers-ii/
//
// Question ID: 445
// Difficult  : Medium
// Solve Date : 2022/05/10 19:27

#include "leetcode/list_node.h"
#include <iosfwd>
#include <stack>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |445. Add Two Numbers II|:
//
// You are given two non-empty linked lists representing two non-negative
// integers. The most significant digit comes first and each of their nodes
// contains a single digit. Add the two numbers and return the sum as a linked
// list. You may assume the two numbers do not contain any leading zero, except
// the number 0 itself.  
//

LEETCODE_BEGIN_RESOLVING(445, AddTwoNumbersII, Solution);

class Solution {
private:
  stack<int> link(stack<int> &x, stack<int> &y) {
    stack<int> res;
    int        carry = 0;
    while (!x.empty() && !y.empty()) {
      int sum = x.top() + y.top() + carry;
      x.pop();
      y.pop();

      res.emplace(sum % 10);
      carry = sum / 10;
    }

    while (!x.empty()) {
      int sum = x.top() + carry;
      x.pop();

      res.emplace(sum % 10);
      carry = sum / 10;
    }

    while (!y.empty()) {
      int sum = y.top() + carry;
      y.pop();

      res.emplace(sum % 10);
      carry = sum / 10;
    }

    if (carry != 0) {
      res.emplace(carry);
    }

    return res;
  }

public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    stack<int> stk1, stk2;
    while (nullptr != l1) {
      stk1.emplace(l1->val);
      l1 = l1->next;
    }
    while (nullptr != l2) {
      stk2.emplace(l2->val);
      l2 = l2->next;
    }

    auto     combine = link(stk1, stk2);
    ListNode dummy, *p = &dummy;
    while (!combine.empty()) {
      p->next = new ListNode(combine.top());
      combine.pop();
      p = p->next;
    }

    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in each linked list is in the range |[1, 100]|.
// * |0 <= Node.val <= 9|
// * It is guaranteed that the list represents a number that does not have
// leading zeros.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: l1 = [7,2,4,3], l2 = [5,6,4]
// Output: [7,8,0,7]
//

LEETCODE_SOLUTION_UNITTEST(445, AddTwoNumbersII, example_1) {
  auto      solution = MakeSolution();
  ListNode *l1       = ListNode::FromVector({7, 2, 4, 3} /*, looped_index*/);
  ListNode *l2       = ListNode::FromVector({5, 6, 4} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({7, 8, 0, 7} /*, looped_index*/);
  ListNode *actual   = solution->addTwoNumbers(l1, l2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(l1, l2, expect, actual);
}

// [Example #2]
//  Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [8,0,7]
//

LEETCODE_SOLUTION_UNITTEST(445, AddTwoNumbersII, example_2) {
  auto      solution = MakeSolution();
  ListNode *l1       = ListNode::FromVector({2, 4, 3} /*, looped_index*/);
  ListNode *l2       = ListNode::FromVector({5, 6, 4} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({8, 0, 7} /*, looped_index*/);
  ListNode *actual   = solution->addTwoNumbers(l1, l2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(l1, l2, expect, actual);
}

// [Example #3]
//  Input: l1 = [0], l2 = [0]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(445, AddTwoNumbersII, example_3) {
  auto      solution = MakeSolution();
  ListNode *l1       = ListNode::FromVector({0} /*, looped_index*/);
  ListNode *l2       = ListNode::FromVector({0} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({0} /*, looped_index*/);
  ListNode *actual   = solution->addTwoNumbers(l1, l2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(l1, l2, expect, actual);
}
