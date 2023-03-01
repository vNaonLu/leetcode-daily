// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Common Value
//
// https://leetcode.com/problems/minimum-common-value/
//
// Question ID: 2540
// Difficult  : Easy
// Solve Date : 2023/02/05 21:53

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2540. Minimum Common Value|:
//
// Given two integer arrays |nums1| and |nums2|, sorted in non-decreasing order,
// return the minimum integer common to both arrays. If there is no common
// integer amongst |nums1| and |nums2|, return |-1|. Note that an integer is
// said to be common to |nums1| and |nums2| if both arrays have at least one
// occurrence of that integer.
//

LEETCODE_BEGIN_RESOLVING(2540, MinimumCommonValue, Solution);

class Solution {
public:
  int getCommon(vector<int> &nums1, vector<int> &nums2) {
    unordered_set<int> memo;
    for (auto x : nums1) {
      memo.emplace(x);
    }
    for (auto x : nums2) {
      if (memo.count(x)) {
        return x;
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 10⁵|
// * |1 <= nums1[i], nums2[j] <= 10⁹|
// * Both |nums1| and |nums2| are sorted in non-decreasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,2,3], nums2 = [2,4]
// Output: 2
//
// The smallest element common to both arrays is 2, so we return 2.

LEETCODE_SOLUTION_UNITTEST(2540, MinimumCommonValue, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2, 3};
  vector<int> nums2    = {2, 4};
  int         expect   = 2;
  int         actual   = solution->getCommon(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
// Output: 2
//
// There are two common elements in the array 2 and 3 out of which 2 is the
// smallest, so 2 is returned.

LEETCODE_SOLUTION_UNITTEST(2540, MinimumCommonValue, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2, 3, 6};
  vector<int> nums2    = {2, 3, 4, 5};
  int         expect   = 2;
  int         actual   = solution->getCommon(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}
