// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Partition List
//
// https://leetcode.com/problems/partition-list/
//
// Question ID: 86
// Difficult  : Medium
// Solve Date : 2022/02/27 00:41

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |86. Partition List|:
//
// Given the |head| of a linked list and a value |x|, partition it such that all
// nodes less than |x| come before nodes greater than or equal to |x|. You
// should preserve the original relative order of the nodes in each of the two
// partitions.  
//

LEETCODE_BEGIN_RESOLVING(86, PartitionList, Solution);

class Solution {
public:
  ListNode *partition(ListNode *head, int x) {
    ListNode less(0, nullptr), greater(0, nullptr), *lp = &less, *gp = &greater;
    while (nullptr != head) {
      if (head->val >= x) {
        gp->next = new ListNode(head->val);
        gp       = gp->next;
      } else {
        lp->next = new ListNode(head->val);
        lp       = lp->next;
      }
      head = head->next;
    }
    lp->next = greater.next;
    return less.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[0, 200]|.
// * |-100 <= Node.val <= 100|
// * |-200 <= x <= 200|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,4,3,2,5,2], x = 3
// Output: [1,2,2,4,3,5]
//

LEETCODE_SOLUTION_UNITTEST(86, PartitionList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head = ListNode::FromVector({1, 4, 3, 2, 5, 2} /*, looped_index*/);
  int       x    = 3;
  ListNode *expect =
      ListNode::FromVector({1, 2, 2, 4, 3, 5} /*, looped_index*/);
  ListNode *actual = solution->partition(head, x);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [2,1], x = 2
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(86, PartitionList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({2, 1} /*, looped_index*/);
  int       x        = 2;
  ListNode *expect   = ListNode::FromVector({1, 2} /*, looped_index*/);
  ListNode *actual   = solution->partition(head, x);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}
