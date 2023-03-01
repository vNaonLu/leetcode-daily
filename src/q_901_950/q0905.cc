// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort Array By Parity
//
// https://leetcode.com/problems/sort-array-by-parity/
//
// Question ID: 905
// Difficult  : Easy
// Solve Date : 2022/05/02 13:17

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |905. Sort Array By Parity|:
//
// Given an integer array |nums|, move all the even integers at the beginning of
// the array followed by all the odd integers. Return any array that satisfies
// this condition.  
//

LEETCODE_BEGIN_RESOLVING(905, SortArrayByParity, Solution);

class Solution {
public:
  vector<int> sortArrayByParity(vector<int> &nums) {
    int i = nums.size() - 1, j = 0;

    while (i > j) {
      if ((nums[i] & 1) == 0) {
        if (nums[j] & 1) {
          swap(nums[j++], nums[i--]);
        } else {
          ++j;
        }
      } else {
        --i;
      }
    }

    return nums;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5000|
// * |0 <= nums[i] <= 5000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,1,2,4]
// Output: [2,4,3,1]
//
// The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.

LEETCODE_SOLUTION_UNITTEST(905, SortArrayByParity, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 2, 4};
  vector<int> expect   = {2, 4, 3, 1};
  vector<int> actual   = solution->sortArrayByParity(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(905, SortArrayByParity, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0};
  vector<int> expect   = {0};
  vector<int> actual   = solution->sortArrayByParity(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}
