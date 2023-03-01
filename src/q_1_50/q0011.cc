// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Container With Most Water
//
// https://leetcode.com/problems/container-with-most-water/
//
// Question ID: 11
// Difficult  : Medium
// Solve Date : 2021/09/22 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |11. Container With Most Water|:
//
// You are given an integer array |height| of length |n|. There are |n| vertical
// lines drawn such that the two endpoints of the |iᵗʰ| line are |(i, 0)| and
// |(i, height[i])|. Find two lines that together with the x-axis form a
// container, such that the container contains the most water. Return the
// maximum amount of water a container can store. Notice that you may not slant
// the container.  
//

LEETCODE_BEGIN_RESOLVING(11, ContainerWithMostWater, Solution);

class Solution {
public:
  int maxArea(vector<int> &height) {
    int res = 0;
    int l = 0, r = height.size() - 1;
    while (l < r) {
      res = max(res, min(height[l], height[r]) * (r - l));
      if (height[l] <= height[r]) {
        ++l;
      } else {
        --r;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == height.length|
// * |2 <= n <= 10⁵|
// * |0 <= height[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: height = [1,8,6,2,5,4,8,3,7]
// Output: 49
//
// The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In
// this case, the max area of water (blue section) the container can contain
// is 49.

LEETCODE_SOLUTION_UNITTEST(11, ContainerWithMostWater, example_1) {
  auto        solution = MakeSolution();
  vector<int> height   = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  int         expect   = 49;
  int         actual   = solution->maxArea(height);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: height = [1,1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(11, ContainerWithMostWater, example_2) {
  auto        solution = MakeSolution();
  vector<int> height   = {1, 1};
  int         expect   = 1;
  int         actual   = solution->maxArea(height);
  LCD_EXPECT_EQ(expect, actual);
}
