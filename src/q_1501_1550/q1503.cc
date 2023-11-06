// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Last Moment Before All Ants Fall Out of a Plank
//
// https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/
//
// Question ID: 1503
// Difficult  : Medium
// Solve Date : 2023/11/04 22:15

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1503. Last Moment Before All Ants Fall Out of a Plank|:
//
// We have a wooden plank of the length |n| units. Some ants are walking on the
// plank, each ant moves with a speed of 1 unit per second. Some of the ants
// move to the left, the other move to the right. When two ants moving in two
// different directions meet at some point, they change their directions and
// continue moving again. Assume changing directions does not take any
// additional time. When an ant reaches one end of the plank at a time |t|, it
// falls out of the plank immediately. Given an integer |n| and two integer
// arrays |left| and |right|, the positions of the ants moving to the left and
// the right, return the moment when the last ant(s) fall out of the plank.
//
//

LEETCODE_BEGIN_RESOLVING(1503, LastMomentBeforeAllAntsFallOutOfAPlank,
                         Solution);

class Solution {
public:
  int getLastMoment(int n, vector<int> &left, vector<int> &right) {
    int l = right.empty() ? 0 : n - *min_element(right.begin(), right.end());
    int r = left.empty() ? 0 : *max_element(left.begin(), left.end());
    return max(l, r);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁴|
// * |0 <= left.length <= n + 1|
// * |0 <= left[i] <= n|
// * |0 <= right.length <= n + 1|
// * |0 <= right[i] <= n|
// * |1 <= left.length + right.length <= n + 1|
// * All values of |left| and |right| are unique, and each value can appear only
// in one of the two arrays.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, left = [4,3], right = [0,1]
// Output: 4
//
// In the image above:
// -The ant at index 0 is named A and going to the right.
// -The ant at index 1 is named B and going to the right.
// -The ant at index 3 is named C and going to the left.
// -The ant at index 4 is named D and going to the left.
// The last moment when an ant was on the plank is t = 4 seconds. After that, it
// falls immediately out of the plank. (i.e., We can say that at t
// = 4.0000000001, there are no ants on the plank).

LEETCODE_SOLUTION_UNITTEST(1503, LastMomentBeforeAllAntsFallOutOfAPlank,
                           example_1) {
  auto        solution = MakeSolution();
  int         n        = 4;
  vector<int> left     = {4, 3};
  vector<int> right    = {0, 1};
  int         expect   = 4;
  int         actual   = solution->getLastMoment(n, left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7, left = [], right = [0,1,2,3,4,5,6,7]
// Output: 7
//
// All ants are going to the right, the ant at index 0 needs 7 seconds to fall.

LEETCODE_SOLUTION_UNITTEST(1503, LastMomentBeforeAllAntsFallOutOfAPlank,
                           example_2) {
  auto        solution = MakeSolution();
  int         n        = 7;
  vector<int> left     = {};
  vector<int> right    = {0, 1, 2, 3, 4, 5, 6, 7};
  int         expect   = 7;
  int         actual   = solution->getLastMoment(n, left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 7, left = [0,1,2,3,4,5,6,7], right = []
// Output: 7
//
// All ants are going to the left, the ant at index 7 needs 7 seconds to fall.

LEETCODE_SOLUTION_UNITTEST(1503, LastMomentBeforeAllAntsFallOutOfAPlank,
                           example_3) {
  auto        solution = MakeSolution();
  int         n        = 7;
  vector<int> left     = {0, 1, 2, 3, 4, 5, 6, 7};
  vector<int> right    = {};
  int         expect   = 7;
  int         actual   = solution->getLastMoment(n, left, right);
  LCD_EXPECT_EQ(expect, actual);
}
