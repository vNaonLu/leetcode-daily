// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Trees With Factors
//
// https://leetcode.com/problems/binary-trees-with-factors/
//
// Question ID: 823
// Difficult  : Medium
// Solve Date : 2022/08/09 18:19

#include <algorithm>
#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |823. Binary Trees With Factors|:
//
// Given an array of unique integers, |arr|, where each integer |arr[i]| is
// strictly greater than |1|. We make a binary tree using these integers, and
// each number may be used for any number of times. Each non-leaf node's value
// should be equal to the product of the values of its children. Return the
// number of binary trees we can make. The answer may be too large so return the
// answer modulo |10⁹ + 7|.
//

LEETCODE_BEGIN_RESOLVING(823, BinaryTreesWithFactors, Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;

public:
  int numFactoredBinaryTrees(vector<int> &arr) {
    sort(arr.begin(), arr.end());
    auto res   = int64_t(0);
    auto dp    = vector<int64_t>(arr.size(), 1);
    auto index = unordered_map<int, int>();

    for (int i = 0; i < dp.size(); ++i) {
      index[arr[i]] = i;
      for (int j = 0; j < i; ++j) {
        if (arr[i] % arr[j] == 0) {
          int r = arr[i] / arr[j];
          if (index.count(r)) {
            dp[i] = (dp[i] + dp[j] * dp[index[r]]) % kMod;
          }
        }
      }
    }

    for (auto &x : dp) {
      res += x;
      res %= kMod;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 1000|
// * |2 <= arr[i] <= 10⁹|
// * All the values of |arr| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [2,4]
// Output: 3
//
// We can make these trees: |[2], [4], [4, 2, 2]|

LEETCODE_SOLUTION_UNITTEST(823, BinaryTreesWithFactors, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 4};
  int         expect   = 3;
  int         actual   = solution->numFactoredBinaryTrees(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [2,4,5,10]
// Output: 7
//
// We can make these trees: |[2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5,
// 2]|.

LEETCODE_SOLUTION_UNITTEST(823, BinaryTreesWithFactors, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 4, 5, 10};
  int         expect   = 7;
  int         actual   = solution->numFactoredBinaryTrees(arr);
  LCD_EXPECT_EQ(expect, actual);
}
