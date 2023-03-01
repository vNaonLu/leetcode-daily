// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Arithmetic Subarrays
//
// https://leetcode.com/problems/arithmetic-subarrays/
//
// Question ID: 1630
// Difficult  : Medium
// Solve Date : 2022/05/04 18:04

#include <array>
#include <iosfwd>
#include <limits>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1630. Arithmetic Subarrays|:
//
// A sequence of numbers is called arithmetic if it consists of at least two
// elements, and the difference between every two consecutive elements is the
// same. More formally, a sequence |s| is arithmetic if and only if |s[i+1] -
// s[i] == s[1] - s[0] |for all valid |i|. For example, these are arithmetic
// sequences: 1, 3, 5, 7, 9 7, 7, 7, 7 3, -1, -5, -9 The following sequence is
// not arithmetic: 1, 1, 2, 5, 7 You are given an array of |n| integers, |nums|,
// and two arrays of |m| integers each, |l| and |r|, representing the |m| range
// queries, where the |iᵗʰ| query is the range |[l[i], r[i]]|. All the arrays
// are 0-indexed. Return a list of |boolean| elements |answer|, where
// |answer[i]| is |true| if the subarray |nums[l[i]], nums[l[i]+1], ... ,
// nums[r[i]]| can be rearranged to form an arithmetic sequence, and |false|
// otherwise.  
//

LEETCODE_BEGIN_RESOLVING(1630, ArithmeticSubarrays, Solution);

class Solution {
private:
  bool helper(vector<int> &nums, int l, int r) {
    unordered_map<int, int> m;
    int min_n = numeric_limits<int>::max(), max_n = numeric_limits<int>::min();
    for (int i = l; i <= r; ++i) {
      auto &x = nums[i];
      ++m[x];
      min_n = min(min_n, x);
      max_n = max(max_n, x);
    }
    if (min_n != max_n) {
      int stride = (max_n - min_n) / (r - l);
      for (int i = min_n; i <= max_n; i += stride) {
        if (m[i] != 1) {
          return false;
        }
      }
    }
    return true;
  }

public:
  vector<bool> checkArithmeticSubarrays(vector<int> &nums, vector<int> &l,
                                        vector<int> &r) {
    vector<bool> res(l.size(), false);
    for (int i = 0; i < res.size(); ++i) {
      res[i] = helper(nums, l[i], r[i]);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |m == l.length|
// * |m == r.length|
// * |2 <= n <= 500|
// * |1 <= m <= 500|
// * |0 <= l[i] < r[i] < n|
// * |-10⁵ <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = |[4,6,5,9,3,7]|, l = |[0,0,2]|, r = |[2,3,5]|
// Output: |[true,false,true]|
//
// In the 0ᵗʰ query, the subarray is [4,6,5]. This can be rearranged as [6,5,4],
// which is an arithmetic sequence. In the 1ˢᵗ query, the subarray is [4,6,5,9].
// This cannot be rearranged as an arithmetic sequence. In the 2ⁿᵈ query, the
// subarray is |[5,9,3,7]. This| can be rearranged as |[3,5,7,9]|, which is an
// arithmetic sequence.

LEETCODE_SOLUTION_UNITTEST(1630, ArithmeticSubarrays, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: nums = [-12,-9,-3,-12,-6,15,20,-25,-20,-15,-10], l = [0,1,6,4,8,7], r
//  = [4,4,9,7,9,10]
// Output: [false,true,false,false,true,true]
//

LEETCODE_SOLUTION_UNITTEST(1630, ArithmeticSubarrays, example_2) {
  auto         solution = MakeSolution();
  vector<int>  nums     = {-12, -9, -3, -12, -6, 15, 20, -25, -20, -15, -10};
  vector<int>  l        = {0, 1, 6, 4, 8, 7};
  vector<int>  r        = {4, 4, 9, 7, 9, 10};
  vector<bool> expect   = {false, true, false, false, true, true};
  vector<bool> actual   = solution->checkArithmeticSubarrays(nums, l, r);
  LCD_EXPECT_EQ(expect, actual);
}
