// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Subarray Minimums
//
// https://leetcode.com/problems/sum-of-subarray-minimums/
//
// Question ID: 907
// Difficult  : Medium
// Solve Date : 2022/02/21 22:50

#include <array>
#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |907. Sum of Subarray Minimums|:
//
// Given an array of integers arr, find the sum of |min(b)|, where |b| ranges
// over every (contiguous) subarray of |arr|. Since the answer may be large,
// return the answer modulo |10⁹ + 7|.  
//

LEETCODE_BEGIN_RESOLVING(907, SumOfSubarrayMinimums, Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;

public:
  int sumSubarrayMins(vector<int> &arr) {
    long long             res = 0;
    stack<pair<int, int>> stk;
    vector<long long>     dp(arr.size() + 2, 0);
    for (int i = arr.size() - 1; i >= 0; --i) {
      int right;
      while (stk.empty() == false && stk.top().first > arr[i]) {
        stk.pop();
      }

      if (stk.empty() == true) {
        right = arr.size();
      } else {
        right = stk.top().second;
      }

      dp[i] = ((arr[i] % kMod * (right - i) % kMod) % kMod + dp[right] % kMod) %
              kMod;
      res = (res % kMod + dp[i] % kMod) % kMod;
      stk.emplace(arr[i], i);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 3 * 10⁴|
// * |1 <= arr[i] <= 3 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [3,1,2,4]
// Output: 17
//
// Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4],
// [3,1,2,4]. Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1. Sum is 17.

LEETCODE_SOLUTION_UNITTEST(907, SumOfSubarrayMinimums, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 1, 2, 4};
  int         expect   = 17;
  int         actual   = solution->sumSubarrayMins(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [11,81,94,43,3]
// Output: 444
//

LEETCODE_SOLUTION_UNITTEST(907, SumOfSubarrayMinimums, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {11, 81, 94, 43, 3};
  int         expect   = 444;
  int         actual   = solution->sumSubarrayMins(arr);
  LCD_EXPECT_EQ(expect, actual);
}
