// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Count of Good Integers
//
// https://leetcode.com/problems/find-the-count-of-good-integers/
//
// Question ID: 3272
// Difficult  : Hard
// Solve Date : 2025/04/12 13:25

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3272. Find the Count of Good Integers|:
//
// You are given two positive integers |n| and |k|.
// An integer |x| is called k-palindromic if:
//
//  • |x| is a palindrome.
//
//  • |x| is divisible by |k|.
// An integer is called good if its digits can be rearranged to form a
// k-palindromic integer. For example, for |k = 2|, 2020 can be rearranged to
// form the k-palindromic integer 2002, whereas 1010 cannot be rearranged to
// form a k-palindromic integer. Return the count of good integers containing
// |n| digits. Note that any integer must not have leading zeros, neither before
// nor after rearrangement. For example, 1010 cannot be rearranged to form 101.
//
//

LEETCODE_BEGIN_RESOLVING(3272, FindTheCountOfGoodIntegers, Solution);

#define ll long long
class Solution {
  ll vectorToNumber(const vector<int> &nums) {
    ll res = 0;
    for (int dig : nums)
      res = res * 10 + dig;
    return res;
  }

  ll fact(int total, ll f = 1) {
    for (int i = 2; i <= total; i++)
      f *= i;
    return f;
  }

  ll totalPermutations(map<int, int> &mpp, int total) {
    ll totalDig = fact(total);
    for (auto &palinVal : mpp)
      totalDig /= fact(palinVal.second);
    return totalDig;
  }

  ll permsWithZero(map<int, int> mpp, int total) {
    return mpp[0] == 0 ? 0 : ([&]() {
      mpp[0]--;
      ll tot = fact(total - 1);
      for (auto &palinVal : mpp)
        tot /= fact(palinVal.second);
      return tot;
    }());
  }

public:
  ll                 res = 0;
  set<map<int, int>> visited;

  void genPal(vector<int> &palin, int left, int right, int divisor, int total) {
    if (left > right) {
      ll palinVal = vectorToNumber(palin);
      if (palinVal % divisor == 0) {
        map<int, int> digMpp;
        for (ll result = palinVal; result; result /= 10)
          digMpp[result % 10]++;
        if (!visited.count(digMpp)) {
          res +=
              totalPermutations(digMpp, total) - permsWithZero(digMpp, total);
          visited.insert(digMpp);
        }
      }
      return;
    }
    for (int dig = (left == 0 ? 1 : 0); dig <= 9; dig++) {
      palin[left] = palin[right] = dig;
      genPal(palin, left + 1, right - 1, divisor, total);
    }
  }

  ll countGoodIntegers(int total, int divisor) {
    vector<int> palin(total);
    genPal(palin, 0, total - 1, divisor, total);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10|
// * |1 <= k <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, k = 5
// Output: 27
//

LEETCODE_SOLUTION_UNITTEST(3272, FindTheCountOfGoodIntegers, example_1) {
  auto      solution = MakeSolution();
  int       n        = 3;
  int       k        = 5;
  long long expect   = 27;
  long long actual   = solution->countGoodIntegers(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, k = 4
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3272, FindTheCountOfGoodIntegers, example_2) {
  auto      solution = MakeSolution();
  int       n        = 1;
  int       k        = 4;
  long long expect   = 2;
  long long actual   = solution->countGoodIntegers(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 5, k = 6
// Output: 2468
//

LEETCODE_SOLUTION_UNITTEST(3272, FindTheCountOfGoodIntegers, example_3) {
  auto      solution = MakeSolution();
  int       n        = 5;
  int       k        = 6;
  long long expect   = 2468;
  long long actual   = solution->countGoodIntegers(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
