// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Difference in Sums After Removal of Elements
//
// https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/
//
// Question ID: 2163
// Difficult  : Hard
// Solve Date : 2025/07/18 19:38

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2163. Minimum Difference in Sums After Removal of Elements|:
//
// You are given a 0-indexed integer array |nums| consisting of |3 * n|
// elements. You are allowed to remove any subsequence of elements of size
// exactly |n| from |nums|. The remaining |2 * n| elements will be divided into
// two equal parts:
//
//  • The first |n| elements belonging to the first part and their sum is
//  |sumᶠᵢᵣₛₜ|.
//
//  • The next |n| elements belonging to the second part and their sum is
//  |sum_{second}|.
// The difference in sums of the two parts is denoted as |sumᶠᵢᵣₛₜ -
// sum_{second}|.
//
//  • For example, if |sumᶠᵢᵣₛₜ = 3| and |sum_{second} = 2|, their difference is
//  |1|.
//
//  • Similarly, if |sumᶠᵢᵣₛₜ = 2| and |sum_{second} = 3|, their difference is
//  |-1|.
// Return the minimum difference possible between the sums of the two parts
// after the removal of |n| elements.
//
//

LEETCODE_BEGIN_RESOLVING(2163, MinimumDifferenceInSumsAfterRemovalOfElements,
                         Solution);

class Solution {
public:
  long long minimumDifference(vector<int> &nums) {
    int n = nums.size();
    int k = n / 3;

    vector<long long>                              leftMins(n), rightMaxs(n);
    priority_queue<int>                            maxLeftHeap;
    priority_queue<int, vector<int>, greater<int>> minRightHeap;
    long long                                      leftSum = 0, rightSum = 0,
              minDiff = numeric_limits<int64_t>::max();

    for (int i = 0; i < k; ++i) {
      maxLeftHeap.push(nums[i]);
      leftSum += nums[i];
    }
    leftMins[k - 1] = leftSum;

    for (int i = k; i < n - k; ++i) {
      if (!maxLeftHeap.empty() && nums[i] < maxLeftHeap.top()) {
        leftSum += nums[i] - maxLeftHeap.top();
        maxLeftHeap.pop();
        maxLeftHeap.push(nums[i]);
      }
      leftMins[i] = leftSum;
    }

    for (int i = n - 1; i >= n - k; --i) {
      minRightHeap.push(nums[i]);
      rightSum += nums[i];
    }
    rightMaxs[n - k] = rightSum;

    for (int i = n - k - 1; i >= k - 1; --i) {
      if (!minRightHeap.empty() && nums[i] > minRightHeap.top()) {
        rightSum += nums[i] - minRightHeap.top();
        minRightHeap.pop();
        minRightHeap.push(nums[i]);
      }
      rightMaxs[i] = rightSum;
    }

    // Compute min difference
    for (int i = k - 1; i < n - k; ++i) {
      minDiff = min(minDiff, leftMins[i] - rightMaxs[i + 1]);
    }

    return minDiff;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |nums.length == 3 * n|
// * |1 <= n <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,1,2]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2163, MinimumDifferenceInSumsAfterRemovalOfElements,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 2};
  long long   expect   = -1;
  long long   actual   = solution->minimumDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [7,9,5,8,1,3]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2163, MinimumDifferenceInSumsAfterRemovalOfElements,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 9, 5, 8, 1, 3};
  long long   expect   = 1;
  long long   actual   = solution->minimumDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}
