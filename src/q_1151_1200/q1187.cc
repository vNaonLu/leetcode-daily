// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Make Array Strictly Increasing
//
// https://leetcode.com/problems/make-array-strictly-increasing/
//
// Question ID: 1187
// Difficult  : Hard
// Solve Date : 2023/06/17 11:12

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1187. Make Array Strictly Increasing|:
//
// Given two integer arrays |arr1| and |arr2|, return the minimum number of
// operations (possibly zero) needed to make |arr1| strictly increasing.
//
// In one operation, you can choose two indices |0 <= i < arr1.length| and |0 <=
// j < arr2.length| and do the assignment |arr1[i] = arr2[j]|.
//
// If there is no way to make |arr1| strictly increasing, return |-1|.
//
//
//

LEETCODE_BEGIN_RESOLVING(1187, MakeArrayStrictlyIncreasing, Solution);

class Solution {
public:
  int makeArrayIncreasing(vector<int> &arr1, vector<int> &arr2) {
    int                 n   = arr1.size();
    int                 m   = arr2.size();
    int                 res = 1e9;
    vector<vector<int>> f(n, vector<int>(m + 10, res));
    f[0][m] = 0;
    for (int i = 0; i < m; ++i) {
      f[0][i] = i + 1;
    }
    sort(arr2.begin(), arr2.end());
    m = distance(arr2.begin(), unique(arr2.begin(), arr2.end()));
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (j != 0) {
          f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
        }
        if (arr1[i - 1] < arr2[j]) {
          f[i][j] = min(f[i][j], f[i - 1][m] + 1);
        }
      }
      for (int j = 0; j < m; ++j) {
        if (arr1[i] > arr2[j]) {
          f[i][m] = min(f[i][m], f[i - 1][j]);
        }
      }
      if (arr1[i] > arr1[i - 1]) {
        f[i][m] = min(f[i][m], f[i - 1][m]);
      }
    }
    for (int i = 0; i <= m; ++i) {
      res = min(res, f[n - 1][i]);
    }
    return res == 1e9 ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= arr1.length, arr2.length <= 2000|
// * |0 <= arr1[i], arr2[i] <= 10^9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
// Output: 1
//
// Replace |5| with |2|, then |arr1 = [1, 2, 3, 6, 7]|.

LEETCODE_SOLUTION_UNITTEST(1187, MakeArrayStrictlyIncreasing, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {1, 5, 3, 6, 7};
  vector<int> arr2     = {1, 3, 2, 4};
  int         expect   = 1;
  int         actual   = solution->makeArrayIncreasing(arr1, arr2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
// Output: 2
//
// Replace |5| with |3| and then replace |3| with |4|. |arr1 = [1, 3, 4, 6, 7]|.

LEETCODE_SOLUTION_UNITTEST(1187, MakeArrayStrictlyIncreasing, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {1, 5, 3, 6, 7};
  vector<int> arr2     = {4, 3, 1};
  int         expect   = 2;
  int         actual   = solution->makeArrayIncreasing(arr1, arr2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
// Output: -1
//
// You can't make |arr1| strictly increasing.

LEETCODE_SOLUTION_UNITTEST(1187, MakeArrayStrictlyIncreasing, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr1     = {1, 5, 3, 6, 7};
  vector<int> arr2     = {1, 6, 3, 3};
  int         expect   = -1;
  int         actual   = solution->makeArrayIncreasing(arr1, arr2);
  LCD_EXPECT_EQ(expect, actual);
}
