// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Units on a Truck
//
// https://leetcode.com/problems/maximum-units-on-a-truck/
//
// Question ID: 1710
// Difficult  : Easy
// Solve Date : 2022/07/01 18:20

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1710. Maximum Units on a Truck|:
//
// You are assigned to put some amount of boxes onto one truck. You are given a
// 2D array |boxTypes|, where |boxTypes[i] = [numberOfBoxesᵢ,
// numberOfUnitsPerBoxᵢ]|:
//
//  • |numberOfBoxesᵢ| is the number of boxes of type |i|.
//
//  • |numberOfUnitsPerBoxᵢ|^{ }is the number of units in each box of the type
//  |i|.
// You are also given an integer |truckSize|, which is the maximum number of
// boxes that can be put on the truck. You can choose any boxes to put on the
// truck as long as the numberof boxes does not exceed |truckSize|. Return the
// maximum total number of units that can be put on the truck.
//

LEETCODE_BEGIN_RESOLVING(1710, MaximumUnitsOnATruck, Solution);

class Solution {
public:
  int maximumUnits(vector<vector<int>> &boxTypes, int truckSize) {
    sort(boxTypes.begin(), boxTypes.end(), [](auto &x, auto &y) {
      return x[1] == y[1] ? x[0] < y[0] : x[1] > y[1];
    });
    int res = 0;
    for (auto box : boxTypes) {
      auto size = box[0], unit = box[1];
      int  put_size = min(size, truckSize);
      res += put_size * unit;
      truckSize -= put_size;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= boxTypes.length <= 1000|
// * |1 <= numberOfBoxesᵢ, numberOfUnitsPerBoxᵢ <= 1000|
// * |1 <= truckSize <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
// Output: 8
//
// There are:
// - 1 box of the first type that contains 3 units.
// - 2 boxes of the second type that contain 2 units each.
// - 3 boxes of the third type that contain 1 unit each.
// You can take all the boxes of the first and second types, and one box of the
// third type. The total number of units will be = (1 * 3) + (2 * 2) + (1 * 1)
// = 8.

LEETCODE_SOLUTION_UNITTEST(1710, MaximumUnitsOnATruck, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> boxTypes = {
      {1, 3},
      {2, 2},
      {3, 1}
  };
  int truckSize = 4;
  int expect    = 8;
  int actual    = solution->maximumUnits(boxTypes, truckSize);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: boxTypes = [[5,10],[2,5],[4,7],[3,9]], truckSize = 10
// Output: 91
//

LEETCODE_SOLUTION_UNITTEST(1710, MaximumUnitsOnATruck, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> boxTypes = {
      {5, 10},
      {2,  5},
      {4,  7},
      {3,  9}
  };
  int truckSize = 10;
  int expect    = 91;
  int actual    = solution->maximumUnits(boxTypes, truckSize);
  LCD_EXPECT_EQ(expect, actual);
}
