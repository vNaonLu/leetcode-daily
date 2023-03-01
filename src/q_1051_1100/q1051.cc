// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Height Checker
//
// https://leetcode.com/problems/height-checker/
//
// Question ID: 1051
// Difficult  : Easy
// Solve Date : 2022/11/05 12:20

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1051. Height Checker|:
//
// A school is trying to take an annual photo of all the students. The students
// are asked to stand in a single file line in non-decreasing order by height.
// Let this ordering be represented by the integer array |expected| where
// |expected[i]| is the expected height of the |iᵗʰ| student in line. You are
// given an integer array |heights| representing the current order that the
// students are standing in. Each |heights[i]| is the height of the |iᵗʰ|
// student in line (0-indexed). Return the number of indices where |heights[i]
// != expected[i]|.
//

LEETCODE_BEGIN_RESOLVING(1051, HeightChecker, Solution);

class Solution {
public:
  int heightChecker(vector<int> &heights) {
    auto expected = heights;
    auto res      = (int)0;
    sort(expected.begin(), expected.end());
    for (auto i = 0; i < heights.size(); ++i) {
      if (heights[i] != expected[i]) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= heights.length <= 100|
// * |1 <= heights[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: heights = [1,1,4,2,1,3]
// Output: 3
//
// heights: [1,1,4,2,1,3]
// expected: [1,1,1,2,3,4]
// Indices 2, 4, and 5 do not match.

LEETCODE_SOLUTION_UNITTEST(1051, HeightChecker, example_1) {
  auto        solution = MakeSolution();
  vector<int> heights  = {1, 1, 4, 2, 1, 3};
  int         expect   = 3;
  int         actual   = solution->heightChecker(heights);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: heights = [5,1,2,3,4]
// Output: 5
//
// heights: [5,1,2,3,4]
// expected: [1,2,3,4,5]
// All indices do not match.

LEETCODE_SOLUTION_UNITTEST(1051, HeightChecker, example_2) {
  auto        solution = MakeSolution();
  vector<int> heights  = {5, 1, 2, 3, 4};
  int         expect   = 5;
  int         actual   = solution->heightChecker(heights);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: heights = [1,2,3,4,5]
// Output: 0
//
// heights: [1,2,3,4,5]
// expected: [1,2,3,4,5]
// All indices match.

LEETCODE_SOLUTION_UNITTEST(1051, HeightChecker, example_3) {
  auto        solution = MakeSolution();
  vector<int> heights  = {1, 2, 3, 4, 5};
  int         expect   = 0;
  int         actual   = solution->heightChecker(heights);
  LCD_EXPECT_EQ(expect, actual);
}
