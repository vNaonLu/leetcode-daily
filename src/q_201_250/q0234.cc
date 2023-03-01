// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Palindrome Linked List
//
// https://leetcode.com/problems/palindrome-linked-list/
//
// Question ID: 234
// Difficult  : Easy
// Solve Date : 2022/08/23 18:07

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |234. Palindrome Linked List|:
//
// Given the |head| of a singly linked list, return |true| if it is a palindrome
// or |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(234, PalindromeLinkedList, Solution);

class Solution {
public:
  bool isPalindrome(ListNode *head) {
    auto v = vector<decltype(ListNode::val)>();
    while (nullptr != head) {
      v.emplace_back(head->val);
      head = head->next;
    }

    int lo = 0;
    int hi = v.size() - 1;

    while (lo < hi) {
      if (v[lo++] != v[hi--]) {
        return false;
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[1, 10⁵]|.
// * |0 <= Node.val <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,2,1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(234, PalindromeLinkedList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 2, 1} /*, looped_index*/);
  bool      expect   = true;
  bool      actual   = solution->isPalindrome(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: head = [1,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(234, PalindromeLinkedList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2} /*, looped_index*/);
  bool      expect   = false;
  bool      actual   = solution->isPalindrome(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}
