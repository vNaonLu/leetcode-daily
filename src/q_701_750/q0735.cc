// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Asteroid Collision
//
// https://leetcode.com/problems/asteroid-collision/
//
// Question ID: 735
// Difficult  : Medium
// Solve Date : 2022/09/25 18:35

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |735. Asteroid Collision|:
//
// We are given an array |asteroids| of integers representing asteroids in a
// row. For each asteroid, the absolute value represents its size, and the sign
// represents its direction (positive meaning right, negative meaning left).
// Each asteroid moves at the same speed. Find out the state of the asteroids
// after all collisions. If two asteroids meet, the smaller one will explode. If
// both are the same size, both will explode. Two asteroids moving in the same
// direction will never meet.
//

LEETCODE_BEGIN_RESOLVING(735, AsteroidCollision, Solution);

class Solution {
public:
  vector<int> asteroidCollision(vector<int> &asteroids) {
    auto res = vector<int>();
    for (auto x : asteroids) {
      auto explode = false;
      while (!res.empty() && x < 0 && res.back() > 0 && !explode) {
        if (res.back() < -x) {
          res.pop_back();
        } else if (res.back() == -x) {
          res.pop_back();
          explode = true;
        } else {
          explode = true;
        }
      }

      if (!explode) {
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
// * |2 <= asteroids.length <= 10⁴|
// * |-1000 <= asteroids[i] <= 1000|
// * |asteroids[i] != 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: asteroids = [5,10,-5]
// Output: [5,10]
//
// The 10 and -5 collide resulting in 10. The 5 and 10 never collide.

LEETCODE_SOLUTION_UNITTEST(735, AsteroidCollision, example_1) {
  auto        solution  = MakeSolution();
  vector<int> asteroids = {5, 10, -5};
  vector<int> expect    = {5, 10};
  vector<int> actual    = solution->asteroidCollision(asteroids);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: asteroids = [8,-8]
// Output: []
//
// The 8 and -8 collide exploding each other.

LEETCODE_SOLUTION_UNITTEST(735, AsteroidCollision, example_2) {
  auto        solution  = MakeSolution();
  vector<int> asteroids = {8, -8};
  vector<int> expect    = {};
  vector<int> actual    = solution->asteroidCollision(asteroids);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: asteroids = [10,2,-5]
// Output: [10]
//
// The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.

LEETCODE_SOLUTION_UNITTEST(735, AsteroidCollision, example_3) {
  auto        solution  = MakeSolution();
  vector<int> asteroids = {10, 2, -5};
  vector<int> expect    = {10};
  vector<int> actual    = solution->asteroidCollision(asteroids);
  LCD_EXPECT_EQ(expect, actual);
}
