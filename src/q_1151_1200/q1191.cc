// Copyright 2023 Naon Lu
//
// This file describes the solution of
// K-Concatenation Maximum Sum
//
// https://leetcode.com/problems/k-concatenation-maximum-sum/
//
// Question ID: 1191
// Difficult  : Medium
// Solve Date : 2022/02/17 18:49

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1191. K-Concatenation Maximum Sum|:
//
// Given an integer array |arr| and an integer |k|, modify the array by
// repeating it |k| times. For example, if |arr = [1, 2]| and |k = 3 |then the
// modified array will be |[1, 2, 1, 2, 1, 2]|. Return the maximum sub-array sum
// in the modified array. Note that the length of the sub-array can be |0| and
// its sum in that case is |0|. As the answer can be very large, return the
// answer modulo |10⁹ + 7|.  
//

LEETCODE_BEGIN_RESOLVING(1191, KConcatenationMaximumSum, Solution);

class Solution {
private:
  constexpr static inline int kMod = 1e9 + 7;
  int                         kadane(vector<int> &arr) {
    int sum = 0, res = 0;
    for (const auto &x : arr) {
      sum = max(sum, 0) + x;
      res = max(res, sum);
    }
    return res;
  }

public:
  int kConcatenationMaxSum(vector<int> &arr, int k) {
    if (k == 1)
      return kadane(arr) % kMod;
    int sum = 0, n = arr.size();
    for (const auto &x : arr)
      sum = (sum + x) % kMod;

    arr.reserve(2 * arr.size());
    for (int i = 0; i < n; ++i) {
      arr.push_back(arr[i]);
    }

    int res = kadane(arr);
    if (sum <= 0)
      return res;
    else
      return (res + long(k - 2) * sum) % kMod;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁵|
// * |1 <= k <= 10⁵|
// * |-10⁴ <= arr[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2], k = 3
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(1191, KConcatenationMaximumSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2};
  int         k        = 3;
  int         expect   = 9;
  int         actual   = solution->kConcatenationMaxSum(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,-2,1], k = 5
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1191, KConcatenationMaximumSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, -2, 1};
  int         k        = 5;
  int         expect   = 2;
  int         actual   = solution->kConcatenationMaxSum(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [-1,-2], k = 7
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1191, KConcatenationMaximumSum, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {-1, -2};
  int         k        = 7;
  int         expect   = 0;
  int         actual   = solution->kConcatenationMaxSum(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}
