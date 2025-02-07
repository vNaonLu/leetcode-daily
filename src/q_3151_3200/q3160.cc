// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Number of Distinct Colors Among the Balls
//
// https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/
//
// Question ID: 3160
// Difficult  : Medium
// Solve Date : 2025/02/07 21:30

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3160. Find the Number of Distinct Colors Among the Balls|:
//
// You are given an integer |limit| and a 2D array |queries| of size |n x 2|.
// There are |limit + 1| balls with distinct labels in the range |[0, limit]|.
// Initially, all balls are uncolored. For every query in |queries| that is of
// the form |[x, y]|, you mark ball |x| with the color |y|. After each query,
// you need to find the number of distinct colors among the balls. Return an
// array |result| of length |n|, where |result[i]| denotes the number of
// distinct colors after |iᵗʰ| query. Note that when answering a query, lack of
// a color will not be considered as a color.
//
//

LEETCODE_BEGIN_RESOLVING(3160, FindTheNumberOfDistinctColorsAmongTheBalls,
                         Solution);

class Solution {
public:
  vector<int> queryResults(int limit, vector<vector<int>> &queries) {
    int                     n = queries.size();
    vector<int>             res(n);
    unordered_map<int, int> cmp;
    unordered_map<int, int> bmp;
    for (int i = 0; i < n; ++i) {
      int b = queries[i][0];
      int c = queries[i][1];
      if (bmp.count(b)) {
        int prev = bmp[b];
        if (--cmp[prev] == 0) {
          cmp.erase(prev);
        }
      }

      bmp[b] = c;
      ++cmp[c];
      res[i] = cmp.size();
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= limit <= 10⁹|
// * |1 <= n == queries.length <= 10⁵|
// * |queries[i].length == 2|
// * |0 <= queries[i][0] <= limit|
// * |1 <= queries[i][1] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
// Output: [1,2,2,3]
//

LEETCODE_SOLUTION_UNITTEST(3160, FindTheNumberOfDistinctColorsAmongTheBalls,
                           example_1) {
  auto                solution = MakeSolution();
  int                 limit    = 4;
  vector<vector<int>> queries  = {
      {1, 4},
      {2, 5},
      {1, 3},
      {3, 4}
  };
  vector<int> expect = {1, 2, 2, 3};
  vector<int> actual = solution->queryResults(limit, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: limit = 4, queries = [[0,1],[1,2],[2,2],[3,4],[4,5]]
// Output: [1,2,2,3,4]
//

LEETCODE_SOLUTION_UNITTEST(3160, FindTheNumberOfDistinctColorsAmongTheBalls,
                           example_2) {
  auto                solution = MakeSolution();
  int                 limit    = 4;
  vector<vector<int>> queries  = {
      {0, 1},
      {1, 2},
      {2, 2},
      {3, 4},
      {4, 5}
  };
  vector<int> expect = {1, 2, 2, 3, 4};
  vector<int> actual = solution->queryResults(limit, queries);
  LCD_EXPECT_EQ(expect, actual);
}
