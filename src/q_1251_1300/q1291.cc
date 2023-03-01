// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sequential Digits
//
// https://leetcode.com/problems/sequential-digits/
//
// Question ID: 1291
// Difficult  : Medium
// Solve Date : 2022/01/23 14:04

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1291. Sequential Digits|:
//
// An integer has sequential digits if and only if each digit in the number is
// one more than the previous digit. Return a sorted list of all the integers in
// the range |[low, high]| inclusive that have sequential digits.  
//

LEETCODE_BEGIN_RESOLVING(1291, SequentialDigits, Solution);

class Solution {
public:
  vector<int> sequentialDigits(int low, int high) {
    vector<int> res;
    int         cur = 0;
    for (int i = 1; i < 10; ++i) {
      cur = i;
      for (int j = i + 1; j < 10; ++j) {
        cur = cur * 10 + j;
        if (cur <= high and cur >= low) {
          res.emplace_back(cur);
        }
      }
    }
    sort(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |10 <= low <= high <= 10^9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: low = 100, high = 300
// Output: [123,234]
//

LEETCODE_SOLUTION_UNITTEST(1291, SequentialDigits, example_1) {
  auto        solution = MakeSolution();
  int         low      = 100;
  int         high     = 300;
  vector<int> expect   = {123, 234};
  vector<int> actual   = solution->sequentialDigits(low, high);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: low = 1000, high = 13000
// Output: [1234,2345,3456,4567,5678,6789,12345]
//

LEETCODE_SOLUTION_UNITTEST(1291, SequentialDigits, example_2) {
  auto        solution = MakeSolution();
  int         low      = 1000;
  int         high     = 13000;
  vector<int> expect   = {1234, 2345, 3456, 4567, 5678, 6789, 12345};
  vector<int> actual   = solution->sequentialDigits(low, high);
  LCD_EXPECT_EQ(expect, actual);
}
