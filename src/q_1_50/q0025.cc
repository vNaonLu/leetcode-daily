// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Nodes in k-Group
//
// https://leetcode.com/problems/reverse-nodes-in-k-group/
//
// Question ID: 25
// Difficult  : Hard
// Solve Date : 2021/10/01 12:27

#include "leetcode/list_node.h"
#include <iosfwd>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |25. Reverse Nodes in k-Group|:
//
// Given the |head| of a linked list, reverse the nodes of the list |k| at a
// time, and return the modified list. |k| is a positive integer and is less
// than or equal to the length of the linked list. If the number of nodes is not
// a multiple of |k| then left-out nodes, in the end, should remain as it is.
// You may not alter the values in the list's nodes, only nodes themselves may
// be changed.  
//

LEETCODE_BEGIN_RESOLVING(25, ReverseNodesInKGroup, Solution);

class Solution {
public:
  ListNode *getNode(ListNode *p, int offset) {
    ListNode *res = p;
    for (int i = 0; i < offset && res != nullptr; i++) {
      res = res->next;
    }
    return res;
  }
  ListNode *reverseNode(ListNode *p, int k) {
    vector<ListNode *> group;
    ListNode          *after_group = p;
    for (int i = 0; i < k; i++) {
      if (after_group == nullptr) {
        break;
      } else {
        group.push_back(after_group);
        after_group = after_group->next;
      }
    }
    if (group.size() == k) {
      for (int i = k - 1; i > 0; i--) {
        group[i]->next = group[i - 1];
      }
      group[0]->next = after_group;
      return group[k - 1];
    } else {
      return p;
    }
  }
  ListNode *reverseKGroup(ListNode *head, int k) {
    if (k == 1)
      return head;
    head        = reverseNode(head, k);
    ListNode *p = getNode(head, k - 1);
    while (p != nullptr && p->next != nullptr) {
      p->next = reverseNode(p->next, k);
      p       = getNode(p, k);
    }
    return head;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is |n|.
// * |1 <= k <= n <= 5000|
// * |0 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4,5], k = 2
// Output: [2,1,4,3,5]
//

LEETCODE_SOLUTION_UNITTEST(25, ReverseNodesInKGroup, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  int       k        = 2;
  ListNode *expect   = ListNode::FromVector({2, 1, 4, 3, 5} /*, looped_index*/);
  ListNode *actual   = solution->reverseKGroup(head, k);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect);
}

// [Example #2]
//  Input: head = [1,2,3,4,5], k = 3
// Output: [3,2,1,4,5]
//

LEETCODE_SOLUTION_UNITTEST(25, ReverseNodesInKGroup, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  int       k        = 3;
  ListNode *expect   = ListNode::FromVector({3, 2, 1, 4, 5} /*, looped_index*/);
  ListNode *actual   = solution->reverseKGroup(head, k);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect);
}
