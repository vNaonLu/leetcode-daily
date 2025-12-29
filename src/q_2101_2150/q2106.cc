// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Fruits Harvested After at Most K Steps
//
// https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/
//
// Question ID: 2106
// Difficult  : Hard
// Solve Date : 2025/08/03 13:46

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2106. Maximum Fruits Harvested After at Most K Steps|:
//
// Fruits are available at some positions on an infinite x-axis. You are given a
// 2D integer array |fruits| where |fruits[i] = [positionᵢ, amountᵢ]| depicts
// |amountᵢ| fruits at the position |positionᵢ|. |fruits| is already sorted by
// |positionᵢ| in ascending order, and each |positionᵢ| is unique. You are also
// given an integer |startPos| and an integer |k|. Initially, you are at the
// position |startPos|. From any position, you can either walk to the left or
// right. It takes one step to move one unit on the x-axis, and you can walk at
// most |k| steps in total. For every position you reach, you harvest all the
// fruits at that position, and the fruits will disappear from that position.
// Return the maximum total number of fruits you can harvest.
//
//

LEETCODE_BEGIN_RESOLVING(2106, MaximumFruitsHarvestedAfterAtMostKSteps,
                         Solution);

class Solution {
public:
  int maxTotalFruits(vector<vector<int>> &fruits, int startPos, int k) {
    auto i0 = lower_bound(fruits.begin(), fruits.end(),
                          vector<int>(1, startPos - k)) -
              fruits.begin();
    auto in = upper_bound(fruits.begin(), fruits.end(),
                          vector<int>(1, startPos + k + 1)) -
              fruits.begin();

    int res  = 0;
    int wsum = 0;
    for (int l = i0, r = i0; r < in; r++) {
      wsum += fruits[r][1];
      const int R = fruits[r][0];
      while (l <= r && step(R, fruits[l][0], startPos) > k) {
        wsum -= fruits[l][1];
        l++;
      }
      res = max(res, wsum);
    }
    return res;
  }

private:
  int step(int r, int l, int start) {
    return min(start - 2 * l + r, 2 * r - start - l);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= fruits.length <= 10⁵|
// * |fruits[i].length == 2|
// * |0 <= startPos, positionᵢ <= 2 * 10⁵|
// * |positionᵢ₋₁ < positionᵢ| for any |i > 0| (0-indexed)
// * |1 <= amountᵢ <= 10⁴|
// * |0 <= k <= 2 * 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(2106, MaximumFruitsHarvestedAfterAtMostKSteps,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> fruits   = {
      {2, 8},
      {6, 3},
      {8, 6}
  };
  int startPos = 5;
  int k        = 4;
  int expect   = 9;
  int actual   = solution->maxTotalFruits(fruits, startPos, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
// Output: 14
//

LEETCODE_SOLUTION_UNITTEST(2106, MaximumFruitsHarvestedAfterAtMostKSteps,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> fruits   = {
      { 0, 9},
      { 4, 1},
      { 5, 7},
      { 6, 2},
      { 7, 4},
      {10, 9}
  };
  int startPos = 5;
  int k        = 4;
  int expect   = 14;
  int actual   = solution->maxTotalFruits(fruits, startPos, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: fruits = [[0,3],[6,4],[8,5]], startPos = 3, k = 2
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2106, MaximumFruitsHarvestedAfterAtMostKSteps,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> fruits   = {
      {0, 3},
      {6, 4},
      {8, 5}
  };
  int startPos = 3;
  int k        = 2;
  int expect   = 0;
  int actual   = solution->maxTotalFruits(fruits, startPos, k);
  LCD_EXPECT_EQ(expect, actual);
}
