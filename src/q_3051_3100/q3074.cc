// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Apple Redistribution into Boxes
//
// https://leetcode.com/problems/apple-redistribution-into-boxes/
//
// Question ID: 3074
// Difficult  : Easy
// Solve Date : 2024/03/10 16:35

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3074. Apple Redistribution into Boxes|:
//
// You are given an array |apple| of size |n| and an array |capacity| of size
// |m|. There are |n| packs where the |iᵗʰ| pack contains |apple[i]| apples.
// There are |m| boxes as well, and the |iᵗʰ| box has a capacity of
// |capacity[i]| apples. Return the minimum number of boxes you need to select
// to redistribute these |n| packs of apples into boxes. Note that, apples from
// the same pack can be distributed into different boxes.
//
//

LEETCODE_BEGIN_RESOLVING(3074, AppleRedistributionIntoBoxes, Solution);

class Solution {
public:
  int minimumBoxes(vector<int> &apple, vector<int> &capacity) {
    sort(capacity.begin(), capacity.end(), greater<int>{});
    int res;
    int sum = accumulate(apple.begin(), apple.end(), 0);
    for (res = 0; res < capacity.size() && sum > 0; ++res) {
      sum -= capacity[res];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == apple.length <= 50|
// * |1 <= m == capacity.length <= 50|
// * |1 <= apple[i], capacity[i] <= 50|
// * The input is generated such that it's possible to redistribute packs of
// apples into boxes.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: apple = [1,3,2], capacity = [4,3,1,5,2]
// Output: 2
//
// We will use boxes with capacities 4 and 5.
// It is possible to distribute the apples as the total capacity is greater than
// or equal to the total number of apples.

LEETCODE_SOLUTION_UNITTEST(3074, AppleRedistributionIntoBoxes, example_1) {
  auto        solution = MakeSolution();
  vector<int> apple    = {1, 3, 2};
  vector<int> capacity = {4, 3, 1, 5, 2};
  int         expect   = 2;
  int         actual   = solution->minimumBoxes(apple, capacity);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: apple = [5,5,5], capacity = [2,4,2,7]
// Output: 4
//
// We will need to use all the boxes.

LEETCODE_SOLUTION_UNITTEST(3074, AppleRedistributionIntoBoxes, example_2) {
  auto        solution = MakeSolution();
  vector<int> apple    = {5, 5, 5};
  vector<int> capacity = {2, 4, 2, 7};
  int         expect   = 4;
  int         actual   = solution->minimumBoxes(apple, capacity);
  LCD_EXPECT_EQ(expect, actual);
}
