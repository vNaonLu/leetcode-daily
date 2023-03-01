// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Construct Quad Tree
//
// https://leetcode.com/problems/construct-quad-tree/
//
// Question ID: 427
// Difficult  : Medium
// Solve Date : 2023/02/27 15:12

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |427. Construct Quad Tree|:
//
// Given a |n * n| matrix |grid| of |0's| and |1's| only. We want to represent
// the |grid| with a Quad-Tree. Return the root of the Quad-Tree representing
// the |grid|. Notice that you can assign the value of a node to True or False
// when |isLeaf| is False, and both are accepted in the answer. A Quad-Tree is a
// tree data structure in which each internal node has exactly four children.
// Besides, each node has two attributes:
//
//  • |val|: True if the node represents a grid of 1's or False if the node
//  represents a grid of 0's.
//
//  • |isLeaf|: True if the node is leaf node on the tree or False if the node
//  has the four children.
// class Node {
//     public boolean val;
//     public boolean isLeaf;
//     public Node topLeft;
//     public Node topRight;
//     public Node bottomLeft;
//     public Node bottomRight;
// }
// We can construct a Quad-Tree from a two-dimensional area using the following
// steps:
//
//  1. If the current grid has the same value (i.e all |1's| or all |0's|) set
//  |isLeaf| True and set |val| to the value of the grid and set the four
//  children to Null and stop.
//
//  2. If the current grid has different values, set |isLeaf| to False and set
//  |val| to any value and divide the current grid into four sub-grids as shown
//  in the photo.
//
//  3. Recurse for each of the children with the proper sub-grid.
// ![img](https://assets.leetcode.com/uploads/2020/02/11/new_top.png)
// If you want to know more about the Quad-Tree, you can refer to the [wiki].
// Quad-Tree format:
// The output represents the serialized format of a Quad-Tree using level order
// traversal, where |null| signifies a path terminator where no node exists
// below. It is very similar to the serialization of the binary tree. The only
// difference is that the node is represented as a list |[isLeaf, val]|. If the
// value of |isLeaf| or |val| is True we represent it as 1 in the list |[isLeaf,
// val]| and if the value of |isLeaf| or |val| is False we represent it as 0.
//

LEETCODE_BEGIN_RESOLVING(427, ConstructQuadTree, Solution);

class Node {
public:
  bool  val;
  bool  isLeaf;
  Node *topLeft;
  Node *topRight;
  Node *bottomLeft;
  Node *bottomRight;

  Node() {
    val         = false;
    isLeaf      = false;
    topLeft     = NULL;
    topRight    = NULL;
    bottomLeft  = NULL;
    bottomRight = NULL;
  }

  Node(bool _val, bool _isLeaf) {
    val         = _val;
    isLeaf      = _isLeaf;
    topLeft     = NULL;
    topRight    = NULL;
    bottomLeft  = NULL;
    bottomRight = NULL;
  }

  Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight,
       Node *_bottomLeft, Node *_bottomRight) {
    val         = _val;
    isLeaf      = _isLeaf;
    topLeft     = _topLeft;
    topRight    = _topRight;
    bottomLeft  = _bottomLeft;
    bottomRight = _bottomRight;
  }
};

class Solution {
private:
  Node *construct(vector<vector<int>> &grid, pair<int, int> row,
                  pair<int, int> col) {
    Node *res               = new Node();
    auto [row_beg, row_end] = row;
    auto [col_beg, col_end] = col;
    auto val                = grid[row_beg][col_beg];
    bool value_not_unique   = false;
    for (int i = row_beg; i < row_end && !value_not_unique; ++i) {
      for (int j = col_beg; j < col_end; ++j) {
        if (val != grid[i][j]) {
          value_not_unique = true;
          break;
        }
      }
    }
    if (value_not_unique) {
      auto  row_mid      = row_beg + (row_end - row_beg) / 2;
      auto  col_mid      = col_beg + (col_end - col_beg) / 2;
      auto *top_left     = construct(grid, make_pair(row_beg, row_mid),
                                     make_pair(col_beg, col_mid));
      auto *top_right    = construct(grid, make_pair(row_beg, row_mid),
                                     make_pair(col_mid, col_end));
      auto *bottom_left  = construct(grid, make_pair(row_mid, row_end),
                                     make_pair(col_beg, col_mid));
      auto *bottom_right = construct(grid, make_pair(row_mid, row_end),
                                     make_pair(col_mid, col_end));
      res->topLeft       = top_left;
      res->topRight      = top_right;
      res->bottomLeft    = bottom_left;
      res->bottomRight   = bottom_right;
      res->isLeaf        = false;
      res->val =
          top_left->val | top_right->val | bottom_left->val | bottom_right->val;
    } else {
      res->val    = val;
      res->isLeaf = true;
    }
    return res;
  }

public:
  Node *construct(vector<vector<int>> &grid) {
    return construct(grid, make_pair(0, grid.size()),
                     make_pair(0, grid.size()));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == grid.length == grid[i].length|
// * |n == 2ˣ| where |0 <= x <= 6|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[0,1],[1,0]]
// Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
//
// The explanation of this example is shown below:
// Notice that 0 represnts False and 1 represents True in the photo representing
// the Quad-Tree.
// ![img](https://assets.leetcode.com/uploads/2020/02/12/e1tree.png)

LEETCODE_SOLUTION_UNITTEST(427, ConstructQuadTree, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: grid =
//  [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
// Output:
// [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
//
// All values in the grid are not the same. We divide the grid into four
// sub-grids. The topLeft, bottomLeft and bottomRight each has the same value.
// The topRight have different values so we divide it into 4 sub-grids where
// each has the same value. Explanation is shown in the photo below:
// ![img](https://assets.leetcode.com/uploads/2020/02/12/e2tree.png)

LEETCODE_SOLUTION_UNITTEST(427, ConstructQuadTree, example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}
