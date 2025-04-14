// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count the Number of Powerful Integers
//
// https://leetcode.com/problems/count-the-number-of-powerful-integers/
//
// Question ID: 2999
// Difficult  : Hard
// Solve Date : 2025/04/10 19:05

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2999. Count the Number of Powerful Integers|:
//
// You are given three integers |start|, |finish|, and |limit|. You are also
// given a 0-indexed string |s| representing a positive integer. A positive
// integer |x| is called powerful if it ends with |s| (in other words, |s| is a
// suffix of |x|) and each digit in |x| is at most |limit|. Return the total
// number of powerful integers in the range |[start..finish]|. A string |x| is a
// suffix of a string |y| if and only if |x| is a substring of |y| that starts
// from some index (including |0|) in |y| and extends to the index |y.length -
// 1|. For example, |25| is a suffix of |5125| whereas |512| is not.
//
//

LEETCODE_BEGIN_RESOLVING(2999, CountTheNumberOfPowerfulIntegers, Solution);

class Solution {
public:
  long long numberOfPowerfulInt(long long start, long long finish, int limit,
                                string s) {
    return helper(finish, limit, s) - helper(start - 1, limit, s);
  }

private:
  long long helper(long long val, int limit, const string &s) {
    string val_str    = to_string(val);
    int    prefix_len = val_str.length() - s.length();
    if (prefix_len < 0) {
      return 0;
    }
    vector<vector<long long>> v(prefix_len + 1, vector<long long>(2, 0));

    v[prefix_len][0] = 1;
    v[prefix_len][1] = val_str.substr(prefix_len) >= s ? 1 : 0;

    for (int i = prefix_len - 1; i >= 0; --i) {
      int cur = val_str[i] - '0';

      v[i][0] = (limit + 1) * v[i + 1][0];

      if (cur <= limit) {
        v[i][1] = (long long)cur * v[i + 1][0] + v[i + 1][1];
      } else {
        v[i][1] = (long long)(limit + 1) * v[i + 1][0];
      }
    }

    return v[0][1]; // Final count from top of chakra flow
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= start <= finish <= 10¹⁵|
// * |1 <= limit <= 9|
// * |1 <= s.length <= floor(log₁₀(finish)) + 1|
// * |s| only consists of numeric digits which are at most |limit|.
// * |s| does not have leading zeros.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: start = 1, finish = 6000, limit = 4, s = "124"
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2999, CountTheNumberOfPowerfulIntegers, example_1) {
  auto      solution = MakeSolution();
  long long start    = 1;
  long long finish   = 6000;
  int       limit    = 4;
  string    s        = "124";
  long long expect   = 5;
  long long actual   = solution->numberOfPowerfulInt(start, finish, limit, s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: start = 15, finish = 215, limit = 6, s = "10"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2999, CountTheNumberOfPowerfulIntegers, example_2) {
  auto      solution = MakeSolution();
  long long start    = 15;
  long long finish   = 215;
  int       limit    = 6;
  string    s        = "10";
  long long expect   = 2;
  long long actual   = solution->numberOfPowerfulInt(start, finish, limit, s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: start = 1000, finish = 2000, limit = 4, s = "3000"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2999, CountTheNumberOfPowerfulIntegers, example_3) {
  auto      solution = MakeSolution();
  long long start    = 1000;
  long long finish   = 2000;
  int       limit    = 4;
  string    s        = "3000";
  long long expect   = 0;
  long long actual   = solution->numberOfPowerfulInt(start, finish, limit, s);
  LCD_EXPECT_EQ(expect, actual);
}
