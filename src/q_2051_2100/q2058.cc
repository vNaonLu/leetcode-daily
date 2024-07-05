// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Minimum and Maximum Number of Nodes Between Critical Points
//
// https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/
//
// Question ID: 2058
// Difficult  : Medium
// Solve Date : 2024/07/05 19:59

#include "leetcode/list_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2058. Find the Minimum and Maximum Number of Nodes Between
// Critical Points|:
//
// A critical point in a linked list is defined as either a local maxima or a
// local minima. A node is a local maxima if the current node has a value
// strictly greater than the previous node and the next node. A node is a local
// minima if the current node has a value strictly smaller than the previous
// node and the next node. Note that a node can only be a local maxima/minima if
// there exists both a previous node and a next node. Given a linked list
// |head|, return an array of length 2 containing |[minDistance, maxDistance]|
// where |minDistance| is the minimum distance between any two distinct critical
// points and |maxDistance| is the maximum distance between any two distinct
// critical points. If there are fewer than two critical points, return |[-1,
// -1]|.
//
//

LEETCODE_BEGIN_RESOLVING(
    2058, FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPoints, Solution);

class Solution {
public:
  vector<int> nodesBetweenCriticalPoints(ListNode *head) {
    vector<int> res       = {-1, -1};
    auto       *prev      = head;
    auto       *p         = prev ? prev->next : nullptr;
    int         prev_peak = -1;
    int         idx       = 1;
    while (p && p->next) {
      if ((p->val > prev->val && p->val > p->next->val) ||
          (p->val < prev->val && p->val < p->next->val)) {
        if (prev_peak > 0) {
          res[0] =
              res[0] == -1 ? (idx - prev_peak) : min(res[0], idx - prev_peak);
          res[1] =
              res[1] == -1 ? (idx - prev_peak) : (res[1] + idx - prev_peak);
        }
        prev_peak = idx;
      }

      prev = p;
      p    = p->next;
      ++idx;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[2, 10⁵]|.
// * |1 <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [3,1]
// Output: [-1,-1]
//

LEETCODE_SOLUTION_UNITTEST(
    2058, FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPoints,
    example_1) {
  auto        solution = MakeSolution();
  ListNode   *head     = ListNode::FromVector({3, 1} /*, looped_index*/);
  vector<int> expect   = {-1, -1};
  vector<int> actual   = solution->nodesBetweenCriticalPoints(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: head = [5,3,1,2,5,1,2]
// Output: [1,3]
//

LEETCODE_SOLUTION_UNITTEST(
    2058, FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPoints,
    example_2) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({5, 3, 1, 2, 5, 1, 2} /*, looped_index*/);
  vector<int> expect = {1, 3};
  vector<int> actual = solution->nodesBetweenCriticalPoints(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #3]
//  Input: head = [1,3,2,2,3,2,2,2,7]
// Output: [3,3]
//

LEETCODE_SOLUTION_UNITTEST(
    2058, FindTheMinimumAndMaximumNumberOfNodesBetweenCriticalPoints,
    example_3) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({1, 3, 2, 2, 3, 2, 2, 2, 7} /*, looped_index*/);
  vector<int> expect = {3, 3};
  vector<int> actual = solution->nodesBetweenCriticalPoints(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}
