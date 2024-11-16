// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Power of K-Size Subarrays I
//
// https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/
//
// Question ID: 3254
// Difficult  : Medium
// Solve Date : 2024/11/16 12:32

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3254. Find the Power of K-Size Subarrays I|:
//
//

LEETCODE_BEGIN_RESOLVING(3254, FindThePowerOfKSizeSubarraysI, Solution);

class Solution {
public:
  vector<int> resultsArray(vector<int> &nums, int k) {
    int n = nums.size();
    if (n == 1) {
      return nums;
    }
    vector<int> res(n - k + 1, -1);
    int         len = 1;
    for (int r = 1; r < k; ++r) {
      if (nums[r] == nums[r - 1] + 1) {
        ++len;
      } else {
        len = 1;
      }
    }

    if (len == k) {
      res[0] = nums[k - 1];
    }
    for (int l = 1, r = k; r < n; ++l, ++r) {
      if (nums[r] == nums[r - 1] + 1) {
        ++len;
      } else {
        len = 1;
      }

      if (len >= k) {
        res[l] = nums[r];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == nums.length <= 500|
// * |1 <= nums[i] <= 10⁵|
// * |1 <= k <= n|
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3254, FindThePowerOfKSizeSubarraysI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 3, 2, 5};
  int         k        = 3;
  vector<int> expect   = {3, 4, -1, -1, -1};
  vector<int> actual   = solution->resultsArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3254, FindThePowerOfKSizeSubarraysI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 2, 2, 2};
  int         k        = 4;
  vector<int> expect   = {-1, -1};
  vector<int> actual   = solution->resultsArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3254, FindThePowerOfKSizeSubarraysI, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 3, 2, 3, 2};
  int         k        = 2;
  vector<int> expect   = {-1, 3, -1, 3, -1};
  vector<int> actual   = solution->resultsArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
