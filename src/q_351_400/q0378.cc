// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Kth Smallest Element in a Sorted Matrix
//
// https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
//
// Question ID: 378
// Difficult  : Medium
// Solve Date : 2022/08/02 18:55

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |378. Kth Smallest Element in a Sorted Matrix|:
//
// Given an |n x n| |matrix| where each of the rows and columns is sorted in
// ascending order, return the |kᵗʰ| smallest element in the matrix. Note that
// it is the |kᵗʰ| smallest element in the sorted order, not the |kᵗʰ| distinct
// element. You must find a solution with a memory complexity better than
// |O(n²)|.
//

LEETCODE_BEGIN_RESOLVING(378, KthSmallestElementInASortedMatrix, Solution);

class Solution {
public:
  int kthSmallest(vector<vector<int>> &matrix, int k) {
    priority_queue<int> pq;
    for (auto &v : matrix) {
      for (auto &x : v) {
        pq.emplace(x);
        if (pq.size() > k) {
          pq.pop();
        }
      }
    }

    return pq.top();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == matrix.length == matrix[i].length|
// * |1 <= n <= 300|
// * |-10⁹ <= matrix[i][j] <= 10⁹|
// * All the rows and columns of |matrix| are guaranteed to be sorted in
// non-decreasing order.
// * |1 <= k <= n²|
// * Could you solve the problem with a constant memory (i.e., |O(1)| memory
// complexity)?
// * Could you solve the problem in |O(n)| time complexity? The solution may be
// too advanced for an interview but you may find reading [this paper] fun.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
// Output: 13
//
// The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8ᵗʰ
// smallest number is 13

LEETCODE_SOLUTION_UNITTEST(378, KthSmallestElementInASortedMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 1,  5,  9},
      {10, 11, 13},
      {12, 13, 15}
  };
  int k      = 8;
  int expect = 13;
  int actual = solution->kthSmallest(matrix, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[-5]], k = 1
// Output: -5
//

LEETCODE_SOLUTION_UNITTEST(378, KthSmallestElementInASortedMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {{-5}};
  int                 k        = 1;
  int                 expect   = -5;
  int                 actual   = solution->kthSmallest(matrix, k);
  LCD_EXPECT_EQ(expect, actual);
}
