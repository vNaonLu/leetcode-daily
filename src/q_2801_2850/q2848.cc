// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Points That Intersect With Cars
//
// https://leetcode.com/problems/points-that-intersect-with-cars/
//
// Question ID: 2848
// Difficult  : Easy
// Solve Date : 2024/01/17 19:08

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2848. Points That Intersect With Cars|:
//
// You are given a 0-indexed 2D integer array |nums| representing the
// coordinates of the cars parking on a number line. For any index |i|, |nums[i]
// = [startᵢ, endᵢ]| where |startᵢ| is the starting point of the |iᵗʰ| car and
// |endᵢ| is the ending point of the |iᵗʰ| car. Return the number of integer
// points on the line that are covered with any part of a car.
//
//

LEETCODE_BEGIN_RESOLVING(2848, PointsThatIntersectWithCars, Solution);

class Solution {
public:
  int numberOfPoints(vector<vector<int>> &nums) {
    set<int> res;
    for (auto &v : nums) {
      for (int i = v[0]; i <= v[1]; ++i) {
        res.emplace(i);
      }
    }
    return res.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |nums[i].length == 2|
// * |1 <= startᵢ <= endᵢ <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [[3,6],[1,5],[4,7]]
// Output: 7
//
// All the points from 1 to 7 intersect at least one car, therefore the answer
// would be 7.

LEETCODE_SOLUTION_UNITTEST(2848, PointsThatIntersectWithCars, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> nums     = {
      {3, 6},
      {1, 5},
      {4, 7}
  };
  int expect = 7;
  int actual = solution->numberOfPoints(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [[1,3],[5,8]]
// Output: 7
//
// Points intersecting at least one car are 1, 2, 3, 5, 6, 7, 8. There are a
// total of 7 points, therefore the answer would be 7.

LEETCODE_SOLUTION_UNITTEST(2848, PointsThatIntersectWithCars, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> nums     = {
      {1, 3},
      {5, 8}
  };
  int expect = 7;
  int actual = solution->numberOfPoints(nums);
  LCD_EXPECT_EQ(expect, actual);
}
