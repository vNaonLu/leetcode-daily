// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Merge Nodes in Between Zeros
//
// https://leetcode.com/problems/merge-nodes-in-between-zeros/
//
// Question ID: 2181
// Difficult  : Medium
// Solve Date : 2023/03/11 01:36

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2181. Merge Nodes in Between Zeros|:
//
// You are given the |head| of a linked list, which contains a series of
// integers separated by |0|'s. The beginning and end of the linked list will
// have |Node.val == 0|. For every two consecutive |0|'s, merge all the nodes
// lying in between them into a single node whose value is the sum of all the
// merged nodes. The modified list should not contain any |0|'s. Return the
// |head| of the modified linked list.
//

LEETCODE_BEGIN_RESOLVING(2181, MergeNodesInBetweenZeros, Solution);

class Solution {
public:
  ListNode *mergeNodes(ListNode *head) {
    ListNode dummy;
    auto     ptr  = head->next;
    auto     iter = &dummy;
    int      sum  = 0;
    while (ptr) {
      sum += ptr->val;
      if (ptr->val == 0) {
        iter->next = new ListNode(sum);
        iter       = iter->next;
        sum        = 0;
      }
      ptr = ptr->next;
    }
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[3, 2 * 10⁵]|.
// * |0 <= Node.val <= 1000|
// * There are no two consecutive nodes with |Node.val == 0|.
// * The beginning and end of the linked list have |Node.val == 0|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [0,3,1,0,4,5,2,0]
// Output: [4,11]
//
// The above figure represents the given linked list. The modified list contains
// - The sum of the nodes marked in green: 3 + 1 = 4.
// - The sum of the nodes marked in red: 4 + 5 + 2 = 11.

LEETCODE_SOLUTION_UNITTEST(2181, MergeNodesInBetweenZeros, example_1) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({0, 3, 1, 0, 4, 5, 2, 0} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({4, 11} /*, looped_index*/);
  ListNode *actual = solution->mergeNodes(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [0,1,0,3,0,2,2,0]
// Output: [1,3,4]
//
// The above figure represents the given linked list. The modified list contains
// - The sum of the nodes marked in green: 1 = 1.
// - The sum of the nodes marked in red: 3 = 3.
// - The sum of the nodes marked in yellow: 2 + 2 = 4.

LEETCODE_SOLUTION_UNITTEST(2181, MergeNodesInBetweenZeros, example_2) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({0, 1, 0, 3, 0, 2, 2, 0} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({1, 3, 4} /*, looped_index*/);
  ListNode *actual = solution->mergeNodes(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}
