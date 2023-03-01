// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find K Closest Elements
//
// https://leetcode.com/problems/find-k-closest-elements/
//
// Question ID: 658
// Difficult  : Medium
// Solve Date : 2022/07/15 20:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |658. Find K Closest Elements|:
//
// Given a sorted integer array |arr|, two integers |k| and |x|, return the |k|
// closest integers to |x| in the array. The result should also be sorted in
// ascending order. An integer |a| is closer to |x| than an integer |b| if:
//
//  • ||a - x| < |b - x||, or
//
//  • ||a - x| == |b - x|| and |a < b|
//

LEETCODE_BEGIN_RESOLVING(658, FindKClosestElements, Solution);

class Solution {
public:
  vector<int> findClosestElements(vector<int> &arr, int k, int x) {
    auto lo = lower_bound(arr.begin(), arr.end(), x);
    auto hi = lo;
    while (distance(lo, hi) != k) {
      if (lo == arr.begin()) {
        ++hi;
      } else if (hi == arr.end()) {
        --lo;
      } else {
        if (x - *(lo - 1) <= *hi - x) {
          --lo;
        } else {
          ++hi;
        }
      }
    }
    return vector<int>(lo, hi);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= arr.length|
// * |1 <= arr.length <= 10⁴|
// * |arr| is sorted in ascending order.
// * |-10⁴ <= arr[i], x <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,2,3,4,5], k = 4, x = 3
// Output: [1,2,3,4]
//

LEETCODE_SOLUTION_UNITTEST(658, FindKClosestElements, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 4, 5};
  int         k        = 4;
  int         x        = 3;
  vector<int> expect   = {1, 2, 3, 4};
  vector<int> actual   = solution->findClosestElements(arr, k, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,2,3,4,5], k = 4, x = -1
// Output: [1,2,3,4]
//

LEETCODE_SOLUTION_UNITTEST(658, FindKClosestElements, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 2, 3, 4, 5};
  int         k        = 4;
  int         x        = -1;
  vector<int> expect   = {1, 2, 3, 4};
  vector<int> actual   = solution->findClosestElements(arr, k, x);
  LCD_EXPECT_EQ(expect, actual);
}
