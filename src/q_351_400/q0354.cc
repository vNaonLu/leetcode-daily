// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Russian Doll Envelopes
//
// https://leetcode.com/problems/russian-doll-envelopes/
//
// Question ID: 354
// Difficult  : Hard
// Solve Date : 2022/05/25 18:13

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |354. Russian Doll Envelopes|:
//
// You are given a 2D array of integers |envelopes| where |envelopes[i] = [wᵢ,
// hᵢ]| represents the width and the height of an envelope. One envelope can fit
// into another if and only if both the width and height of one envelope are
// greater than the other envelope's width and height. Return the maximum number
// of envelopes you can Russian doll (i.e., put one inside the other). Note: You
// cannot rotate an envelope.
//

LEETCODE_BEGIN_RESOLVING(354, RussianDollEnvelopes, Solution);

class Solution {
public:
  int maxEnvelopes(vector<vector<int>> &envelopes) {
    sort(envelopes.begin(), envelopes.end(), [](auto &a, auto &b) {
      return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
    });

    vector<int> res;
    for (auto &v : envelopes) {
      auto e = v[1];

      auto f = lower_bound(res.begin(), res.end(), e);
      if (f == res.end()) {
        res.emplace_back(e);
      } else {
        *f = e;
      }
    }

    return res.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= envelopes.length <= 10⁵|
// * |envelopes[i].length == 2|
// * |1 <= wᵢ, hᵢ <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
// Output: 3
//
// The maximum number of envelopes you can Russian doll is |3| ([2,3] => [5,4]
// => [6,7]).

LEETCODE_SOLUTION_UNITTEST(354, RussianDollEnvelopes, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> envelopes = {
      {5, 4},
      {6, 4},
      {6, 7},
      {2, 3}
  };
  int expect = 3;
  int actual = solution->maxEnvelopes(envelopes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: envelopes = [[1,1],[1,1],[1,1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(354, RussianDollEnvelopes, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> envelopes = {
      {1, 1},
      {1, 1},
      {1, 1}
  };
  int expect = 1;
  int actual = solution->maxEnvelopes(envelopes);
  LCD_EXPECT_EQ(expect, actual);
}
