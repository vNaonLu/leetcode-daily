// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Convert Sorted List to Binary Search Tree
//
// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
//
// Question ID: 109
// Difficult  : Medium
// Solve Date : 2022/03/01 14:29

#include "leetcode/list_node.h"
#include "leetcode/tree_node.h"
#include <algorithm>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |109. Convert Sorted List to Binary Search Tree|:
//
// Given the |head| of a singly linked list where elements are sorted in
// ascending order, convert it to a height-balanced binary search tree.  
//

LEETCODE_BEGIN_RESOLVING(109, ConvertSortedListToBinarySearchTree, Solution);

class Solution {
private:
  TreeNode *buildTree(ListNode *beg, ListNode *end = nullptr) {
    if (beg == end)
      return nullptr;
    ListNode *mid = beg, *fast = beg;
    while (fast != end && fast->next != end) {
      fast = fast->next->next;
      mid  = mid->next;
    }
    return new TreeNode(mid->val, buildTree(beg, mid),
                        buildTree(mid->next, end));
  }

public:
  TreeNode *sortedListToBST(ListNode *head) { return buildTree(head); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in |head| is in the range |[0, 2 * 10⁴]|.
// * |-10⁵ <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [-10,-3,0,5,9]
// Output: [0,-3,9,-10,null,5]
//
// One possible answer is [0,-3,9,-10,null,5], which represents the shown height
// balanced BST.

LEETCODE_SOLUTION_UNITTEST(109, ConvertSortedListToBinarySearchTree,
                           example_1) {
  auto      solution = MakeSolution();
  ListNode *head = ListNode::FromVector({-10, -3, 0, 5, 9} /*, looped_index*/);
  TreeNode *expect = TreeNode::FromVector({0, -3, 9, -10, null, 5});
  TreeNode *actual = solution->sortedListToBST(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
  TreeNode::Release(expect, actual);
}

// [Example #2]
//  Input: head = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(109, ConvertSortedListToBinarySearchTree,
                           example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({} /*, looped_index*/);
  TreeNode *expect   = TreeNode::FromVector({});
  TreeNode *actual   = solution->sortedListToBST(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
  TreeNode::Release(expect, actual);
}
