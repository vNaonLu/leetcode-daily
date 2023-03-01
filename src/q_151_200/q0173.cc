// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Search Tree Iterator
//
// https://leetcode.com/problems/binary-search-tree-iterator/
//
// Question ID: 173
// Difficult  : Medium
// Solve Date : 2021/10/05 12:37

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |173. Binary Search Tree Iterator|:
//
// Implement the |BSTIterator| class that represents an iterator over the
// [in-order traversal] of a binary search tree (BST):
//
//  • |BSTIterator(TreeNode root)| Initializes an object of the |BSTIterator|
//  class. The |root| of the BST is given as part of the constructor. The
//  pointer should be initialized to a non-existent number smaller than any
//  element in the BST.
//
//  • |boolean hasNext()| Returns |true| if there exists a number in the
//  traversal to the right of the pointer, otherwise returns |false|.
//
//  • |int next()| Moves the pointer to the right, then returns the number at
//  the pointer.
// Notice that by initializing the pointer to a non-existent smallest number,
// the first call to |next()| will return the smallest element in the BST. You
// may assume that |next()| calls will always be valid. That is, there will be
// at least a next number in the in-order traversal when |next()| is called.  
//

LEETCODE_BEGIN_RESOLVING(173, BinarySearchTreeIterator, BSTIterator);

class BSTIterator {
private:
  int         index;
  vector<int> traverse;
  void        traverseHelper(TreeNode *p) {
    if (p == nullptr)
      return;
    traverseHelper(p->left);
    traverse.push_back(p->val);
    traverseHelper(p->right);
  }

public:
  BSTIterator(TreeNode *root) {
    index = -1;
    traverse.clear();
    traverseHelper(root);
  }
  int  next() { return traverse[++index]; }
  bool hasNext() { return index < (int)traverse.size() - 1; }
};

LEETCODE_END_RESOLVING(BSTIterator);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁵]|.
// * |0 <= Node.val <= 10⁶|
// * At most |10⁵| calls will be made to |hasNext|, and |next|.
// * Could you implement |next()| and |hasNext()| to run in average |O(1)| time
// and use  |O(h)| memory, where |h| is the height of the tree?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next",
//  "hasNext", "next", "hasNext"]
// [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
// Output: [null, 3, 7, true, 9, true, 15, true, 20, false]
//
// BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
// bSTIterator.next(); // return 3
// bSTIterator.next(); // return 7
// bSTIterator.hasNext(); // return True
// bSTIterator.next(); // return 9
// bSTIterator.hasNext(); // return True
// bSTIterator.next(); // return 15
// bSTIterator.hasNext(); // return True
// bSTIterator.next(); // return 20
// bSTIterator.hasNext(); // return False

LEETCODE_SOLUTION_UNITTEST(173, BinarySearchTreeIterator, example_1) {
  TreeNode *s0_root      = TreeNode::FromVector({7, 3, 15, null, null, 9, 20});
  auto      bst_iterator = MakeBSTIterator(s0_root);
  int       s1_expect    = 3;
  int       s1_actual    = bst_iterator->next();
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_expect = 7;
  int s2_actual = bst_iterator->next();
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  bool s3_expect = true;
  bool s3_actual = bst_iterator->hasNext();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_expect = 9;
  int s4_actual = bst_iterator->next();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  bool s5_expect = true;
  bool s5_actual = bst_iterator->hasNext();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  int s6_expect = 15;
  int s6_actual = bst_iterator->next();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
  bool s7_expect = true;
  bool s7_actual = bst_iterator->hasNext();
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  int s8_expect = 20;
  int s8_actual = bst_iterator->next();
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  bool s9_expect = false;
  bool s9_actual = bst_iterator->hasNext();
  LCD_EXPECT_EQ(s9_expect, s9_actual);
  TreeNode::Release(s0_root);
}
