// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Self Dividing Numbers
//
// https://leetcode.com/problems/self-dividing-numbers/
//
// Question ID: 728
// Difficult  : Easy
// Solve Date : 2022/11/01 18:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |728. Self Dividing Numbers|:
//
// A self-dividing number is a number that is divisible by every digit it
// contains.
//
//  • For example, |128| is a self-dividing number because |128 % 1 == 0|, |128
//  % 2 == 0|, and |128 % 8 == 0|.
// A self-dividing number is not allowed to contain the digit zero.
// Given two integers |left| and |right|, return a list of all the self-dividing
// numbers in the range |[left, right]|.
//

LEETCODE_BEGIN_RESOLVING(728, SelfDividingNumbers, Solution);

class Solution {
private:
  bool isSelfDividing(int x) {
    auto t = x;
    while (t != 0) {
      auto c = t % 10;
      if (c == 0 || x % c != 0) {
        return false;
      }
      t /= 10;
    }
    return true;
  }

public:
  vector<int> selfDividingNumbers(int left, int right) {
    auto res = vector<int>();
    for (int i = left; i <= right; ++i) {
      if (isSelfDividing(i)) {
        res.emplace_back(i);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= left <= right <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: left = 1, right = 22
// Output: [1,2,3,4,5,6,7,8,9,11,12,15,22]
//

LEETCODE_SOLUTION_UNITTEST(728, SelfDividingNumbers, example_1) {
  auto        solution = MakeSolution();
  int         left     = 1;
  int         right    = 22;
  vector<int> expect   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22};
  vector<int> actual   = solution->selfDividingNumbers(left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: left = 47, right = 85
// Output: [48,55,66,77]
//

LEETCODE_SOLUTION_UNITTEST(728, SelfDividingNumbers, example_2) {
  auto        solution = MakeSolution();
  int         left     = 47;
  int         right    = 85;
  vector<int> expect   = {48, 55, 66, 77};
  vector<int> actual   = solution->selfDividingNumbers(left, right);
  LCD_EXPECT_EQ(expect, actual);
}
