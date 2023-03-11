// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Number After Digit Swaps by Parity
//
// https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/
//
// Question ID: 2231
// Difficult  : Easy
// Solve Date : 2023/03/11 14:38

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2231. Largest Number After Digit Swaps by Parity|:
//
// You are given a positive integer |num|. You may swap any two digits of |num|
// that have the same parity (i.e. both odd digits or both even digits). Return
// the largest possible value of |num| after any number of swaps.
//

LEETCODE_BEGIN_RESOLVING(2231, LargestNumberAfterDigitSwapsByParity, Solution);

class Solution {
public:
  int largestInteger(int num) {
    priority_queue<int, vector<int>, greater<int>> odd;
    priority_queue<int, vector<int>, greater<int>> even;
    int64_t                                        scale = 1;
    int                                            res   = 0;
    int                                            x     = num;
    while (x) {
      auto cur = x % 10;
      if (cur & 1) {
        odd.emplace(cur);
      } else {
        even.emplace(cur);
      }
      x /= 10;
    }
    while (num) {
      auto cur = num % 10;
      if (cur & 1) {
        res += scale * odd.top();
        odd.pop();
      } else {
        res += scale * even.top();
        even.pop();
      }
      scale *= 10;
      num /= 10;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= num <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 1234
// Output: 3412
//
// Swap the digit 3 with the digit 1, this results in the number 3214.
// Swap the digit 2 with the digit 4, this results in the number 3412.
// Note that there may be other sequences of swaps but it can be shown that 3412
// is the largest possible number. Also note that we may not swap the digit 4
// with the digit 1 since they are of different parities.

LEETCODE_SOLUTION_UNITTEST(2231, LargestNumberAfterDigitSwapsByParity,
                           example_1) {
  auto solution = MakeSolution();
  int  num      = 1234;
  int  expect   = 3412;
  int  actual   = solution->largestInteger(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 65875
// Output: 87655
//
// Swap the digit 8 with the digit 6, this results in the number 85675.
// Swap the first digit 5 with the digit 7, this results in the number 87655.
// Note that there may be other sequences of swaps but it can be shown that
// 87655 is the largest possible number.

LEETCODE_SOLUTION_UNITTEST(2231, LargestNumberAfterDigitSwapsByParity,
                           example_2) {
  auto solution = MakeSolution();
  int  num      = 65875;
  int  expect   = 87655;
  int  actual   = solution->largestInteger(num);
  LCD_EXPECT_EQ(expect, actual);
}
