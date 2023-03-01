// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Mutated Array Closest to Target
//
// https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/
//
// Question ID: 1300
// Difficult  : Medium
// Solve Date : 2022/07/29 18:49

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1300. Sum of Mutated Array Closest to Target|:
//
// Given an integer array |arr| and a target value |target|, return the integer
// |value| such that when we change all the integers larger than |value| in the
// given array to be equal to |value|, the sum of the array gets as close as
// possible (in absolute difference) to |target|. In case of a tie, return the
// minimum such integer. Notice that the answer is not neccesarilly a number
// from |arr|.
//

LEETCODE_BEGIN_RESOLVING(1300, SumOfMutatedArrayClosestToTarget, Solution);

class Solution {
private:
  template <typename iterator, typename type>
  auto obtainDiff(iterator beg, iterator end, type threshold, type target) {
    auto res = 0;
    while (beg != end) {
      res += *(beg) > threshold ? threshold : *beg;
      ++beg;
    }

    return abs(res - target);
  }

public:
  int findBestValue(vector<int> &arr, int target) {
    auto lo = 0;
    auto hi = *max_element(arr.begin(), arr.end());

    if (hi < lo) {

      return hi;
    }

    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (obtainDiff(arr.begin(), arr.end(), mid, target) <=
          obtainDiff(arr.begin(), arr.end(), mid + 1, target)) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    return lo;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 10⁴|
// * |1 <= arr[i], target <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [4,9,3], target = 10
// Output: 3
//
// When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal
// answer.

LEETCODE_SOLUTION_UNITTEST(1300, SumOfMutatedArrayClosestToTarget, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {4, 9, 3};
  int         target   = 10;
  int         expect   = 3;
  int         actual   = solution->findBestValue(arr, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [2,3,5], target = 10
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(1300, SumOfMutatedArrayClosestToTarget, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 3, 5};
  int         target   = 10;
  int         expect   = 5;
  int         actual   = solution->findBestValue(arr, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [60864,25176,27249,21296,20204], target = 56803
// Output: 11361
//

LEETCODE_SOLUTION_UNITTEST(1300, SumOfMutatedArrayClosestToTarget, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {60864, 25176, 27249, 21296, 20204};
  int         target   = 56803;
  int         expect   = 11361;
  int         actual   = solution->findBestValue(arr, target);
  LCD_EXPECT_EQ(expect, actual);
}
