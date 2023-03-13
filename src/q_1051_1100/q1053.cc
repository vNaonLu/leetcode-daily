// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Previous Permutation With One Swap
//
// https://leetcode.com/problems/previous-permutation-with-one-swap/
//
// Question ID: 1053
// Difficult  : Medium
// Solve Date : 2022/02/19 14:52

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1053. Previous Permutation With One Swap|:
//
// Given an array of positive integers |arr| (not necessarily distinct), return
// the lexicographically largest permutation that is smaller than |arr|, that
// can be made with exactly one swap. If it cannot be done, then return the same
// array. Note that a swap exchanges the positions of two numbers |arr[i]| and
// |arr[j]|  
//

LEETCODE_BEGIN_RESOLVING(1053, PreviousPermutationWithOneSwap, Solution);

class Solution {
public:
  vector<int> prevPermOpt1(vector<int> &arr) {
    for (int i = arr.size() - 2; i >= 0; --i) {
      if (arr[i] > arr[i + 1]) {
        int largest = arr[i];
        int smaller = numeric_limits<int>::min();
        int index   = 0;
        for (int j = i + 1; j < arr.size(); ++j) {
          if (arr[j] < arr[i] && arr[j] > smaller) {
            smaller = arr[j];
            index   = j;
          }
        }
        arr[i]     = smaller;
        arr[index] = largest;
        break;
      }
    }
    return arr;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁴|
// * |1 <= arr[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [3,2,1]
// Output: [3,1,2]
//
// Swapping 2 and 1.

LEETCODE_SOLUTION_UNITTEST(1053, PreviousPermutationWithOneSwap, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 2, 1};
  vector<int> expect   = {3, 1, 2};
  vector<int> actual   = solution->prevPermOpt1(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,1,5]
// Output: [1,1,5]
//
// This is already the smallest permutation.

LEETCODE_SOLUTION_UNITTEST(1053, PreviousPermutationWithOneSwap, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 1, 5};
  vector<int> expect   = {1, 1, 5};
  vector<int> actual   = solution->prevPermOpt1(arr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [1,9,4,6,7]
// Output: [1,7,4,6,9]
//
// Swapping 9 and 7.

LEETCODE_SOLUTION_UNITTEST(1053, PreviousPermutationWithOneSwap, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 9, 4, 6, 7};
  vector<int> expect   = {1, 7, 4, 6, 9};
  vector<int> actual   = solution->prevPermOpt1(arr);
  LCD_EXPECT_EQ(expect, actual);
}
