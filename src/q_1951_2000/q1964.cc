// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Longest Valid Obstacle Course at Each Position
//
// https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/
//
// Question ID: 1964
// Difficult  : Hard
// Solve Date : 2023/05/07 14:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1964. Find the Longest Valid Obstacle Course at Each
// Position|:
//
// You want to build some obstacle courses. You are given a 0-indexed integer
// array |obstacles| of length |n|, where |obstacles[i]| describes the height of
// the |iᵗʰ| obstacle. For every index |i| between |0| and |n - 1| (inclusive),
// find the length of the longest obstacle course in |obstacles| such that:
//
//  • You choose any number of obstacles between |0| and |i| inclusive.
//
//  • You must include the |iᵗʰ| obstacle in the course.
//
//  • You must put the chosen obstacles in the same order as they appear in
//  |obstacles|.
//
//  • Every obstacle (except the first) is taller than or the same height as the
//  obstacle immediately before it.
// Return an array |ans| of length |n|, where |ans[i]| is the length of the
// longest obstacle course for index |i| as described above.
//
//

LEETCODE_BEGIN_RESOLVING(1964, FindTheLongestValidObstacleCourseAtEachPosition,
                         Solution);

class Solution {
public:
  vector<int> longestObstacleCourseAtEachPosition(vector<int> &obstacles) {
    vector<int> res;
    vector<int> tmp(obstacles.size(), 1e9);
    for (auto x : obstacles) {
      auto iter = upper_bound(tmp.begin(), tmp.end(), x);
      res.emplace_back(iter - tmp.begin() + 1);
      *iter = x;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == obstacles.length|
// * |1 <= n <= 10⁵|
// * |1 <= obstacles[i] <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: obstacles = [1,2,3,2]
// Output: [1,2,3,3]
//
// The longest valid obstacle course at each position is:
// - i = 0: [1], [1] has length 1.
// - i = 1: [1,2], [1,2] has length 2.
// - i = 2: [1,2,3], [1,2,3] has length 3.
// - i = 3: [1,2,3,2], [1,2,2] has length 3.

LEETCODE_SOLUTION_UNITTEST(1964,
                           FindTheLongestValidObstacleCourseAtEachPosition,
                           example_1) {
  auto        solution  = MakeSolution();
  vector<int> obstacles = {1, 2, 3, 2};
  vector<int> expect    = {1, 2, 3, 3};
  vector<int> actual = solution->longestObstacleCourseAtEachPosition(obstacles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: obstacles = [2,2,1]
// Output: [1,2,1]
//
// The longest valid obstacle course at each position is:
// - i = 0: [2], [2] has length 1.
// - i = 1: [2,2], [2,2] has length 2.
// - i = 2: [2,2,1], [1] has length 1.

LEETCODE_SOLUTION_UNITTEST(1964,
                           FindTheLongestValidObstacleCourseAtEachPosition,
                           example_2) {
  auto        solution  = MakeSolution();
  vector<int> obstacles = {2, 2, 1};
  vector<int> expect    = {1, 2, 1};
  vector<int> actual = solution->longestObstacleCourseAtEachPosition(obstacles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: obstacles = [3,1,5,6,4,2]
// Output: [1,1,2,3,2,2]
//
// The longest valid obstacle course at each position is:
// - i = 0: [3], [3] has length 1.
// - i = 1: [3,1], [1] has length 1.
// - i = 2: [3,1,5], [3,5] has length 2. [1,5] is also valid.
// - i = 3: [3,1,5,6], [3,5,6] has length 3. [1,5,6] is also valid.
// - i = 4: [3,1,5,6,4], [3,4] has length 2. [1,4] is also valid.
// - i = 5: [3,1,5,6,4,2], [1,2] has length 2.

LEETCODE_SOLUTION_UNITTEST(1964,
                           FindTheLongestValidObstacleCourseAtEachPosition,
                           example_3) {
  auto        solution  = MakeSolution();
  vector<int> obstacles = {3, 1, 5, 6, 4, 2};
  vector<int> expect    = {1, 1, 2, 3, 2, 2};
  vector<int> actual = solution->longestObstacleCourseAtEachPosition(obstacles);
  LCD_EXPECT_EQ(expect, actual);
}
