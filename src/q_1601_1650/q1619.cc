// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Mean of Array After Removing Some Elements
//
// https://leetcode.com/problems/mean-of-array-after-removing-some-elements/
//
// Question ID: 1619
// Difficult  : Easy
// Solve Date : 2023/09/01 20:59

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1619. Mean of Array After Removing Some Elements|:
//
// Given an integer array |arr|, return the mean of the remaining integers after
// removing the smallest |5%| and the largest |5%| of the elements. Answers
// within |10⁻⁵| of the actual answer will be considered accepted.
//
//

LEETCODE_BEGIN_RESOLVING(1619, MeanOfArrayAfterRemovingSomeElements, Solution);

class Solution {
public:
  double trimMean(vector<int> &arr) {
    auto first = arr.begin() + (arr.size() / 20);
    auto last  = arr.end() - (arr.size() / 20);
    nth_element(arr.begin(), first, arr.end());
    nth_element(first, last, arr.end());
    return accumulate(first, last, 0.0) / distance(first, last);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |20 <= arr.length <= 1000|
// * |arr.length| is a multiple of |20|.
// * |0 <= arr[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3]
// Output: 2.00000
//
// After erasing the minimum and the maximum values of this array, all elements
// are equal to 2, so the mean is 2.

LEETCODE_SOLUTION_UNITTEST(1619, MeanOfArrayAfterRemovingSomeElements,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                          2, 2, 2, 2, 2, 2, 2, 2, 2, 3};
  double      expect   = 2.00000;
  double      actual   = solution->trimMean(arr);
  EXPECT_NEAR(expect, actual, 1e-5);
}

// [Example #2]
//  Input: arr = [6,2,7,5,1,2,0,3,10,2,5,0,5,5,0,8,7,6,8,0]
// Output: 4.00000
//

LEETCODE_SOLUTION_UNITTEST(1619, MeanOfArrayAfterRemovingSomeElements,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {6, 2, 7, 5, 1, 2, 0, 3, 10, 2,
                          5, 0, 5, 5, 0, 8, 7, 6, 8,  0};
  double      expect   = 4.00000;
  double      actual   = solution->trimMean(arr);
  EXPECT_NEAR(expect, actual, 1e-5);
}

// [Example #3]
//  Input: arr =
//  [6,0,7,0,7,5,7,8,3,4,0,7,8,1,6,8,1,1,2,4,8,1,9,5,4,3,8,5,10,8,6,6,1,0,6,10,8,2,3,4]
// Output: 4.77778
//

LEETCODE_SOLUTION_UNITTEST(1619, MeanOfArrayAfterRemovingSomeElements,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {6,  0, 7, 0, 7, 5, 7, 8,  3, 4, 0, 7, 8, 1,
                          6,  8, 1, 1, 2, 4, 8, 1,  9, 5, 4, 3, 8, 5,
                          10, 8, 6, 6, 1, 0, 6, 10, 8, 2, 3, 4};
  double      expect   = 4.77778;
  double      actual   = solution->trimMean(arr);
  EXPECT_NEAR(expect, actual, 1e-5);
}
