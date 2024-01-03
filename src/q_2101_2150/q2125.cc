// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Number of Laser Beams in a Bank
//
// https://leetcode.com/problems/number-of-laser-beams-in-a-bank/
//
// Question ID: 2125
// Difficult  : Medium
// Solve Date : 2024/01/03 20:42

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2125. Number of Laser Beams in a Bank|:
//
// Anti-theft security devices are activated inside a bank. You are given a
// 0-indexed binary string array |bank| representing the floor plan of the bank,
// which is an |m x n| 2D matrix. |bank[i]| represents the |iᵗʰ| row, consisting
// of |'0'|s and |'1'|s. |'0'| means the cell is empty, while |'1'| means the
// cell has a security device. There is one laser beam between any two security
// devices if both conditions are met:
//
//  • The two devices are located on two different rows: |r₁| and |r₂|, where
//  |r₁ < r₂|.
//
//  • For each row |i| where |r₁ < i < r₂|, there are no security devices in the
//  |iᵗʰ| row.
// Laser beams are independent, i.e., one beam does not interfere nor join with
// another. Return the total number of laser beams in the bank.
//
//

LEETCODE_BEGIN_RESOLVING(2125, NumberOfLaserBeamsInABank, Solution);

class Solution {
public:
  int numberOfBeams(vector<string> &bank) {
    int n = bank.size();
    if (n < 2) {
      return 0;
    }
    vector<int> tmp;

    for (int i = 0; i < n; ++i) {
      int sum = 0;
      for (auto x : bank[i]) {
        if (x == '1') {
          ++sum;
        }
      }
      if (sum > 0) {
        tmp.emplace_back(sum);
      }
    }
    if (tmp.size() < 2) {
      return 0;
    }
    int res = 0;
    for (int i = 0; i < tmp.size() - 1; ++i) {
      res += tmp[i] * tmp[i + 1];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == bank.length|
// * |n == bank[i].length|
// * |1 <= m, n <= 500|
// * |bank[i][j]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: bank = ["011001","000000","010100","001000"]
// Output: 8
//
// Between each of the following device pairs, there is one beam. In total,
// there are 8 beams:
//  * bank[0][1] -- bank[2][1]
//  * bank[0][1] -- bank[2][3]
//  * bank[0][2] -- bank[2][1]
//  * bank[0][2] -- bank[2][3]
//  * bank[0][5] -- bank[2][1]
//  * bank[0][5] -- bank[2][3]
//  * bank[2][1] -- bank[3][2]
//  * bank[2][3] -- bank[3][2]
// Note that there is no beam between any device on the 0ᵗʰ row with any on the
// 3ʳᵈ row. This is because the 2ⁿᵈ row contains security devices, which breaks
// the second condition.

LEETCODE_SOLUTION_UNITTEST(2125, NumberOfLaserBeamsInABank, example_1) {
  auto           solution = MakeSolution();
  vector<string> bank     = {"011001", "000000", "010100", "001000"};
  int            expect   = 8;
  int            actual   = solution->numberOfBeams(bank);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: bank = ["000","111","000"]
// Output: 0
//
// There does not exist two devices located on two different rows.

LEETCODE_SOLUTION_UNITTEST(2125, NumberOfLaserBeamsInABank, example_2) {
  auto           solution = MakeSolution();
  vector<string> bank     = {"000", "111", "000"};
  int            expect   = 0;
  int            actual   = solution->numberOfBeams(bank);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: ["0","0"]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2125, NumberOfLaserBeamsInABank, extra_testcase_1) {
  auto           solution = MakeSolution();
  vector<string> bank     = {"0", "0"};
  int            expect   = 0;
  int            actual   = solution->numberOfBeams(bank);
  LCD_EXPECT_EQ(expect, actual);
}
