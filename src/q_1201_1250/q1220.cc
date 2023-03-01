// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Vowels Permutation
//
// https://leetcode.com/problems/count-vowels-permutation/
//
// Question ID: 1220
// Difficult  : Hard
// Solve Date : 2022/08/07 13:07

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1220. Count Vowels Permutation|:
//
// Given an integer |n|, your task is to count how many strings of length |n|
// can be formed under the following rules:
//
//  • Each character is a lower case vowel( |'a'|, |'e'|, |'i'|, |'o'|, |'u'|)
//
//  • Each vowel |'a'| may only be followed by an |'e'|.
//
//  • Each vowel |'e'| may only be followed by an |'a'|or an |'i'|.
//
//  • Each vowel |'i'| may not be followed by another |'i'|.
//
//  • Each vowel |'o'| may only be followed by an |'i'| or a |'u'|.
//
//  • Each vowel |'u'| may only be followed by an |'a'.|
// Since the answermay be too large,return it modulo |10^9 + 7.|
//

LEETCODE_BEGIN_RESOLVING(1220, CountVowelsPermutation, Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;
  int solve(int prev, int count, int n, vector<vector<int>> &dp) {
    if (count == n) {
      return 1;
    }

    if (dp[count][prev] == -1) {
      int res = 0;
      for (int i = 1; i <= 5; ++i) {
        if (prev == 1 && i == 2) {
          res = (res + solve(i, count + 1, n, dp)) % kMod;
        } else if (prev == 2 && (i == 1 || i == 3)) {
          res = (res + solve(i, count + 1, n, dp)) % kMod;
        } else if (prev == 3 && i != 3) {
          res = (res + solve(i, count + 1, n, dp)) % kMod;
        } else if (prev == 4 && (i == 3 || i == 5)) {
          res = (res + solve(i, count + 1, n, dp)) % kMod;
        } else if (prev == 5 && (i == 1)) {
          res = (res + solve(i, count + 1, n, dp)) % kMod;
        }
      }
      dp[count][prev] = res;
    }

    return dp[count][prev] %= kMod;
  }

public:
  int countVowelPermutation(int n) {
    auto res = 0;
    auto dp  = vector<vector<int>>(n + 1, vector<int>(6, -1));
    for (int i = 1; i <= 5; ++i) {
      res += solve(i, 1, n, dp);
      res %= kMod;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2 * 10^4|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: 5
//
// All possible strings are: "a", "e", "i" , "o" and "u".

LEETCODE_SOLUTION_UNITTEST(1220, CountVowelsPermutation, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 5;
  int  actual   = solution->countVowelPermutation(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: 10
//
// All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi",
// "ou" and "ua".

LEETCODE_SOLUTION_UNITTEST(1220, CountVowelsPermutation, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 10;
  int  actual   = solution->countVowelPermutation(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 5
// Output: 68
//

LEETCODE_SOLUTION_UNITTEST(1220, CountVowelsPermutation, example_3) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 68;
  int  actual   = solution->countVowelPermutation(n);
  LCD_EXPECT_EQ(expect, actual);
}
