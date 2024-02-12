// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Missing and Repeated Values
//
// https://leetcode.com/problems/find-missing-and-repeated-values/
//
// Question ID: 2965
// Difficult  : Easy
// Solve Date : 2024/02/11 12:15

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2965. Find Missing and Repeated Values|:
//
// You are given a 0-indexed 2D integer matrix |grid| of size |n * n| with
// values in the range |[1, n²]|. Each integer appears exactly once except |a|
// which appears twice and |b| which is missing. The task is to find the
// repeating and missing numbers |a| and |b|. Return a 0-indexed integer array
// |ans| of size |2| where |ans[0]| equals to |a| and |ans[1]| equals to |b|.
//
//

LEETCODE_BEGIN_RESOLVING(2965, FindMissingAndRepeatedValues, Solution);

class Solution {
public:
  vector<int> findMissingAndRepeatedValues(vector<vector<int>> &grid) {
    vector<int>   res = {-1, -1};
    map<int, int> cnt;
    for (auto &v : grid) {
      for (auto x : v) {
        ++cnt[x];

        if (cnt[x] == 2) {
          res[0] = x;
        }
      }
    }

    for (int i = 1; i <= grid.size() * grid.size(); ++i) {
      if (!cnt.count(i)) {
        res[1] = i;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n == grid.length == grid[i].length <= 50|
// * |1 <= grid[i][j] <= n * n|
// * For all |x| that |1 <= x <= n * n| there is exactly one |x| that is not
// equal to any of the grid members.
// * For all |x| that |1 <= x <= n * n| there is exactly one |x| that is equal
// to exactly two of the grid members.
// * For all |x| that |1 <= x <= n * n| except two of them there is exatly one
// pair of |i, j| that |0 <= i, j <= n - 1| and |grid[i][j] == x|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,3],[2,2]]
// Output: [2,4]
//
// Number 2 is repeated and number 4 is missing so the answer is [2,4].

LEETCODE_SOLUTION_UNITTEST(2965, FindMissingAndRepeatedValues, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 3},
      {2, 2}
  };
  vector<int> expect = {2, 4};
  vector<int> actual = solution->findMissingAndRepeatedValues(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[9,1,7],[8,9,2],[3,4,6]]
// Output: [9,5]
//
// Number 9 is repeated and number 5 is missing so the answer is [9,5].

LEETCODE_SOLUTION_UNITTEST(2965, FindMissingAndRepeatedValues, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {9, 1, 7},
      {8, 9, 2},
      {3, 4, 6}
  };
  vector<int> expect = {9, 5};
  vector<int> actual = solution->findMissingAndRepeatedValues(grid);
  LCD_EXPECT_EQ(expect, actual);
}
