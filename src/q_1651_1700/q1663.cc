// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest String With A Given Numeric Value
//
// https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/
//
// Question ID: 1663
// Difficult  : Medium
// Solve Date : 2022/03/22 11:51

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1663. Smallest String With A Given Numeric Value|:
//
// The numeric value of a lowercase character is defined as its position
// |(1-indexed)| in the alphabet, so the numeric value of |a| is |1|, the
// numeric value of |b| is |2|, the numeric value of |c| is |3|, and so on. The
// numeric value of a string consisting of lowercase characters is defined as
// the sum of its characters' numeric values. For example, the numeric value of
// the string |"abe"| is equal to |1 + 2 + 5 = 8|. You are given two integers
// |n| and |k|. Return the lexicographically smallest string with length equal
// to |n| and numeric value equal to |k|. Note that a string |x| is
// lexicographically smaller than string |y| if |x| comes before |y| in
// dictionary order, that is, either |x| is a prefix of |y|, or if |i| is the
// first position such that |x[i] != y[i]|, then |x[i]| comes before |y[i]| in
// alphabetic order.  
//

LEETCODE_BEGIN_RESOLVING(1663, SmallestStringWithAGivenNumericValue, Solution);

class Solution {
public:
  string getSmallestString(int n, int k) {
    string res;
    res.assign(n, 'a');

    int curr = n, idx = n - 1;

    while (curr < k) {
      res[idx] = min(25, k - curr) + 'a';
      curr += res[idx--] - 'a';
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |n <= k <= 26 * n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, k = 27
// Output: "aay"
//
// The numeric value of the string is 1 + 1 + 25 = 27, and it is the smallest
// string with such a value and length equal to 3.

LEETCODE_SOLUTION_UNITTEST(1663, SmallestStringWithAGivenNumericValue,
                           example_1) {
  auto   solution = MakeSolution();
  int    n        = 3;
  int    k        = 27;
  string expect   = "aay";
  string actual   = solution->getSmallestString(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, k = 73
// Output: "aaszz"
//

LEETCODE_SOLUTION_UNITTEST(1663, SmallestStringWithAGivenNumericValue,
                           example_2) {
  auto   solution = MakeSolution();
  int    n        = 5;
  int    k        = 73;
  string expect   = "aaszz";
  string actual   = solution->getSmallestString(n, k);
  LCD_EXPECT_EQ(expect, actual);
}
