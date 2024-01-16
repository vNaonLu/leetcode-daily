// Copyright 2024 Naon Lu
//
// This file describes the solution of
//   Count Symmetric Integers
//
// https://leetcode.com/problems/count-symmetric-integers/
//
// Question ID: 2843
// Difficult  : Easy
// Solve Date : 2024/01/16 19:32

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2843.   Count Symmetric Integers|:
//
// You are given two positive integers |low| and |high|.
// An integer |x| consisting of |2 * n| digits is symmetric if the sum of the
// first |n| digits of |x| is equal to the sum of the last |n| digits of |x|.
// Numbers with an odd number of digits are never symmetric. Return the number
// of symmetric integers in the range |[low, high]|.
//
//

LEETCODE_BEGIN_RESOLVING(2843, CountSymmetricIntegers, Solution);

class Solution {
public:
  int countSymmetricIntegers(int low, int high) {
    int res = 0;
    for (int i = low; i <= high; ++i) {
      if (i >= 100 && i < 1000) {
        continue;
      }

      int         t = i;
      int         n = 0;
      vector<int> v(5);
      while (t) {
        int dg = t % 10;
        t /= 10;
        v[n++] = dg;
      }

      if ((n == 2 && v[0] == v[1]) || (n == 4 && v[0] + v[1] == v[2] + v[3])) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= low <= high <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: low = 1, high = 100
// Output: 9
//
// There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77,
// 88, and 99.

LEETCODE_SOLUTION_UNITTEST(2843, CountSymmetricIntegers, example_1) {
  auto solution = MakeSolution();
  int  low      = 1;
  int  high     = 100;
  int  expect   = 9;
  int  actual   = solution->countSymmetricIntegers(low, high);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: low = 1200, high = 1230
// Output: 4
//
// There are 4 symmetric integers between 1200 and 1230: 1203, 1212, 1221, and
// 1230.

LEETCODE_SOLUTION_UNITTEST(2843, CountSymmetricIntegers, example_2) {
  auto solution = MakeSolution();
  int  low      = 1200;
  int  high     = 1230;
  int  expect   = 4;
  int  actual   = solution->countSymmetricIntegers(low, high);
  LCD_EXPECT_EQ(expect, actual);
}
