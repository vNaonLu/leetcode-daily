// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Divide an Array Into Subarrays With Minimum Cost II
//
// https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-ii/
//
// Question ID: 3013
// Difficult  : Hard
// Solve Date : 2026/02/02 18:51

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3013. Divide an Array Into Subarrays With Minimum Cost II|:
//
// You are given a 0-indexed array of integers |nums| of length |n|, and two
// positive integers |k| and |dist|. The cost of an array is the value of its
// first element. For example, the cost of |[1,2,3]| is |1| while the cost of
// |[3,4,1]| is |3|. You need to divide |nums| into |k| disjoint contiguous
// subarrays, such that the difference between the starting index of the second
// subarray and the starting index of the |kth| subarray should be less than or
// equal to |dist|. In other words, if you divide |nums| into the subarrays
// |nums[0..(i₁ - 1)], nums[i₁..(i₂ - 1)], ..., nums[iₖ₋₁..(n - 1)]|, then |iₖ₋₁
// - i₁ <= dist|. Return the minimum possible sum of the cost of these
// subarrays.
//
//

LEETCODE_BEGIN_RESOLVING(3013, DivideAnArrayIntoSubarraysWithMinimumCostII,
                         Solution);

class Solution {
public:
  struct SmartWindow {
    int           K;
    multiset<int> low, high;
    long long     sumLow = 0;

    SmartWindow(int k) : K(k) {}

    int  windowSize() const { return (int)low.size() + (int)high.size(); }
    void rebalance() {
      int need = min(K, windowSize());

      while ((int)low.size() > need) {
        auto it = prev(low.end());
        int  x  = *it;
        low.erase(it);
        sumLow -= x;
        high.insert(x);
      }
      while ((int)low.size() < need && !high.empty()) {
        auto it = high.begin();
        int  x  = *it;
        high.erase(it);
        low.insert(x);
        sumLow += x;
      }
    }
    void add(int x) {
      if (low.empty() || x <= *prev(low.end())) {
        low.insert(x);
        sumLow += x;
      } else {
        high.insert(x);
      }
      rebalance();
    }
    void remove(int x) {
      auto itLow = low.find(x);
      if (itLow != low.end()) {
        low.erase(itLow);
        sumLow -= x;
      } else {
        auto itHigh = high.find(x);
        if (itHigh != high.end()) {
          high.erase(itHigh);
        }
      }
      rebalance();
    }
    long long query() const { return sumLow; }
  };
  long long minimumCost(vector<int> &nums, int k, int dist) {
    int n = (int)nums.size();
    k -= 1;
    SmartWindow window(k);
    for (int i = 1; i <= 1 + dist; i++) {
      window.add(nums[i]);
    }
    long long ans = window.query();
    for (int i = 2; i + dist < n; i++) {
      window.remove(nums[i - 1]);
      window.add(nums[i + dist]);
      ans = min(ans, window.query());
    }
    return ans + nums[0];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= n <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |3 <= k <= n|
// * |k - 2 <= dist <= n - 2|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3013, DivideAnArrayIntoSubarraysWithMinimumCostII,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 2, 6, 4, 2};
  int         k        = 3;
  int         dist     = 3;
  long long   expect   = 5;
  long long   actual   = solution->minimumCost(nums, k, dist);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [10,1,2,2,2,1], k = 4, dist = 3
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(3013, DivideAnArrayIntoSubarraysWithMinimumCostII,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 1, 2, 2, 2, 1};
  int         k        = 4;
  int         dist     = 3;
  long long   expect   = 15;
  long long   actual   = solution->minimumCost(nums, k, dist);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [10,8,18,9], k = 3, dist = 1
// Output: 36
//

LEETCODE_SOLUTION_UNITTEST(3013, DivideAnArrayIntoSubarraysWithMinimumCostII,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 8, 18, 9};
  int         k        = 3;
  int         dist     = 1;
  long long   expect   = 36;
  long long   actual   = solution->minimumCost(nums, k, dist);
  LCD_EXPECT_EQ(expect, actual);
}
