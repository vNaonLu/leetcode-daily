// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Next Greater Numerically Balanced Number
//
// https://leetcode.com/problems/next-greater-numerically-balanced-number/
//
// Question ID: 2048
// Difficult  : Medium
// Solve Date : 2025/10/24 14:50

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2048. Next Greater Numerically Balanced Number|:
//
// An integer |x| is numerically balanced if for every digit |d| in the number
// |x|, there are exactly |d| occurrences of that digit in |x|. Given an integer
// |n|, return the smallest numerically balanced number strictly greater than
// |n|.
//
//

LEETCODE_BEGIN_RESOLVING(2048, NextGreaterNumericallyBalancedNumber, Solution);

class Solution {
public:
  int nextBeautifulNumber(int n) {
    static const int balanced[] = {
        1,      22,     122,    212,    221,    333,    1333,   3133,   3313,
        3331,   4444,   14444,  22333,  23233,  23323,  23332,  32233,  32323,
        32332,  33223,  33232,  33322,  41444,  44144,  44414,  44441,  55555,
        122333, 123233, 123323, 123332, 132233, 132323, 132332, 133223, 133232,
        133322, 155555, 212333, 213233, 213323, 213332, 221333, 223133, 223313,
        223331, 224444, 231233, 231323, 231332, 232133, 232313, 232331, 233123,
        233132, 233213, 233231, 233312, 233321, 242444, 244244, 244424, 244442,
        312233, 312323, 312332, 313223, 313232, 313322, 321233, 321323, 321332,
        322133, 322313, 322331, 323123, 323132, 323213, 323231, 323312, 323321,
        331223, 331232, 331322, 332123, 332132, 332213, 332231, 332312, 332321,
        333122, 333212, 333221, 422444, 424244, 424424, 424442, 442244, 442424,
        442442, 444224, 444242, 444422, 515555, 551555, 555155, 555515, 555551,
        666666, 1224444};

    int left = 0, right = size(balanced) - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (balanced[mid] <= n)
        left = mid + 1;
      else
        right = mid - 1;
    }
    return balanced[left];
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= n <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: 22
//

LEETCODE_SOLUTION_UNITTEST(2048, NextGreaterNumericallyBalancedNumber,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 22;
  int  actual   = solution->nextBeautifulNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1000
// Output: 1333
//

LEETCODE_SOLUTION_UNITTEST(2048, NextGreaterNumericallyBalancedNumber,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 1000;
  int  expect   = 1333;
  int  actual   = solution->nextBeautifulNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3000
// Output: 3133
//

LEETCODE_SOLUTION_UNITTEST(2048, NextGreaterNumericallyBalancedNumber,
                           example_3) {
  auto solution = MakeSolution();
  int  n        = 3000;
  int  expect   = 3133;
  int  actual   = solution->nextBeautifulNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}
