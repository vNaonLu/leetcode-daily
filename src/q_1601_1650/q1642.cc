// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Furthest Building You Can Reach
//
// https://leetcode.com/problems/furthest-building-you-can-reach/
//
// Question ID: 1642
// Difficult  : Medium
// Solve Date : 2022/06/21 22:12

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1642. Furthest Building You Can Reach|:
//
// You are given an integer array |heights| representing the heights of
// buildings, some |bricks|, and some |ladders|. You start your journey from
// building |0| and move to the next building by possibly using bricks or
// ladders. While moving from building |i| to building |i+1| (0-indexed),
//
//  • If the current building's height is greater than or equal to the next
//  building's height, you do not need a ladder or bricks.
//
//  • If the current building's height is less than the next building's height,
//  you can either use one ladder or |(h[i+1] - h[i])| bricks.
// Return the furthest building index (0-indexed) you can reach if you use the
// given ladders and bricks optimally.
//

LEETCODE_BEGIN_RESOLVING(1642, FurthestBuildingYouCanReach, Solution);

class Solution {
private:
  bool helper(vector<int> &h, int b, int l, int m) {
    vector<int> diff;
    for (int i = 1; i <= m; ++i) {
      if (h[i] > h[i - 1]) {
        diff.emplace_back(h[i] - h[i - 1]);
      }
    }
    sort(diff.begin(), diff.end(), greater<int>());
    int r = diff.size();
    for (int i = l; i < r; ++i) {
      if (diff[i] > b) {
        return false;
      }
      b -= diff[i];
    }

    return true;
  }

public:
  int furthestBuilding(vector<int> &heights, int bricks, int ladders) {
    int l = 0, r = heights.size() - 1;
    while (l < r) {
      int m = (l + r + 1) / 2;
      if (helper(heights, bricks, ladders, m)) {
        l = m;
      } else {
        r = m - 1;
      }
    }

    return l;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= heights.length <= 10⁵|
// * |1 <= heights[i] <= 10⁶|
// * |0 <= bricks <= 10⁹|
// * |0 <= ladders <= heights.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
// Output: 4
//
// Starting at building 0, you can follow these steps:
// - Go to building 1 without using ladders nor bricks since 4 >= 2.
// - Go to building 2 using 5 bricks. You must use either bricks or ladders
// because 2 < 7.
// - Go to building 3 without using ladders nor bricks since 7 >= 6.
// - Go to building 4 using your only ladder. You must use either bricks or
// ladders because 6 < 9. It is impossible to go beyond building 4 because you
// do not have any more bricks or ladders.

LEETCODE_SOLUTION_UNITTEST(1642, FurthestBuildingYouCanReach, example_1) {
  auto        solution = MakeSolution();
  vector<int> heights  = {4, 2, 7, 6, 9, 14, 12};
  int         bricks   = 5;
  int         ladders  = 1;
  int         expect   = 4;
  int         actual   = solution->furthestBuilding(heights, bricks, ladders);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(1642, FurthestBuildingYouCanReach, example_2) {
  auto        solution = MakeSolution();
  vector<int> heights  = {4, 12, 2, 7, 3, 18, 20, 3, 19};
  int         bricks   = 10;
  int         ladders  = 2;
  int         expect   = 7;
  int         actual   = solution->furthestBuilding(heights, bricks, ladders);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: heights = [14,3,19,3], bricks = 17, ladders = 0
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1642, FurthestBuildingYouCanReach, example_3) {
  auto        solution = MakeSolution();
  vector<int> heights  = {14, 3, 19, 3};
  int         bricks   = 17;
  int         ladders  = 0;
  int         expect   = 3;
  int         actual   = solution->furthestBuilding(heights, bricks, ladders);
  LCD_EXPECT_EQ(expect, actual);
}
