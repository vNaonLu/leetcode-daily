// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Two Out of Three
//
// https://leetcode.com/problems/two-out-of-three/
//
// Question ID: 2032
// Difficult  : Easy
// Solve Date : 2022/12/12 19:51

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2032. Two Out of Three|:
//
// Given three integer arrays |nums1|, |nums2|, and |nums3|, return a distinct
// array containing all the values that are present in at least two out of the
// three arrays. You may return the values in any order.
//

LEETCODE_BEGIN_RESOLVING(2032, TwoOutOfThree, Solution);

class Solution {
private:
  void helper(unordered_map<int, int> &out, vector<int> const &ns) {
    auto cnt = unordered_set<int>(ns.begin(), ns.end());
    for (auto x : cnt) {
      ++out[x];
    }
  }

public:
  vector<int> twoOutOfThree(vector<int> &nums1, vector<int> &nums2,
                            vector<int> &nums3) {
    auto freq = unordered_map<int, int>();

    helper(freq, nums1);
    helper(freq, nums2);
    helper(freq, nums3);

    auto res = vector<int>();
    for (auto [x, cnt] : freq) {
      if (cnt >= 2) {
        res.emplace_back(x);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length, nums3.length <= 100|
// * |1 <= nums1[i], nums2[j], nums3[k] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
// Output: [3,2]
//
// The values that are present in at least two arrays are:
// - 3, in all three arrays.
// - 2, in nums1 and nums2.

LEETCODE_SOLUTION_UNITTEST(2032, TwoOutOfThree, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 1, 3, 2};
  vector<int> nums2    = {2, 3};
  vector<int> nums3    = {3};
  vector<int> expect   = {3, 2};
  vector<int> actual   = solution->twoOutOfThree(nums1, nums2, nums3);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [3,1], nums2 = [2,3], nums3 = [1,2]
// Output: [2,3,1]
//
// The values that are present in at least two arrays are:
// - 2, in nums2 and nums3.
// - 3, in nums1 and nums2.
// - 1, in nums1 and nums3.

LEETCODE_SOLUTION_UNITTEST(2032, TwoOutOfThree, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {3, 1};
  vector<int> nums2    = {2, 3};
  vector<int> nums3    = {1, 2};
  vector<int> expect   = {2, 3, 1};
  vector<int> actual   = solution->twoOutOfThree(nums1, nums2, nums3);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums1 = [1,2,2], nums2 = [4,3,3], nums3 = [5]
// Output: []
//
// No value is present in at least two arrays.

LEETCODE_SOLUTION_UNITTEST(2032, TwoOutOfThree, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2, 2};
  vector<int> nums2    = {4, 3, 3};
  vector<int> nums3    = {5};
  vector<int> expect   = {};
  vector<int> actual   = solution->twoOutOfThree(nums1, nums2, nums3);
  LCD_EXPECT_EQ(expect, actual);
}
