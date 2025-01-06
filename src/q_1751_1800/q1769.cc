// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Number of Operations to Move All Balls to Each Box
//
// https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/
//
// Question ID: 1769
// Difficult  : Medium
// Solve Date : 2025/01/06 22:43

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1769. Minimum Number of Operations to Move All Balls to Each
// Box|:
//
// You have |n| boxes. You are given a binary string |boxes| of length |n|,
// where |boxes[i]| is |'0'| if the |iᵗʰ| box is empty, and |'1'| if it contains
// one ball. In one operation, you can move one ball from a box to an adjacent
// box. Box |i| is adjacent to box |j| if |abs(i - j) == 1|. Note that after
// doing so, there may be more than one ball in some boxes. Return an array
// |answer| of size |n|, where |answer[i]| is the minimum number of operations
// needed to move all the balls to the |iᵗʰ| box. Each |answer[i]| is calculated
// considering the initial state of the boxes.
//
//

LEETCODE_BEGIN_RESOLVING(1769, MinimumNumberOfOperationsToMoveAllBallsToEachBox,
                         Solution);

class Solution {
public:
  vector<int> minOperations(string boxes) {
    int         n = boxes.size();
    vector<int> left(n);
    vector<int> right(n);
    vector<int> res(n);
    int         count = boxes.front() == '1' ? 1 : 0;
    for (int i = 1; i < n; ++i) {
      left[i] = left[i - 1] + count;
      count += boxes[i] == '1' ? 1 : 0;
    }

    count = boxes.back() == '1' ? 1 : 0;

    for (int i = n - 2; i >= 0; --i) {
      right[i] = right[i + 1] + count;
      count += boxes[i] == '1' ? 1 : 0;
    }

    for (int i = 0; i < n; ++i) {
      res[i] = left[i] + right[i];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == boxes.length|
// * |1 <= n <= 2000|
// * |boxes[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: boxes = "110"
// Output: [1,1,3]
//

LEETCODE_SOLUTION_UNITTEST(1769,
                           MinimumNumberOfOperationsToMoveAllBallsToEachBox,
                           example_1) {
  auto        solution = MakeSolution();
  string      boxes    = "110";
  vector<int> expect   = {1, 1, 3};
  vector<int> actual   = solution->minOperations(boxes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: boxes = "001011"
// Output: [11,8,5,4,3,4]
//

LEETCODE_SOLUTION_UNITTEST(1769,
                           MinimumNumberOfOperationsToMoveAllBallsToEachBox,
                           example_2) {
  auto        solution = MakeSolution();
  string      boxes    = "001011";
  vector<int> expect   = {11, 8, 5, 4, 3, 4};
  vector<int> actual   = solution->minOperations(boxes);
  LCD_EXPECT_EQ(expect, actual);
}
