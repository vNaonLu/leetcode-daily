// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Make Array Elements Zero
//
// https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/
//
// Question ID: 3495
// Difficult  : Hard
// Solve Date : 2025/09/06 21:09

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3495. Minimum Operations to Make Array Elements Zero|:
//
// You are given a 2D array |queries|, where |queries[i]| is of the form |[l,
// r]|. Each |queries[i]| defines an array of integers |nums| consisting of
// elements ranging from |l| to |r|, both inclusive. In one operation, you can:
//
//  • Select two integers |a| and |b| from the array.
//
//  • Replace them with |floor(a / 4)| and |floor(b / 4)|.
// Your task is to determine the minimum number of operations required to reduce
// all elements of the array to zero for each query. Return the sum of the
// results for all queries.
//
//

LEETCODE_BEGIN_RESOLVING(3495, MinimumOperationsToMakeArrayElementsZero,
                         Solution);

class Solution {
public:
  long long minOperations(vector<vector<int>> &queries) {
    int64_t res = 0;
    for (auto &q : queries) {
      int64_t l     = q[0];
      int64_t r     = q[1];
      auto    total = stepsum(r) - stepsum(l - 1);
      res += (total + 1) / 2;
    }
    return res;
  }

private:
  int64_t stepsum(int64_t n) {
    if (n <= 0) {
      return 0;
    }
    int64_t res = 0, base = 1, step = 1;
    while (base <= n) {
      int64_t cnt = min(n, base * 4 - 1) - base + 1;
      res += cnt * step;
      base *= 4;
      step++;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= queries.length <= 10⁵|
// * |queries[i].length == 2|
// * |queries[i] == [l, r]|
// * |1 <= l < r <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: queries = [[1,2],[2,4]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3495, MinimumOperationsToMakeArrayElementsZero,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> queries  = {
      {1, 2},
      {2, 4}
  };
  long long expect = 3;
  long long actual = solution->minOperations(queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: queries = [[2,6]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3495, MinimumOperationsToMakeArrayElementsZero,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> queries  = {
      {2, 6}
  };
  long long expect = 4;
  long long actual = solution->minOperations(queries);
  LCD_EXPECT_EQ(expect, actual);
}
