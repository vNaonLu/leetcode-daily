// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find X-Sum of All K-Long Subarrays II
//
// https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/
//
// Question ID: 3321
// Difficult  : Hard
// Solve Date : 2025/11/05 20:30

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3321. Find X-Sum of All K-Long Subarrays II|:
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

LEETCODE_BEGIN_RESOLVING(3321, FindXSumOfAllKLongSubarraysII, Solution);

class Solution {
  using pii = pair<long long, int>;

public:
  vector<long long> findXSum(vector<int> &nums, int k, int x) {
    vector<long long> result;

    unordered_map<int, int> numCount;
    set<pii, greater<pii>>  top, bottom;

    long long running_sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      long long count = numCount[nums[i]];
      if (count > 0) {
        if (top.count({count, nums[i]}) > 0) {
          top.erase({count, nums[i]});
          running_sum -= count * nums[i];
        } else {
          bottom.erase({count, nums[i]});
        }
      }

      count += 1;
      numCount[nums[i]] = count;
      top.insert({count, nums[i]});
      running_sum += (count)*nums[i];

      if (top.size() > x) {
        auto it_smallest = prev(end(top));
        running_sum -= it_smallest->first * it_smallest->second;
        bottom.insert({it_smallest->first, it_smallest->second});
        top.erase(it_smallest);
      }

      if (i >= k) {
        long long count = numCount[nums[i - k]];
        if (top.count({count, nums[i - k]})) {
          running_sum -= count * nums[i - k];
          top.erase({count, nums[i - k]});
        } else {
          bottom.erase({count, nums[i - k]});
        }

        count -= 1;
        numCount[nums[i - k]] = count;
        if (count > 0) {
          bottom.insert({count, nums[i - k]});
        }

        if (top.size() < x) {
          auto it = begin(bottom);
          if (it != end(bottom)) {
            running_sum += it->first * it->second;
            top.insert({it->first, it->second});
            bottom.erase(it);
          }
        }
      }

      if (i + 1 >= k) {
        result.push_back(running_sum);
      }
    }
    return result;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |nums.length == n|
// * |1 <= n <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= x <= k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
// Output: [6,10,12]
//

LEETCODE_SOLUTION_UNITTEST(3321, FindXSumOfAllKLongSubarraysII, example_1) {
  auto              solution = MakeSolution();
  vector<int>       nums     = {1, 1, 2, 2, 3, 4, 2, 3};
  int               k        = 6;
  int               x        = 2;
  vector<long long> expect   = {6, 10, 12};
  vector<long long> actual   = solution->findXSum(nums, k, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,8,7,8,7,5], k = 2, x = 2
// Output: [11,15,15,15,12]
//

LEETCODE_SOLUTION_UNITTEST(3321, FindXSumOfAllKLongSubarraysII, example_2) {
  auto              solution = MakeSolution();
  vector<int>       nums     = {3, 8, 7, 8, 7, 5};
  int               k        = 2;
  int               x        = 2;
  vector<long long> expect   = {11, 15, 15, 15, 12};
  vector<long long> actual   = solution->findXSum(nums, k, x);
  LCD_EXPECT_EQ(expect, actual);
}
