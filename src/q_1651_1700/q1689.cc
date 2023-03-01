// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Partitioning Into Minimum Number Of Deci-Binary Numbers
//
// https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/
//
// Question ID: 1689
// Difficult  : Medium
// Solve Date : 2022/06/27 18:08

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1689. Partitioning Into Minimum Number Of Deci-Binary
// Numbers|:
//
// A decimal number is called deci-binary if each of its digits is either |0| or
// |1| without any leading zeros. For example, |101| and |1100| are deci-binary,
// while |112| and |3001| are not. Given a string |n| that represents a positive
// decimal integer, return the minimum number of positive deci-binary numbers
// needed so that they sum up to |n|.
//

LEETCODE_BEGIN_RESOLVING(1689, PartitioningIntoMinimumNumberOfDeciBinaryNumbers,
                         Solution);

class Solution {
public:
  int minPartitions(string n) { return *max_element(n.begin(), n.end()) - '0'; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n.length <= 10⁵|
// * |n| consists of only digits.
// * |n| does not contain any leading zeros and represents a positive integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = "32"
// Output: 3
//
// 10 + 11 + 11 = 32

LEETCODE_SOLUTION_UNITTEST(1689,
                           PartitioningIntoMinimumNumberOfDeciBinaryNumbers,
                           example_1) {
  auto   solution = MakeSolution();
  string n        = "32";
  int    expect   = 3;
  int    actual   = solution->minPartitions(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = "82734"
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(1689,
                           PartitioningIntoMinimumNumberOfDeciBinaryNumbers,
                           example_2) {
  auto   solution = MakeSolution();
  string n        = "82734";
  int    expect   = 8;
  int    actual   = solution->minPartitions(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = "27346209830709182346"
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(1689,
                           PartitioningIntoMinimumNumberOfDeciBinaryNumbers,
                           example_3) {
  auto   solution = MakeSolution();
  string n        = "27346209830709182346";
  int    expect   = 9;
  int    actual   = solution->minPartitions(n);
  LCD_EXPECT_EQ(expect, actual);
}
