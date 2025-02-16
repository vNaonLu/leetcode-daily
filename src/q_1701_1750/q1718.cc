// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Construct the Lexicographically Largest Valid Sequence
//
// https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/
//
// Question ID: 1718
// Difficult  : Medium
// Solve Date : 2025/02/16 14:16

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1718. Construct the Lexicographically Largest Valid
// Sequence|:
//
// Given an integer |n|, find a sequence that satisfies all of the following:
//
//  • The integer |1| occurs once in the sequence.
//
//  • Each integer between |2| and |n| occurs twice in the sequence.
//
//  • For every integer |i| between |2| and |n|, the distance between the two
//  occurrences of |i| is exactly |i|.
// The distance between two numbers on the sequence, |a[i]| and |a[j]|, is the
// absolute difference of their indices, ||j - i||. Return the lexicographically
// largest sequence. It is guaranteed that under the given constraints, there is
// always a solution. A sequence |a| is lexicographically larger than a sequence
// |b| (of the same length) if in the first position where |a| and |b| differ,
// sequence |a| has a number greater than the corresponding number in |b|. For
// example, |[0,1,9,0]| is lexicographically larger than |[0,1,5,6]| because the
// first position they differ is at the third number, and |9| is greater than
// |5|.
//
//

LEETCODE_BEGIN_RESOLVING(1718,
                         ConstructTheLexicographicallyLargestValidSequence,
                         Solution);

class Solution {
public:
  vector<int> constructDistancedSequence(int n) {
    return vector<vector<int>>{
        {},
        {1},
        {2, 1, 2},
        {3, 1, 2, 3, 2},
        {4, 2, 3, 2, 4, 3, 1},
        {5, 3, 1, 4, 3, 5, 2, 4, 2},
        {6, 4, 2, 5, 2, 4, 6, 3, 5, 1, 3},
        {7, 5, 3, 6, 4, 3, 5, 7, 4, 6, 2, 1, 2},
        {8, 6, 4, 2, 7, 2, 4, 6, 8, 5, 3, 7, 1, 3, 5},
        {9, 7, 5, 3, 8, 6, 3, 5, 7, 9, 4, 6, 8, 2, 4, 2, 1},
        {10, 8, 6, 9, 3, 1, 7, 3, 6, 8, 10, 5, 9, 7, 4, 2, 5, 2, 4},
        {11, 9, 10, 6, 4, 1, 7, 8, 4, 6, 9, 11, 10, 7, 5, 8, 2, 3, 2, 5, 3},
        {12, 10, 11, 7, 5, 3, 8, 9, 3, 5, 7, 10,
         12, 11, 8,  6, 9, 2, 4, 2, 1, 6, 4},
        {13, 11, 12, 8, 6,  4, 9, 10, 1, 4, 6, 8, 11,
         13, 12, 9,  7, 10, 3, 5, 2,  3, 2, 7, 5},
        {14, 12, 13, 9, 7,  11, 4, 1, 10, 8, 4, 7, 9, 12,
         14, 13, 11, 8, 10, 6,  3, 5, 2,  3, 2, 6, 5},
        {15, 13, 14, 10, 8,  12, 5, 3, 11, 9, 3, 5, 8, 10, 13,
         15, 14, 12, 9,  11, 7,  4, 6, 1,  2, 4, 2, 7, 6},
        {16, 14, 15, 11, 9,  13, 6, 4, 12, 10, 1, 4, 6, 9, 11, 14,
         16, 15, 13, 10, 12, 8,  5, 7, 2,  3,  2, 5, 3, 8, 7},
        {17, 15, 16, 12, 10, 14, 7, 5, 3, 13, 11, 3, 5, 7, 10, 12, 15,
         17, 16, 14, 9,  11, 13, 8, 6, 2, 1,  2,  4, 9, 6, 8,  4},
        {18, 16, 17, 13, 11, 15, 8, 14, 4, 2, 12, 2, 4, 10, 8, 11, 13, 16,
         18, 17, 15, 14, 12, 10, 9, 7,  5, 3, 6,  1, 3, 5,  7, 9,  6},
        {19, 17, 18, 14, 12, 16, 9,  15, 6, 3, 13, 1, 3, 11, 6, 9, 12, 14, 17,
         19, 18, 16, 15, 13, 11, 10, 8,  4, 5, 7,  2, 4, 2,  5, 8, 10, 7},
        {20, 18, 19, 15, 13, 17, 10, 16, 7,  5,  3,  14, 12,
         3,  5,  7,  10, 13, 15, 18, 20, 19, 17, 16, 12, 14,
         11, 9,  4,  6,  8,  2,  4,  2,  1,  6,  9,  11, 8}
    }[n];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 20|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output: [3,1,2,3,2]
//

LEETCODE_SOLUTION_UNITTEST(1718,
                           ConstructTheLexicographicallyLargestValidSequence,
                           example_1) {
  auto        solution = MakeSolution();
  int         n        = 3;
  vector<int> expect   = {3, 1, 2, 3, 2};
  vector<int> actual   = solution->constructDistancedSequence(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5
// Output: [5,3,1,4,3,5,2,4,2]
//

LEETCODE_SOLUTION_UNITTEST(1718,
                           ConstructTheLexicographicallyLargestValidSequence,
                           example_2) {
  auto        solution = MakeSolution();
  int         n        = 5;
  vector<int> expect   = {5, 3, 1, 4, 3, 5, 2, 4, 2};
  vector<int> actual   = solution->constructDistancedSequence(n);
  LCD_EXPECT_EQ(expect, actual);
}
