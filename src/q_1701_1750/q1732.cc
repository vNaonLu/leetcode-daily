// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Highest Altitude
//
// https://leetcode.com/problems/find-the-highest-altitude/
//
// Question ID: 1732
// Difficult  : Easy
// Solve Date : 2022/12/23 12:01

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1732. Find the Highest Altitude|:
//
// There is a biker going on a road trip. The road trip consists of |n + 1|
// points at different altitudes. The biker starts his trip on point |0| with
// altitude equal |0|. You are given an integer array |gain| of length |n| where
// |gain[i]| is the net gain in altitude between points |i|​​​​​​
// and |i + 1| for all ( |0 <= i < n)|. Return the highest altitude of a point.
//

LEETCODE_BEGIN_RESOLVING(1732, FindTheHighestAltitude, Solution);

class Solution {
public:
  int largestAltitude(vector<int> &gain) {
    auto alt = (int)0;
    auto res = (int)0;
    for (auto x : gain) {
      alt += x;
      res = max(res, alt);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == gain.length|
// * |1 <= n <= 100|
// * |-100 <= gain[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: gain = [-5,1,5,0,-7]
// Output: 1
//
// The altitudes are [0,-5,-4,1,1,-6]. The highest is 1.

LEETCODE_SOLUTION_UNITTEST(1732, FindTheHighestAltitude, example_1) {
  auto        solution = MakeSolution();
  vector<int> gain     = {-5, 1, 5, 0, -7};
  int         expect   = 1;
  int         actual   = solution->largestAltitude(gain);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: gain = [-4,-3,-2,-1,4,3,2]
// Output: 0
//
// The altitudes are [0,-4,-7,-9,-10,-6,-3,-1]. The highest is 0.

LEETCODE_SOLUTION_UNITTEST(1732, FindTheHighestAltitude, example_2) {
  auto        solution = MakeSolution();
  vector<int> gain     = {-4, -3, -2, -1, 4, 3, 2};
  int         expect   = 0;
  int         actual   = solution->largestAltitude(gain);
  LCD_EXPECT_EQ(expect, actual);
}
