// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Restore The Array
//
// https://leetcode.com/problems/restore-the-array/
//
// Question ID: 1416
// Difficult  : Hard
// Solve Date : 2023/04/23 13:59

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1416. Restore The Array|:
//
// A program was supposed to print an array of integers. The program forgot to
// print whitespaces and the array is printed as a string of digits |s| and all
// we know is that all integers in the array were in the range |[1, k]| and
// there are no leading zeros in the array. Given the string |s| and the integer
// |k|, return the number of the possible arrays that can be printed as |s|
// using the mentioned program. Since the answer may be very large, return it
// modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1416, RestoreTheArray, Solution);

class Solution {
public:
  int numberOfArrays(string s, int k) {
    vector<int> dp(100001, 0);
    return dfs(&dp, s, k);
  }

private:
  int dfs(vector<int> *dp, string &s, int k, int cur = 0) {
    if (cur == s.size()) {
      return 1;
    }
    if (s[cur] == '0') {
      return 0;
    }

    if (!(*dp)[cur]) {
      int64_t num = 0;
      for (int i = 1; i + cur <= s.size(); ++i) {
        num = num * 10 + s[i + cur - 1] - '0';
        if (num > k) {
          break;
        }
        (*dp)[cur] = ((*dp)[cur] + dfs(dp, s, k, cur + i)) % kMod;
      }
    }
    return (*dp)[cur];
  }
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of only digits and does not contain leading zeros.
// * |1 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "1000", k = 10000
// Output: 1
//
// The only possible array is [1000]

LEETCODE_SOLUTION_UNITTEST(1416, RestoreTheArray, example_1) {
  auto   solution = MakeSolution();
  string s        = "1000";
  int    k        = 10000;
  int    expect   = 1;
  int    actual   = solution->numberOfArrays(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "1000", k = 10
// Output: 0
//
// There cannot be an array that was printed this way and has all integer >= 1
// and <= 10.

LEETCODE_SOLUTION_UNITTEST(1416, RestoreTheArray, example_2) {
  auto   solution = MakeSolution();
  string s        = "1000";
  int    k        = 10;
  int    expect   = 0;
  int    actual   = solution->numberOfArrays(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "1317", k = 2000
// Output: 8
//
// Possible arrays are
// [1317],[131,7],[13,17],[1,317],[13,1,7],[1,31,7],[1,3,17],[1,3,1,7]

LEETCODE_SOLUTION_UNITTEST(1416, RestoreTheArray, example_3) {
  auto   solution = MakeSolution();
  string s        = "1317";
  int    k        = 2000;
  int    expect   = 8;
  int    actual   = solution->numberOfArrays(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input:
//  "407780786171321121429620765476840275495357129574174233567552131453038760763182952432348422252546559691171161181440370120987634895458140447952079749439961325982629462531738374032416182281868731817661954890417245087359968833257550123324827240537957646002494771036413572415"
// 823924906
// Output: 427125123
//

LEETCODE_SOLUTION_UNITTEST(1416, RestoreTheArray, extra_testcase_1) {
  auto   solution = MakeSolution();
  string s =
      "407780786171321121429620765476840275495357129574174233567552131453038760"
      "763182952432348422252546559691171161181440370120987634895458140447952079"
      "749439961325982629462531738374032416182281868731817661954890417245087359"
      "968833257550123324827240537957646002494771036413572415";
  int k      = 823924906;
  int expect = 427125123;
  int actual = solution->numberOfArrays(s, k);
  LCD_EXPECT_EQ(expect, actual);
}
