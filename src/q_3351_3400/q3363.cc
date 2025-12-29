// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Maximum Number of Fruits Collected
//
// https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/
//
// Question ID: 3363
// Difficult  : Hard
// Solve Date : 2025/08/07 20:25

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3363. Find the Maximum Number of Fruits Collected|:
//
// There is a game dungeon comprised of |n x n| rooms arranged in a fruits.
// You are given a 2D array |fruits| of size |n x n|, where |fruits[i][j]|
// represents the number of fruits in the room |(i, j)|. Three children will
// play in the game dungeon, with initial positions at the corner rooms |(0,
// 0)|, |(0, n - 1)|, and |(n - 1, 0)|. The children will make exactly |n - 1|
// moves according to the following rules to reach the room |(n - 1, n - 1)|:
//
//  • The child starting from |(0, 0)| must move from their current room |(i,
//  j)| to one of the rooms |(i + 1, j + 1)|, |(i + 1, j)|, and |(i, j + 1)| if
//  the target room exists.
//
//  • The child starting from |(0, n - 1)| must move from their current room
//  |(i, j)| to one of the rooms |(i + 1, j - 1)|, |(i + 1, j)|, and |(i + 1, j
//  + 1)| if the target room exists.
//
//  • The child starting from |(n - 1, 0)| must move from their current room
//  |(i, j)| to one of the rooms |(i - 1, j + 1)|, |(i, j + 1)|, and |(i + 1, j
//  + 1)| if the target room exists.
// When a child enters a room, they will collect all the fruits there. If two or
// more children enter the same room, only one child will collect the fruits,
// and the room will be emptied after they leave. Return the maximum number of
// fruits the children can collect from the dungeon.
//
//

LEETCODE_BEGIN_RESOLVING(3363, FindTheMaximumNumberOfFruitsCollected, Solution);

class Solution {
public:
  int maxCollectedFruits(vector<vector<int>> &fruits) {
    int n   = fruits.size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
      res += fruits[i][i];
    }
    for (int pass = 0; pass < 2; pass++) {
      if (pass == 1) {
        for (int i = 0; i < n; i++) {
          for (int j = i + 1; j < n; j++) {
            swap(fruits[i][j], fruits[j][i]);
          }
        }
      }

      vector<int> prev(n, -1), curr(n, -1);
      prev[n - 1] = fruits[0][n - 1];

      for (int row = 1; row < n - 1; row++) {
        fill(curr.begin(), curr.end(), -1);
        for (int i = 0; i < n; i++) {
          if (prev[i] < 0)
            continue;
          if (i > 0)
            curr[i - 1] = max(curr[i - 1], prev[i] + fruits[row][i - 1]);
          if (i < n - 1)
            curr[i + 1] = max(curr[i + 1], prev[i] + fruits[row][i + 1]);
          curr[i] = max(curr[i], prev[i] + fruits[row][i]);
        }
        swap(prev, curr);
      }
      res += prev[n - 1];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n == fruits.length == fruits[i].length <= 1000|
// * |0 <= fruits[i][j] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]
// Output: 100
//

LEETCODE_SOLUTION_UNITTEST(3363, FindTheMaximumNumberOfFruitsCollected,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> fruits   = {
      { 1,  2,  3,  4},
      { 5,  6,  8,  7},
      { 9, 10, 11, 12},
      {13, 14, 15, 16}
  };
  int expect = 100;
  int actual = solution->maxCollectedFruits(fruits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: fruits = [[1,1],[1,1]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3363, FindTheMaximumNumberOfFruitsCollected,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> fruits   = {
      {1, 1},
      {1, 1}
  };
  int expect = 4;
  int actual = solution->maxCollectedFruits(fruits);
  LCD_EXPECT_EQ(expect, actual);
}
