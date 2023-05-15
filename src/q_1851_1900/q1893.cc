// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if All the Integers in a Range Are Covered
//
// https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/
//
// Question ID: 1893
// Difficult  : Easy
// Solve Date : 2023/05/15 13:44

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1893. Check if All the Integers in a Range Are Covered|:
//
// You are given a 2D integer array |ranges| and two integers |left| and
// |right|. Each |ranges[i] = [startᵢ, endᵢ]| represents an inclusive interval
// between |startᵢ| and |endᵢ|. Return |true| if each integer in the inclusive
// range |[left, right]| is covered by at least one interval in |ranges|. Return
// |false| otherwise. An integer |x| is covered by an interval |ranges[i] =
// [startᵢ, endᵢ]| if |startᵢ <= x <= endᵢ|.
//
//

LEETCODE_BEGIN_RESOLVING(1893, CheckIfAllTheIntegersInARangeAreCovered,
                         Solution);

class Solution {
public:
  bool isCovered(vector<vector<int>> &ranges, int left, int right) {
    vector<int> covered(51, 0);
    for (auto &v : ranges) {
      for (int i = v[0]; i <= v[1]; ++i) {
        covered[i] = 1;
      }
    }
    for (int i = left; i <= right; ++i) {
      if (covered[i] == 0) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= ranges.length <= 50|
// * |1 <= startᵢ <= endᵢ <= 50|
// * |1 <= left <= right <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ranges = [[1,2],[3,4],[5,6]], left = 2, right = 5
// Output: true
//
// Every integer between 2 and 5 is covered:
// - 2 is covered by the first range.
// - 3 and 4 are covered by the second range.
// - 5 is covered by the third range.

LEETCODE_SOLUTION_UNITTEST(1893, CheckIfAllTheIntegersInARangeAreCovered,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> ranges   = {
      {1, 2},
      {3, 4},
      {5, 6}
  };
  int  left   = 2;
  int  right  = 5;
  bool expect = true;
  bool actual = solution->isCovered(ranges, left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ranges = [[1,10],[10,20]], left = 21, right = 21
// Output: false
//
// 21 is not covered by any range.

LEETCODE_SOLUTION_UNITTEST(1893, CheckIfAllTheIntegersInARangeAreCovered,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> ranges   = {
      { 1, 10},
      {10, 20}
  };
  int  left   = 21;
  int  right  = 21;
  bool expect = false;
  bool actual = solution->isCovered(ranges, left, right);
  LCD_EXPECT_EQ(expect, actual);
}
