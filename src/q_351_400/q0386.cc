// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Lexicographical Numbers
//
// https://leetcode.com/problems/lexicographical-numbers/
//
// Question ID: 386
// Difficult  : Medium
// Solve Date : 2024/03/16 12:50

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |386. Lexicographical Numbers|:
//
// Given an integer |n|, return all the numbers in the range |[1, n]| sorted in
// lexicographical order. You must write an algorithm that runs in |O(n)| time
// and uses |O(1)| extra space.
//
//

LEETCODE_BEGIN_RESOLVING(386, LexicographicalNumbers, Solution);

class Solution {
public:
  vector<int> lexicalOrder(int n) {
    vector<int> res;
    helper(1, &res, n);
    return res;
  }

private:
  void helper(int prefix, vector<int> *out, int n) {
    if (prefix > n) {
      return;
    }

    out->emplace_back(prefix);
    helper(prefix * 10, out, n);
    if (prefix % 10 != 9) {
      helper(prefix + 1, out, n);
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 5 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 13
// Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
//

LEETCODE_SOLUTION_UNITTEST(386, LexicographicalNumbers, example_1) {
  auto        solution = MakeSolution();
  int         n        = 13;
  vector<int> expect   = {1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> actual   = solution->lexicalOrder(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(386, LexicographicalNumbers, example_2) {
  auto        solution = MakeSolution();
  int         n        = 2;
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->lexicalOrder(n);
  LCD_EXPECT_EQ(expect, actual);
}
