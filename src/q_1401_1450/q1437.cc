// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check If All 1's Are at Least Length K Places Away
//
// https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/
//
// Question ID: 1437
// Difficult  : Easy
// Solve Date : 2022/05/24 14:03

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1437. Check If All 1's Are at Least Length K Places Away|:
//
// Given an binary array |nums| and an integer |k|, return |true| if all |1|'s
// are at least |k| places away from each other, otherwise return |false|.
//

LEETCODE_BEGIN_RESOLVING(1437, CheckIfAll1SAreAtLeastLengthKPlacesAway,
                         Solution);

class Solution {
public:
  bool kLengthApart(vector<int> &nums, int k) {
    int l = 0;
    while (l < nums.size() && nums[l] == 0) {
      ++l;
    }

    for (int r = l + 1; r < nums.size(); ++r) {
      if (nums[r] == 1) {
        if (r - l - 1 < k) {
          return false;
        }

        l = r;
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= k <= nums.length|
// * |nums[i]| is |0| or |1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,0,0,0,1,0,0,1], k = 2
// Output: true
//
// Each of the 1s are at least 2 places away from each other.

LEETCODE_SOLUTION_UNITTEST(1437, CheckIfAll1SAreAtLeastLengthKPlacesAway,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 0, 0, 0, 1, 0, 0, 1};
  int         k        = 2;
  bool        expect   = true;
  bool        actual   = solution->kLengthApart(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,0,0,1,0,1], k = 2
// Output: false
//
// The second 1 and third 1 are only one apart from each other.

LEETCODE_SOLUTION_UNITTEST(1437, CheckIfAll1SAreAtLeastLengthKPlacesAway,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 0, 0, 1, 0, 1};
  int         k        = 2;
  bool        expect   = false;
  bool        actual   = solution->kLengthApart(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}
