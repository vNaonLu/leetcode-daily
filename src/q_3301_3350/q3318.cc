// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find X-Sum of All K-Long Subarrays I
//
// https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/
//
// Question ID: 3318
// Difficult  : Easy
// Solve Date : 2024/10/19 13:42

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3318. Find X-Sum of All K-Long Subarrays I|:
//
// You are given an array |nums| of |n| integers and two integers |k| and |x|.
// The x-sum of an array is calculated by the following procedure:
//
//  • Count the occurrences of all elements in the array.
//
//  • Keep only the occurrences of the top |x| most frequent elements. If two
//  elements have the same number of occurrences, the element with the bigger
//  value is considered more frequent.
//
//  • Calculate the sum of the resulting array.
// Note that if an array has less than |x| distinct elements, its x-sum is the
// sum of the array. Return an integer array |answer| of length |n - k + 1|
// where |answer[i]| is the x-sum of the subarray |nums[i..i + k - 1]|.
//
//

LEETCODE_BEGIN_RESOLVING(3318, FindXSumOfAllKLongSubarraysI, Solution);

class Solution {
public:
  vector<int> findXSum(vector<int> &nums, int k, int x) {
    vector<pair<int, int>> freq(51);
    vector<int>            res;
    int                    lo = 0;
    int                    hi = 0;
    while (hi < k) {
      ++freq[nums[hi]].first;
      freq[nums[hi]].second = nums[hi];
      ++hi;
    }
    for (hi = k, lo = 1, res.emplace_back(calc(freq, x)); hi < nums.size();
         ++hi, ++lo, res.emplace_back(calc(freq, x))) {
      int l_num = nums[lo - 1];
      int r_num = nums[hi];
      --freq[l_num].first;
      ++freq[r_num].first;
      freq[r_num].second = r_num;
    }
    return res;
  }

private:
  int calc(auto v, int x) {
    sort(v.begin(), v.end(), greater<pair<int, int>>{});
    int res = 0;
    for (int i = 0; i < x; ++i) {
      auto [f, num] = v[i];
      if (f == 0) {
        break;
      }

      res += num * f;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == nums.length <= 50|
// * |1 <= nums[i] <= 50|
// * |1 <= x <= k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
// Output: [6,10,12]
//

LEETCODE_SOLUTION_UNITTEST(3318, FindXSumOfAllKLongSubarraysI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 2, 3, 4, 2, 3};
  int         k        = 6;
  int         x        = 2;
  vector<int> expect   = {6, 10, 12};
  vector<int> actual   = solution->findXSum(nums, k, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,8,7,8,7,5], k = 2, x = 2
// Output: [11,15,15,15,12]
//

LEETCODE_SOLUTION_UNITTEST(3318, FindXSumOfAllKLongSubarraysI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 8, 7, 8, 7, 5};
  int         k        = 2;
  int         x        = 2;
  vector<int> expect   = {11, 15, 15, 15, 12};
  vector<int> actual   = solution->findXSum(nums, k, x);
  LCD_EXPECT_EQ(expect, actual);
}
