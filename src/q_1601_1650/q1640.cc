// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check Array Formation Through Concatenation
//
// https://leetcode.com/problems/check-array-formation-through-concatenation/
//
// Question ID: 1640
// Difficult  : Easy
// Solve Date : 2023/09/04 11:15

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1640. Check Array Formation Through Concatenation|:
//
// You are given an array of distinct integers |arr| and an array of integer
// arrays |pieces|, where the integers in |pieces| are distinct. Your goal is to
// form |arr| by concatenating the arrays in |pieces| in any order. However, you
// are not allowed to reorder the integers in each array |pieces[i]|. Return
// |true| if it is possible to form the array |arr| from |pieces|. Otherwise,
// return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(1640, CheckArrayFormationThroughConcatenation,
                         Solution);

class Solution {
public:
  bool canFormArray(vector<int> &arr, vector<vector<int>> &pieces) {
    map<int, vector<int>> mp;
    for (auto &v : pieces) {
      mp[v[0]] = v;
    }
    vector<int> res;
    for (auto x : arr) {
      if (mp.find(x) != mp.end()) {
        res.insert(res.end(), mp[x].begin(), mp[x].end());
      }
    }
    return res == arr;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= pieces.length <= arr.length <= 100|
// * |sum(pieces[i].length) == arr.length|
// * |1 <= pieces[i].length <= arr.length|
// * |1 <= arr[i], pieces[i][j] <= 100|
// * The integers in |arr| are distinct.
// * The integers in |pieces| are distinct (i.e., If we flatten pieces in a 1D
// array, all the integers in this array are distinct).
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [15,88], pieces = [[88],[15]]
// Output: true
//
// Concatenate [15] then [88]

LEETCODE_SOLUTION_UNITTEST(1640, CheckArrayFormationThroughConcatenation,
                           example_1) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {15, 88};
  vector<vector<int>> pieces   = {{88}, {15}};
  bool                expect   = true;
  bool                actual   = solution->canFormArray(arr, pieces);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [49,18,16], pieces = [[16,18,49]]
// Output: false
//
// Even though the numbers match, we cannot reorder pieces[0].

LEETCODE_SOLUTION_UNITTEST(1640, CheckArrayFormationThroughConcatenation,
                           example_2) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {49, 18, 16};
  vector<vector<int>> pieces   = {
      {16, 18, 49}
  };
  bool expect = false;
  bool actual = solution->canFormArray(arr, pieces);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [91,4,64,78], pieces = [[78],[4,64],[91]]
// Output: true
//
// Concatenate [91] then [4,64] then [78]

LEETCODE_SOLUTION_UNITTEST(1640, CheckArrayFormationThroughConcatenation,
                           example_3) {
  auto                solution = MakeSolution();
  vector<int>         arr      = {91, 4, 64, 78};
  vector<vector<int>> pieces   = {
      {78},
      {4, 64},
      {91}
  };
  bool expect = true;
  bool actual = solution->canFormArray(arr, pieces);
  LCD_EXPECT_EQ(expect, actual);
}
