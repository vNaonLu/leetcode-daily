// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Number of People Aware of a Secret
//
// https://leetcode.com/problems/number-of-people-aware-of-a-secret/
//
// Question ID: 2327
// Difficult  : Medium
// Solve Date : 2025/09/09 19:03

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2327. Number of People Aware of a Secret|:
//
// On day |1|, one person discovers a secret.
// You are given an integer |delay|, which means that each person will share the
// secret with a new person every day, starting from |delay| days after
// discovering the secret. You are also given an integer |forget|, which means
// that each person will forget the secret |forget| days after discovering it. A
// person cannot share the secret on the same day they forgot it, or on any day
// afterwards. Given an integer |n|, return the number of people who know the
// secret at the end of day |n|. Since the answer may be very large, return it
// modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(2327, NumberOfPeopleAwareOfASecret, Solution);

class Solution {
public:
  int peopleAwareOfSecret(int n, int delay, int forget) {
    vector<int64_t> dp(n + 1);
    dp[1]         = 1;
    int64_t share = 0;
    for (int t = 2; t <= n; ++t) {
      if (t > delay) {
        share = (kMod + share + dp[t - delay]) % kMod;
      }
      if (t > forget) {
        share = (kMod + share - dp[t - forget]) % kMod;
      }
      dp[t] = share;
    }

    int64_t know = 0;
    for (int i = n - forget + 1; i <= n; ++i) {
      know = (know + dp[i]) % kMod;
    }
    return know;
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 1000|
// * |1 <= delay < forget <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6, delay = 2, forget = 4
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2327, NumberOfPeopleAwareOfASecret, example_1) {
  auto solution = MakeSolution();
  int  n        = 6;
  int  delay    = 2;
  int  forget   = 4;
  int  expect   = 5;
  int  actual   = solution->peopleAwareOfSecret(n, delay, forget);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, delay = 1, forget = 3
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(2327, NumberOfPeopleAwareOfASecret, example_2) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  delay    = 1;
  int  forget   = 3;
  int  expect   = 6;
  int  actual   = solution->peopleAwareOfSecret(n, delay, forget);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 289
// 7
// 23
// Output: 790409951
//

LEETCODE_SOLUTION_UNITTEST(2327, NumberOfPeopleAwareOfASecret,
                           extra_testcase_1) {
  auto solution = MakeSolution();
  int  n        = 289;
  int  delay    = 7;
  int  forget   = 23;
  int  expect   = 790409951;
  int  actual   = solution->peopleAwareOfSecret(n, delay, forget);
  LCD_EXPECT_EQ(expect, actual);
}
