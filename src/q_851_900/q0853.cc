// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Car Fleet
//
// https://leetcode.com/problems/car-fleet/
//
// Question ID: 853
// Difficult  : Medium
// Solve Date : 2024/08/29 22:08

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |853. Car Fleet|:
//
// There are |n| cars at given miles away from the starting mile 0, traveling to
// reach the mile |target|. You are given two integer array |position| and
// |speed|, both of length |n|, where |position[i]| is the starting mile of the
// |iᵗʰ| car and |speed[i]| is the speed of the |iᵗʰ| car in miles per hour. A
// car cannot pass another car, but it can catch up and then travel next to it
// at the speed of the slower car. A car fleet is a car or cars driving next to
// each other. The speed of the car fleet is the minimum speed of any car in the
// fleet. If a car catches up to a car fleet at the mile |target|, it will still
// be considered as part of the car fleet. Return the number of car fleets that
// will arrive at the destination.
//
//

LEETCODE_BEGIN_RESOLVING(853, CarFleet, Solution);

class Solution {
public:
  int carFleet(int target, vector<int> &position, vector<int> &speed) {
    map<int, double> mp;
    for (int i = 0; i < position.size(); ++i) {
      mp[-position[i]] = (1.0 * (target - position[i]) / speed[i]);
    }
    int    res = 0;
    double cur = 0;
    for (auto [_, x] : mp) {
      if (x > cur) {
        cur = x;
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == position.length == speed.length|
// * |1 <= n <= 10⁵|
// * |0 < target <= 10⁶|
// * |0 <= position[i] < target|
// * All the values of |position| are unique.
// * |0 < speed[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(853, CarFleet, example_1) {
  auto        solution = MakeSolution();
  int         target   = 12;
  vector<int> position = {10, 8, 0, 5, 3};
  vector<int> speed    = {2, 4, 1, 1, 3};
  int         expect   = 3;
  int         actual   = solution->carFleet(target, position, speed);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: target = 10, position = [3], speed = [3]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(853, CarFleet, example_2) {
  auto        solution = MakeSolution();
  int         target   = 10;
  vector<int> position = {3};
  vector<int> speed    = {3};
  int         expect   = 1;
  int         actual   = solution->carFleet(target, position, speed);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: target = 100, position = [0,2,4], speed = [4,2,1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(853, CarFleet, example_3) {
  auto        solution = MakeSolution();
  int         target   = 100;
  vector<int> position = {0, 2, 4};
  vector<int> speed    = {4, 2, 1};
  int         expect   = 1;
  int         actual   = solution->carFleet(target, position, speed);
  LCD_EXPECT_EQ(expect, actual);
}
