// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Length of Longest Fibonacci Subsequence
//
// https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/
//
// Question ID: 873
// Difficult  : Medium
// Solve Date : 2024/09/03 22:36

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |873. Length of Longest Fibonacci Subsequence|:
//
// A sequence |x₁, x₂, ..., xₙ| is Fibonacci-like if:
//
//  • |n >= 3|
//
//  • |xᵢ + xᵢ₊₁ == xᵢ₊₂| for all |i + 2 <= n|
// Given a strictly increasing array |arr| of positive integers forming a
// sequence, return the length of the longest Fibonacci-like subsequence of
// |arr|. If one does not exist, return |0|. A subsequence is derived from
// another sequence |arr| by deleting any number of elements (including none)
// from |arr|, without changing the order of the remaining elements. For
// example, |[3, 5, 8]| is a subsequence of |[3, 4, 5, 6, 7, 8]|.
//
//

LEETCODE_BEGIN_RESOLVING(873, LengthOfLongestFibonacciSubsequence, Solution);

class Solution {
public:
  int lenLongestFibSubseq(vector<int> &arr) {
    int                     n = arr.size();
    vector<vector<int>>     dp(n, vector<int>(n, -1));
    int                     res = 0;
    unordered_map<int, int> mp;
    for (int i = 0; i < arr.size(); ++i) {
      mp[arr[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (mp.find(arr[i] + arr[j]) != mp.end()) {
          res = max(res, 2 + solve(i, j, arr, &dp));
        }
      }
    }
    return res >= 3 ? res : 0;
  }

private:
  int solve(int i, int j, vector<int> const &arr, vector<vector<int>> *dp) {
    if (j >= arr.size() || i > j) {
      return 0;
    }
    if ((*dp)[i][j] != -1) {
      return (*dp)[i][j];
    }
    int x = 0;
    int l = j + 1;
    int r = arr.size() - 1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (arr[mid] == arr[j] + arr[i]) {
        x = 1 + solve(j, mid, arr, dp);
        break;
      } else if (arr[mid] > arr[j] + arr[i]) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    return (*dp)[i][j] = x;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= arr.length <= 1000|
// * |1 <= arr[i] < arr[i + 1] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,3,4,5,6,7,8]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(873, LengthOfLongestFibonacciSubsequence,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 4, 5, 6, 7, 8};
  int         expect   = 5;
  int         actual   = solution->lenLongestFibSubseq(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,3,7,11,12,14,18]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(873, LengthOfLongestFibonacciSubsequence,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 3, 7, 11, 12, 14, 18};
  int         expect   = 3;
  int         actual   = solution->lenLongestFibSubseq(arr);
  LCD_EXPECT_EQ(expect, actual);
}
