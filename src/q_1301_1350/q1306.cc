// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Jump Game III
//
// https://leetcode.com/problems/jump-game-iii/
//
// Question ID: 1306
// Difficult  : Medium
// Solve Date : 2021/12/09 17:58

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1306. Jump Game III|:
//
// Given an array of non-negative integers |arr|, you are initially positioned
// at |start| index of the array. When you are at index |i|, you can jump to |i
// + arr[i]| or |i - arr[i]|, check if you can reach to any index with value 0.
// Notice that you can not jump outside of the array at any time.
//  
//

LEETCODE_BEGIN_RESOLVING(1306, JumpGameIII, Solution);

class Solution {
public:
  bool canReach(vector<int> &arr, int start) {
    queue<int> q;
    int        n = arr.size();
    q.push(start);
    while (!q.empty()) {
      int f = q.front();
      q.pop();
      if (f - arr[f] >= 0) {
        if (arr[f - arr[f]] == 0) {
          return true;
        } else if (arr[f - arr[f]] > 0) {
          q.push(f - arr[f]);
        }
      }
      if (f + arr[f] < n) {
        if (arr[f + arr[f]] == 0) {
          return true;
        } else if (arr[f + arr[f]] > 0) {
          q.push(f + arr[f]);
        }
      }
      arr[f] = -1;
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 5 * 10⁴|
// * |0 <= arr[i] < arr.length|
// * |0 <= start < arr.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [4,2,3,0,3,1,2], start = 5
// Output: true
//
// All possible ways to reach at index 3 with value 0 are:
// index 5 -> index 4 -> index 1 -> index 3
// index 5 -> index 6 -> index 4 -> index 1 -> index 3

LEETCODE_SOLUTION_UNITTEST(1306, JumpGameIII, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {4, 2, 3, 0, 3, 1, 2};
  int         start    = 5;
  bool        expect   = true;
  bool        actual   = solution->canReach(arr, start);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [4,2,3,0,3,1,2], start = 0
// Output: true
// Explanation:
// One possible way to reach at index 3 with value 0 is:
// index 0 -> index 4 -> index 1 -> index 3
//

LEETCODE_SOLUTION_UNITTEST(1306, JumpGameIII, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {4, 2, 3, 0, 3, 1, 2};
  int         start    = 0;
  bool        expect   = true;
  bool        actual   = solution->canReach(arr, start);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [3,0,2,1,2], start = 2
// Output: false
//
// There is no way to reach at index 1 with value 0.

LEETCODE_SOLUTION_UNITTEST(1306, JumpGameIII, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 0, 2, 1, 2};
  int         start    = 2;
  bool        expect   = false;
  bool        actual   = solution->canReach(arr, start);
  LCD_EXPECT_EQ(expect, actual);
}
