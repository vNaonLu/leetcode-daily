// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Depth of N-ary Tree
//
// https://leetcode.com/problems/maximum-depth-of-n-ary-tree/
//
// Question ID: 559
// Difficult  : Easy
// Solve Date : 2022/10/11 13:28

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |559. Maximum Depth of N-ary Tree|:
//
// Given a n-ary tree, find its maximum depth.
// The maximum depth is the number of nodes along the longest path from the root
// node down to the farthest leaf node. Nary-Tree input serialization is
// represented in their level order traversal, each group of children is
// separated by the null value (See examples).
//

LEETCODE_BEGIN_RESOLVING(559, MaximumDepthOfNAryTree, Solution);

class Node {
public:
  int            val;
  vector<Node *> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, vector<Node *> _children) {
    val      = _val;
    children = _children;
  }
};

class Solution {
public:
  int maxDepth(Node *root) {
    if (nullptr == root) {
      return 0;
    }
    auto depth = (int)0;
    for (auto p : root->children) {
      depth = max(depth, maxDepth(p));
    }
    return 1 + depth;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The total number of nodes is in the range |[0, 10⁴]|.
// * The depth of the n-ary tree is less than or equal to |1000|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,null,3,2,4,null,5,6]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(559, MaximumDepthOfNAryTree, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: root =
//  [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(559, MaximumDepthOfNAryTree, example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}
