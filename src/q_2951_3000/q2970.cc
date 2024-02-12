// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count the Number of Incremovable Subarrays I
//
// https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-i/
//
// Question ID: 2970
// Difficult  : Easy
// Solve Date : 2024/02/12 12:19

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2970. Count the Number of Incremovable Subarrays I|:
//
// You are given a 0-indexed array of positive integers |nums|.
// A subarray of |nums| is called incremovable if |nums| becomes strictly
// increasing on removing the subarray. For example, the subarray |[3, 4]| is an
// incremovable subarray of |[5, 3, 4, 6, 7]| because removing this subarray
// changes the array |[5, 3, 4, 6, 7]| to |[5, 6, 7]| which is strictly
// increasing. Return the total number of incremovable subarrays of |nums|. Note
// that an empty array is considered strictly increasing. A subarray is a
// contiguous non-empty sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2970, CountTheNumberOfIncremovableSubarraysI,
                         Solution);

class Solution {
public:
  int incremovableSubarrayCount(vector<int> &nums) {
    int n   = nums.size();
    int res = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        vector<int> tmp;
        for (int k = 0; k < i; ++k) {
          tmp.emplace_back(nums[k]);
        }
        for (int k = j + 1; k < n; ++k) {
          tmp.emplace_back(nums[k]);
        }
        if (isRemovable(tmp)) {
          ++res;
        }
      }
    }

    return res;
  }

private:
  bool isRemovable(vector<int> const &v) {
    for (int i = 1; i < v.size(); ++i) {
      if (v[i] <= v[i - 1]) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |1 <= nums[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: 10
//
// The 10 incremovable subarrays are: [1], [2], [3], [4], [1,2], [2,3], [3,4],
// [1,2,3], [2,3,4], and [1,2,3,4], because on removing any one of these
// subarrays nums becomes strictly increasing. Note that you cannot select an
// empty subarray.

LEETCODE_SOLUTION_UNITTEST(2970, CountTheNumberOfIncremovableSubarraysI,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 10;
  int         actual   = solution->incremovableSubarrayCount(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [6,5,7,8]
// Output: 7
//
// The 7 incremovable subarrays are: [5], [6], [5,7], [6,5], [5,7,8], [6,5,7]
// and [6,5,7,8]. It can be shown that there are only 7 incremovable subarrays
// in nums.

LEETCODE_SOLUTION_UNITTEST(2970, CountTheNumberOfIncremovableSubarraysI,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 5, 7, 8};
  int         expect   = 7;
  int         actual   = solution->incremovableSubarrayCount(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [8,7,6,6]
// Output: 3
//
// The 3 incremovable subarrays are: [8,7,6], [7,6,6], and [8,7,6,6]. Note that
// [8,7] is not an incremovable subarray because after removing [8,7] nums
// becomes [6,6], which is sorted in ascending order but not strictly
// increasing.

LEETCODE_SOLUTION_UNITTEST(2970, CountTheNumberOfIncremovableSubarraysI,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {8, 7, 6, 6};
  int         expect   = 3;
  int         actual   = solution->incremovableSubarrayCount(nums);
  LCD_EXPECT_EQ(expect, actual);
}
