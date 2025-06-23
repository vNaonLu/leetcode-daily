// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count the Hidden Sequences
//
// https://leetcode.com/problems/count-the-hidden-sequences/
//
// Question ID: 2145
// Difficult  : Medium
// Solve Date : 2025/04/21 20:46

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2145. Count the Hidden Sequences|:
//
// You are given a 0-indexed array of |n| integers |differences|, which
// describes the differences between each pair of consecutive integers of a
// hidden sequence of length |(n + 1)|. More formally, call the hidden sequence
// |hidden|, then we have that |differences[i] = hidden[i + 1] - hidden[i]|. You
// are further given two integers |lower| and |upper| that describe the
// inclusive range of values |[lower, upper]| that the hidden sequence can
// contain.
//
//  • For example, given |differences = [1, -3, 4]|, |lower = 1|, |upper = 6|,
//  the hidden sequence is a sequence of length |4| whose elements are in
//  between |1| and |6| (inclusive).
//
//
//    • |[3, 4, 1, 5]| and |[4, 5, 2, 6]| are possible hidden sequences.
//
//    • |[5, 6, 3, 7]| is not possible since it contains an element greater than
//    |6|.
//
//    • |[1, 2, 3, 4]| is not possible since the differences are not correct.
//
//
// Return the number of possible hidden sequences there are. If there are no
// possible sequences, return |0|.
//
//

LEETCODE_BEGIN_RESOLVING(2145, CountTheHiddenSequences, Solution);

class Solution {
public:
  int numberOfArrays(vector<int> &differences, int lower, int upper) {
    int     x   = upper - lower;
    int64_t sum = 0;
    int64_t mx  = 0;
    int64_t mn  = 0;
    for (auto d : differences) {
      sum += d;
      mx = max(mx, sum);
      mn = min(mn, sum);
      if (mx - mn > x) {
        return 0;
      }
    }
    return x - (mx - mn) + 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == differences.length|
// * |1 <= n <= 10⁵|
// * |-10⁵ <= differences[i] <= 10⁵|
// * |-10⁵ <= lower <= upper <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: differences = [1,-3,4], lower = 1, upper = 6
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2145, CountTheHiddenSequences, example_1) {
  auto        solution    = MakeSolution();
  vector<int> differences = {1, -3, 4};
  int         lower       = 1;
  int         upper       = 6;
  int         expect      = 2;
  int         actual      = solution->numberOfArrays(differences, lower, upper);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: differences = [3,-4,5,1,-2], lower = -4, upper = 5
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2145, CountTheHiddenSequences, example_2) {
  auto        solution    = MakeSolution();
  vector<int> differences = {3, -4, 5, 1, -2};
  int         lower       = -4;
  int         upper       = 5;
  int         expect      = 4;
  int         actual      = solution->numberOfArrays(differences, lower, upper);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: differences = [4,-7,2], lower = 3, upper = 6
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2145, CountTheHiddenSequences, example_3) {
  auto        solution    = MakeSolution();
  vector<int> differences = {4, -7, 2};
  int         lower       = 3;
  int         upper       = 6;
  int         expect      = 0;
  int         actual      = solution->numberOfArrays(differences, lower, upper);
  LCD_EXPECT_EQ(expect, actual);
}
