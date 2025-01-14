// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Prefix Common Array of Two Arrays
//
// https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/
//
// Question ID: 2657
// Difficult  : Medium
// Solve Date : 2025/01/14 21:48

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2657. Find the Prefix Common Array of Two Arrays|:
//
// You are given two 0-indexed integer permutations |A| and |B| of length |n|.
// A prefix common array of |A| and |B| is an array |C| such that |C[i]| is
// equal to the count of numbers that are present at or before the index |i| in
// both |A| and |B|. Return the prefix common array of |A| and |B|. A sequence
// of |n| integers is called a permutation if it contains all integers from |1|
// to |n| exactly once.
//
//

LEETCODE_BEGIN_RESOLVING(2657, FindThePrefixCommonArrayOfTwoArrays, Solution);

class Solution {
public:
  vector<int> findThePrefixCommonArray(vector<int> &A, vector<int> &B) {
    vector<int> cnt(A.size(), 0);
    vector<int> res(A.size(), 0);

    for (int i = 0; i < A.size(); ++i) {
      if (++cnt[A[i] - 1] == 2) {
        ++res[i];
      }
      if (++cnt[B[i] - 1] == 2) {
        ++res[i];
      }
    }

    for (int i = 1; i < res.size(); ++i) {
      res[i] += res[i - 1];
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= A.length == B.length == n <= 50|
// * |1 <= A[i], B[i] <= n|
// * |It is guaranteed that A and B are both a permutation of n integers.|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: A = [1,3,2,4], B = [3,1,2,4]
// Output: [0,2,3,4]
//

LEETCODE_SOLUTION_UNITTEST(2657, FindThePrefixCommonArrayOfTwoArrays,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> A        = {1, 3, 2, 4};
  vector<int> B        = {3, 1, 2, 4};
  vector<int> expect   = {0, 2, 3, 4};
  vector<int> actual   = solution->findThePrefixCommonArray(A, B);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: A = [2,3,1], B = [3,1,2]
// Output: [0,1,3]
//

LEETCODE_SOLUTION_UNITTEST(2657, FindThePrefixCommonArrayOfTwoArrays,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> A        = {2, 3, 1};
  vector<int> B        = {3, 1, 2};
  vector<int> expect   = {0, 1, 3};
  vector<int> actual   = solution->findThePrefixCommonArray(A, B);
  LCD_EXPECT_EQ(expect, actual);
}
