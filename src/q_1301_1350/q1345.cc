// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Jump Game IV
//
// https://leetcode.com/problems/jump-game-iv/
//
// Question ID: 1345
// Difficult  : Hard
// Solve Date : 2022/01/15 14:26

#include <iosfwd>
#include <list>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1345. Jump Game IV|:
//
// Given an array of integers |arr|, you are initially positioned at the first
// index of the array. In one step you can jump from index |i| to index:
//
//  • |i + 1| where:  |i + 1 < arr.length|.
//
//  • |i - 1| where:  |i - 1 >= 0|.
//
//  • |j| where: |arr[i] == arr[j]| and |i != j|.
// Return the minimum number of steps to reach the last index of the array.
// Notice that you can not jump outside of the array at any time.
//  
//

LEETCODE_BEGIN_RESOLVING(1345, JumpGameIV, Solution);

class Solution {
public:
  int minJumps(vector<int> &arr) {
    unordered_map<int, vector<int>> mp;

    for (int i = 0; i < arr.size(); i++) {
      mp[arr[i]].push_back(i);
    }

    queue<int> q;
    q.push(0);

    vector<int> dis(arr.size(), 1e9);

    dis[0] = 0;

    while (!q.empty()) {
      int index = q.front();
      q.pop();

      if (index == arr.size() - 1)
        return dis[index];

      vector<int> &list = mp[arr[index]];
      list.push_back(index - 1);
      list.push_back(index + 1);

      for (auto &x : list) {
        if (x >= 0 and x < arr.size() and dis[x] > dis[index] + 1) {
          dis[x] = dis[index] + 1;
          q.push(x);
        }
      }
      list.clear();
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 5 * 10⁴|
// * |-10⁸ <= arr[i] <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
// Output: 3
//
// You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the
// last index of the array.

LEETCODE_SOLUTION_UNITTEST(1345, JumpGameIV, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {100, -23, -23, 404, 100, 23, 23, 23, 3, 404};
  int         expect   = 3;
  int         actual   = solution->minJumps(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [7]
// Output: 0
//
// Start index is the last index. You do not need to jump.

LEETCODE_SOLUTION_UNITTEST(1345, JumpGameIV, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {7};
  int         expect   = 0;
  int         actual   = solution->minJumps(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [7,6,9,6,9,6,9,7]
// Output: 1
//
// You can jump directly from index 0 to index 7 which is last index of the
// array.

LEETCODE_SOLUTION_UNITTEST(1345, JumpGameIV, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {7, 6, 9, 6, 9, 6, 9, 7};
  int         expect   = 1;
  int         actual   = solution->minJumps(arr);
  LCD_EXPECT_EQ(expect, actual);
}
