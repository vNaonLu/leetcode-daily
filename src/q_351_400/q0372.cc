// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Super Pow
//
// https://leetcode.com/problems/super-pow/
//
// Question ID: 372
// Difficult  : Medium
// Solve Date : 2022/11/16 19:06

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |372. Super Pow|:
//
// Your task is to calculate |aᵇ| mod |1337| where |a| is a positive integer and
// |b| is an extremely large positive integer given in the form of an array.
//

LEETCODE_BEGIN_RESOLVING(372, SuperPow, Solution);

class Solution {
private:
  inline constexpr static int kMod = 1337;

  int calcPow(int a, int b) {
    auto res = (long)1;
    while (b--) {
      res = (res * a) % kMod;
    }
    return res;
  }

public:
  int superPow(int a, vector<int> &b) {
    if (b.empty()) {
      return 1;
    }
    auto bk = b.back();
    b.pop_back();
    return calcPow(superPow(a, b), 10) * calcPow(a, bk) % kMod;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= a <= 2³¹ - 1|
// * |1 <= b.length <= 2000|
// * |0 <= b[i] <= 9|
// * |b| does not contain leading zeros.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: a = 2, b = [3]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(372, SuperPow, example_1) {
  auto        solution = MakeSolution();
  int         a        = 2;
  vector<int> b        = {3};
  int         expect   = 8;
  int         actual   = solution->superPow(a, b);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: a = 2, b = [1,0]
// Output: 1024
//

LEETCODE_SOLUTION_UNITTEST(372, SuperPow, example_2) {
  auto        solution = MakeSolution();
  int         a        = 2;
  vector<int> b        = {1, 0};
  int         expect   = 1024;
  int         actual   = solution->superPow(a, b);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: a = 1, b = [4,3,3,8,5,2]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(372, SuperPow, example_3) {
  auto        solution = MakeSolution();
  int         a        = 1;
  vector<int> b        = {4, 3, 3, 8, 5, 2};
  int         expect   = 1;
  int         actual   = solution->superPow(a, b);
  LCD_EXPECT_EQ(expect, actual);
}
