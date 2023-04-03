// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Largest Group
//
// https://leetcode.com/problems/count-largest-group/
//
// Question ID: 1399
// Difficult  : Easy
// Solve Date : 2023/04/03 16:06

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1399. Count Largest Group|:
//
// You are given an integer |n|.
// Each number from |1| to |n| is grouped according to the sum of its digits.
// Return the number of groups that have the largest size.
//
//

LEETCODE_BEGIN_RESOLVING(1399, CountLargestGroup, Solution);

class Solution {
private:
  int calcDigitSum(int x) {
    int res = 0;
    while (x > 0) {
      res += x % 10;
      x /= 10;
    }
    return res;
  }

public:
  int countLargestGroup(int n) {
    unordered_map<int, vector<int>> memo;
    int                             res        = 0;
    int                             max_length = 0;
    for (int i = 1; i <= n; ++i) {
      memo[calcDigitSum(i)].emplace_back(i);
    }
    for (auto &[sum, v] : memo) {
      if (max_length < v.size()) {
        max_length = v.size();
        res        = 1;
      } else if (max_length == v.size()) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 13
// Output: 4
//
// There are 9 groups in total, they are grouped according sum of its digits of
// numbers from 1 to 13: [1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8],
// [9]. There are 4 groups with largest size.

LEETCODE_SOLUTION_UNITTEST(1399, CountLargestGroup, example_1) {
  auto solution = MakeSolution();
  int  n        = 13;
  int  expect   = 4;
  int  actual   = solution->countLargestGroup(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: 2
//
// There are 2 groups [1], [2] of size 1.

LEETCODE_SOLUTION_UNITTEST(1399, CountLargestGroup, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 2;
  int  actual   = solution->countLargestGroup(n);
  LCD_EXPECT_EQ(expect, actual);
}
