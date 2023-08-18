// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Make Two Arrays Equal by Reversing Subarrays
//
// https://leetcode.com/problems/make-two-arrays-equal-by-reversing-subarrays/
//
// Question ID: 1460
// Difficult  : Easy
// Solve Date : 2023/08/18 18:04

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1460. Make Two Arrays Equal by Reversing Subarrays|:
//
// You are given two integer arrays of equal length |target| and |arr|. In one
// step, you can select any non-empty subarray of |arr| and reverse it. You are
// allowed to make any number of steps. Return |true| if you can make |arr|
// equal to |target| or |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(1460, MakeTwoArraysEqualByReversingSubarrays,
                         Solution);

class Solution {
public:
  bool canBeEqual(vector<int> &target, vector<int> &arr) {
    vector<int> freq(10001, 0);
    for (auto x : target) {
      ++freq[x];
    }
    for (auto x : arr) {
      --freq[x];
    }
    return all_of(freq.begin(), freq.end(), [](auto x) { return x == 0; });
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |target.length == arr.length|
// * |1 <= target.length <= 1000|
// * |1 <= target[i] <= 1000|
// * |1 <= arr[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: target = [1,2,3,4], arr = [2,4,1,3]
// Output: true
//
// You can follow the next steps to convert arr to target:
// 1- Reverse subarray [2,4,1], arr becomes [1,4,2,3]
// 2- Reverse subarray [4,2], arr becomes [1,2,4,3]
// 3- Reverse subarray [4,3], arr becomes [1,2,3,4]
// There are multiple ways to convert arr to target, this is not the only way to
// do so.

LEETCODE_SOLUTION_UNITTEST(1460, MakeTwoArraysEqualByReversingSubarrays,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> target   = {1, 2, 3, 4};
  vector<int> arr      = {2, 4, 1, 3};
  bool        expect   = true;
  bool        actual   = solution->canBeEqual(target, arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: target = [7], arr = [7]
// Output: true
//
// arr is equal to target without any reverses.

LEETCODE_SOLUTION_UNITTEST(1460, MakeTwoArraysEqualByReversingSubarrays,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> target   = {7};
  vector<int> arr      = {7};
  bool        expect   = true;
  bool        actual   = solution->canBeEqual(target, arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: target = [3,7,9], arr = [3,7,11]
// Output: false
//
// arr does not have value 9 and it can never be converted to target.

LEETCODE_SOLUTION_UNITTEST(1460, MakeTwoArraysEqualByReversingSubarrays,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> target   = {3, 7, 9};
  vector<int> arr      = {3, 7, 11};
  bool        expect   = false;
  bool        actual   = solution->canBeEqual(target, arr);
  LCD_EXPECT_EQ(expect, actual);
}
