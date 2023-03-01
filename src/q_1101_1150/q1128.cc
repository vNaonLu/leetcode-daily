// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Equivalent Domino Pairs
//
// https://leetcode.com/problems/number-of-equivalent-domino-pairs/
//
// Question ID: 1128
// Difficult  : Easy
// Solve Date : 2022/06/13 18:21

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1128. Number of Equivalent Domino Pairs|:
//
// Given a list of |dominoes|, |dominoes[i] = [a, b]| is equivalent to
// |dominoes[j] = [c, d]| if and only if either ( |a == c| and |b == d|), or (
// |a == d| and |b == c|) - that is, one domino can be rotated to be equal to
// another domino. Return the number of pairs |(i, j)| for which |0 <= i < j <
// dominoes.length|, and |dominoes[i]| is equivalent to |dominoes[j]|.
//

LEETCODE_BEGIN_RESOLVING(1128, NumberOfEquivalentDominoPairs, Solution);

class Solution {
public:
  int numEquivDominoPairs(vector<vector<int>> &dominoes) {
    int                      res = 0;
    map<pair<int, int>, int> mp;
    for (auto &v : dominoes) {
      auto find = mp.find({v[0], v[1]});

      if (find == mp.end()) {
        find = mp.find({v[1], v[0]});
      }

      if (find != mp.end()) {
        res += find->second;
        ++find->second;
      } else {
        mp.emplace(make_pair(v[0], v[1]), 1);
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= dominoes.length <= 4 * 10⁴|
// * |dominoes[i].length == 2|
// * |1 <= dominoes[i][j] <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1128, NumberOfEquivalentDominoPairs, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> dominoes = {
      {1, 2},
      {2, 1},
      {3, 4},
      {5, 6}
  };
  int expect = 1;
  int actual = solution->numEquivDominoPairs(dominoes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1128, NumberOfEquivalentDominoPairs, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> dominoes = {
      {1, 2},
      {1, 2},
      {1, 1},
      {1, 2},
      {2, 2}
  };
  int expect = 3;
  int actual = solution->numEquivDominoPairs(dominoes);
  LCD_EXPECT_EQ(expect, actual);
}
