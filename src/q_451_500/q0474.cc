// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Ones and Zeroes
//
// https://leetcode.com/problems/ones-and-zeroes/
//
// Question ID: 474
// Difficult  : Medium
// Solve Date : 2022/05/23 18:23

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |474. Ones and Zeroes|:
//
// You are given an array of binary strings |strs| and two integers |m| and |n|.
// Return the size of the largest subset of |strs| such that there are at most
// |m| |0|'s and |n| |1|'s in the subset. A set |x| is a subset of a set |y| if
// all elements of |x| are also elements of |y|.
//

LEETCODE_BEGIN_RESOLVING(474, OnesAndZeroes, Solution);

class Solution {
public:
  int findMaxForm(vector<string> &strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (auto &s : strs) {
      int zero = count(s.begin(), s.end(), '0'), one = s.size();

      for (int i = m; i >= zero; --i) {
        for (int j = n; j >= (one - zero); --j) {
          dp[i][j] = max(dp[i][j], 1 + dp[i - zero][j - (one - zero)]);
        }
      }
    }

    return dp.back().back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= strs.length <= 600|
// * |1 <= strs[i].length <= 100|
// * |strs[i]| consists only of digits |'0'| and |'1'|.
// * |1 <= m, n <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
// Output: 4
//
// The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"},
// so the answer is 4. Other valid but smaller subsets include {"0001", "1"} and
// {"10", "1", "0"}.
// {"111001"} is an invalid subset because it contains 4 1's, greater than the
// maximum of 3.

LEETCODE_SOLUTION_UNITTEST(474, OnesAndZeroes, example_1) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"10", "0001", "111001", "1", "0"};
  int            m        = 5;
  int            n        = 3;
  int            expect   = 4;
  int            actual   = solution->findMaxForm(strs, m, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: strs = ["10","0","1"], m = 1, n = 1
// Output: 2
// Explanation: The largest subset is {"0", "1"}, so the answer is 2.
//

LEETCODE_SOLUTION_UNITTEST(474, OnesAndZeroes, example_2) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"10", "0", "1"};
  int            m        = 1;
  int            n        = 1;
  int            expect   = 2;
  int            actual   = solution->findMaxForm(strs, m, n);
  LCD_EXPECT_EQ(expect, actual);
}
