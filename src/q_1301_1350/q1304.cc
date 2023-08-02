// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find N Unique Integers Sum up to Zero
//
// https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/
//
// Question ID: 1304
// Difficult  : Easy
// Solve Date : 2023/08/02 11:25

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1304. Find N Unique Integers Sum up to Zero|:
//
// Given an integer |n|, return any array containing |n| unique integers such
// that they add up to |0|.
//
//

LEETCODE_BEGIN_RESOLVING(1304, FindNUniqueIntegersSumUpToZero, Solution);

class Solution {
public:
  vector<int> sumZero(int n) {
    vector<int> res;

    if (n & 1) {
      res.emplace_back(0);
    }

    n /= 2;
    for (int i = 0; i < n; ++i) {
      res.emplace_back(i + 1);
      res.emplace_back(-1 * (i + 1));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
///////////////////////////////////////////////////////////////////////////////

namespace {
int Accumulate(const vector<int> &v) {
  return accumulate(v.begin(), v.end(), 0);
}
} // namespace

// [Example #1]
//  Input: n = 5
// Output: [-7,-1,1,3,4]
//
// These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].

LEETCODE_SOLUTION_UNITTEST(1304, FindNUniqueIntegersSumUpToZero, example_1) {
  auto        solution = MakeSolution();
  int         n        = 5;
  vector<int> actual   = solution->sumZero(n);
  LCD_EXPECT_EQ(0, Accumulate(actual));
}

// [Example #2]
//  Input: n = 3
// Output: [-1,0,1]
//

LEETCODE_SOLUTION_UNITTEST(1304, FindNUniqueIntegersSumUpToZero, example_2) {
  auto        solution = MakeSolution();
  int         n        = 3;
  vector<int> actual   = solution->sumZero(n);
  LCD_EXPECT_EQ(0, Accumulate(actual));
}

// [Example #3]
//  Input: n = 1
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(1304, FindNUniqueIntegersSumUpToZero, example_3) {
  auto        solution = MakeSolution();
  int         n        = 1;
  vector<int> actual   = solution->sumZero(n);
  LCD_EXPECT_EQ(0, Accumulate(actual));
}
