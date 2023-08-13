// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if There is a Valid Partition For The Array
//
// https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/
//
// Question ID: 2369
// Difficult  : Medium
// Solve Date : 2023/08/13 16:26

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2369. Check if There is a Valid Partition For The Array|:
//
// You are given a 0-indexed integer array |nums|. You have to partition the
// array into one or more contiguous subarrays. We call a partition of the array
// valid if each of the obtained subarrays satisfies one of the following
// conditions:
//
//  1. The subarray consists of exactly |2| equal elements. For example, the
//  subarray |[2,2]| is good.
//
//  2. The subarray consists of exactly |3| equal elements. For example, the
//  subarray |[4,4,4]| is good.
//
//  3. The subarray consists of exactly |3| consecutive increasing elements,
//  that is, the difference between adjacent elements is |1|. For example, the
//  subarray |[3,4,5]| is good, but the subarray |[1,3,5]| is not.
// Return |true| if the array has at least one valid partition. Otherwise,
// return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(2369, CheckIfThereIsAValidPartitionForTheArray,
                         Solution);

class Solution {
public:
  bool validPartition(vector<int> &nums) {
    vector<int> dp(nums.size() + 1, -1);
    return helper(nums, &dp, 0);
  }

private:
  bool helper(const vector<int> &v, vector<int> *dp, int i) {
    int n = v.size();
    if (n == i) {
      return true;
    }

    if ((*dp)[i] != -1) {
      return (*dp)[i];
    }

    if (i + 1 < n && v[i] == v[i + 1]) {
      if (helper(v, dp, i + 2)) {
        return (*dp)[i] = true;
      }
    }

    if (i + 2 < n && v[i] == v[i + 2] && v[i] == v[i + 1]) {
      if (helper(v, dp, i + 3)) {
        return (*dp)[i] = true;
      }
    }

    if (i + 2 < n && v[i] + 1 == v[i + 1] && v[i] + 2 == v[i + 2]) {
      if (helper(v, dp, i + 3)) {
        return (*dp)[i] = true;
      }
    }
    return (*dp)[i] = false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,4,4,5,6]
// Output: true
//
// The array can be partitioned into the subarrays [4,4] and [4,5,6].
// This partition is valid, so we return true.

LEETCODE_SOLUTION_UNITTEST(2369, CheckIfThereIsAValidPartitionForTheArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 4, 4, 5, 6};
  bool        expect   = true;
  bool        actual   = solution->validPartition(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1,2]
// Output: false
//
// There is no valid partition for this array.

LEETCODE_SOLUTION_UNITTEST(2369, CheckIfThereIsAValidPartitionForTheArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 2};
  bool        expect   = false;
  bool        actual   = solution->validPartition(nums);
  LCD_EXPECT_EQ(expect, actual);
}
