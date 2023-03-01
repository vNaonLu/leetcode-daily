// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Convert Binary Number in a Linked List to Integer
//
// https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/
//
// Question ID: 1290
// Difficult  : Easy
// Solve Date : 2021/12/07 18:28

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1290. Convert Binary Number in a Linked List to Integer|:
//
// Given |head| which is a reference node to a singly-linked list. The value of
// each node in the linked list is either |0| or |1|. The linked list holds the
// binary representation of a number. Return the decimal value of the number in
// the linked list. The most significant bit is at the head of the linked list.
//  
//

LEETCODE_BEGIN_RESOLVING(1290, ConvertBinaryNumberInALinkedListToInteger,
                         Solution);

class Solution {
public:
  int getDecimalValue(ListNode *head) {
    int res = 0;
    while (nullptr != head) {
      res <<= 1;
      if (head->val == 1)
        res |= 1;
      head = head->next;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The Linked List is not empty.
// * Number of nodes will not exceed |30|.
// * Each node's value is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,0,1]
// Output: 5
//
// (101) in base 2 = (5) in base 10

LEETCODE_SOLUTION_UNITTEST(1290, ConvertBinaryNumberInALinkedListToInteger,
                           example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 0, 1} /*, looped_index*/);
  int       expect   = 5;
  int       actual   = solution->getDecimalValue(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: head = [0]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1290, ConvertBinaryNumberInALinkedListToInteger,
                           example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({0} /*, looped_index*/);
  int       expect   = 0;
  int       actual   = solution->getDecimalValue(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}
