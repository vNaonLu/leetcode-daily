// Copyright 2023 Naon Lu
//
// This file describes the solution of
// How Many Numbers Are Smaller Than the Current Number
//
// https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/
//
// Question ID: 1365
// Difficult  : Easy
// Solve Date : 2023/08/05 22:19

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1365. How Many Numbers Are Smaller Than the Current Number|:
//
// Given the array |nums|, for each |nums[i]| find out how many numbers in the
// array are smaller than it. That is, for each |nums[i]| you have to count the
// number of valid |j's| such that |j != i| and |nums[j] < nums[i]|. Return the
// answer in an array.
//
//

LEETCODE_BEGIN_RESOLVING(1365, HowManyNumbersAreSmallerThanTheCurrentNumber,
                         Solution);

class Solution {
public:
  vector<int> smallerNumbersThanCurrent(vector<int> &nums) {
    vector<int>   res;
    multiset<int> st(nums.begin(), nums.end());
    for (auto x : nums) {
      res.emplace_back(distance(st.begin(), st.find(x)));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 500|
// * |0 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [8,1,2,2,3]
// Output: [4,0,1,1,3]
//
// For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3).
// For nums[1]=1 does not exist any smaller number than it.
// For nums[2]=2 there exist one smaller number than it (1).
// For nums[3]=2 there exist one smaller number than it (1).
// For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).

LEETCODE_SOLUTION_UNITTEST(1365, HowManyNumbersAreSmallerThanTheCurrentNumber,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {8, 1, 2, 2, 3};
  vector<int> expect   = {4, 0, 1, 1, 3};
  vector<int> actual   = solution->smallerNumbersThanCurrent(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [6,5,4,8]
// Output: [2,1,0,3]
//

LEETCODE_SOLUTION_UNITTEST(1365, HowManyNumbersAreSmallerThanTheCurrentNumber,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 5, 4, 8};
  vector<int> expect   = {2, 1, 0, 3};
  vector<int> actual   = solution->smallerNumbersThanCurrent(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [7,7,7,7]
// Output: [0,0,0,0]
//

LEETCODE_SOLUTION_UNITTEST(1365, HowManyNumbersAreSmallerThanTheCurrentNumber,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 7, 7, 7};
  vector<int> expect   = {0, 0, 0, 0};
  vector<int> actual   = solution->smallerNumbersThanCurrent(nums);
  LCD_EXPECT_EQ(expect, actual);
}
