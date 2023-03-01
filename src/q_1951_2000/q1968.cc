// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Array With Elements Not Equal to Average of Neighbors
//
// https://leetcode.com/problems/array-with-elements-not-equal-to-average-of-neighbors/
//
// Question ID: 1968
// Difficult  : Medium
// Solve Date : 2022/03/07 19:08

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1968. Array With Elements Not Equal to Average of Neighbors|:
//
// You are given a 0-indexed array |nums| of distinct integers. You want to
// rearrange the elements in the array such that every element in the rearranged
// array is not equal to the average of its neighbors. More formally, the
// rearranged array should have the property such that for every |i| in the
// range |1 <= i < nums.length - 1|, |(nums[i-1] + nums[i+1]) / 2| is not equal
// to |nums[i]|. Return any rearrangement of |nums| that meets the requirements.
//  
//

LEETCODE_BEGIN_RESOLVING(1968, ArrayWithElementsNotEqualToAverageOfNeighbors,
                         Solution);

class Solution {
public:
  vector<int> rearrangeArray(vector<int> &nums) {
    vector<int> res = nums;
    for (int i = 1; i < res.size() - 1; ++i) {
      int x = res[i - 1], y = res[i], z = res[i + 1];
      if (x < y && y < z || x > y && y > z) {
        swap(res[i], res[i + 1]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,5]
// Output: [1,2,4,5,3]
//
// When i=1, nums[i] = 2, and the average of its neighbors is (1+4) / 2 = 2.5.
// When i=2, nums[i] = 4, and the average of its neighbors is (2+5) / 2 = 3.5.
// When i=3, nums[i] = 5, and the average of its neighbors is (4+3) / 2 = 3.5.

LEETCODE_SOLUTION_UNITTEST(1968, ArrayWithElementsNotEqualToAverageOfNeighbors,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  vector<int> expect   = {1, 3, 2, 5, 4};
  vector<int> actual   = solution->rearrangeArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [6,2,0,9,7]
// Output: [9,7,6,2,0]
//
// When i=1, nums[i] = 7, and the average of its neighbors is (9+6) / 2 = 7.5.
// When i=2, nums[i] = 6, and the average of its neighbors is (7+2) / 2 = 4.5.
// When i=3, nums[i] = 2, and the average of its neighbors is (6+0) / 2 = 3.

LEETCODE_SOLUTION_UNITTEST(1968, ArrayWithElementsNotEqualToAverageOfNeighbors,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 2, 0, 9, 7};
  vector<int> expect   = {6, 0, 9, 2, 7};
  vector<int> actual   = solution->rearrangeArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}
