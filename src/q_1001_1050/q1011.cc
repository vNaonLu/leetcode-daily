// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Capacity To Ship Packages Within D Days
//
// https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
//
// Question ID: 1011
// Difficult  : Medium
// Solve Date : 2023/02/22 18:34

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1011. Capacity To Ship Packages Within D Days|:
//
// A conveyor belt has packages that must be shipped from one port to another
// within |days| days. The |iᵗʰ| package on the conveyor belt has a weight of
// |weights[i]|. Each day, we load the ship with packages on the conveyor belt
// (in the order given by |weights|). We may not load more weight than the
// maximum weight capacity of the ship. Return the least weight capacity of the
// ship that will result in all the packages on the conveyor belt being shipped
// within |days| days.
//

LEETCODE_BEGIN_RESOLVING(1011, CapacityToShipPackagesWithinDDays, Solution);

class Solution {
public:
  int shipWithinDays(vector<int> &weights, int days) {
    int lo = *max_element(weights.begin(), weights.end());
    int hi = accumulate(weights.begin(), weights.end(), 0);
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      int cur = 0, need = 1;
      for (int w : weights) {
        if (cur + w > mid) {
          cur = 0;
          need++;
        }
        cur += w;
      }
      if (need <= days) {
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
// * |1 <= days <= weights.length <= 5 * 10⁴|
// * |1 <= weights[i] <= 500|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
// Output: 15
//
// A ship capacity of 15 is the minimum to ship all the packages in 5 days like
// this: 1st day: 1, 2, 3, 4, 5 2nd day: 6, 7 3rd day: 8 4th day: 9 5th day: 10
// Note that the cargo must be shipped in the order given, so using a ship of
// capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6,
// 7), (8), (9), (10) is not allowed.

LEETCODE_SOLUTION_UNITTEST(1011, CapacityToShipPackagesWithinDDays, example_1) {
  auto        solution = MakeSolution();
  vector<int> weights  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int         days     = 5;
  int         expect   = 15;
  int         actual   = solution->shipWithinDays(weights, days);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: weights = [3,2,2,4,1,4], days = 3
// Output: 6
//
// A ship capacity of 6 is the minimum to ship all the packages in 3 days like
// this: 1st day: 3, 2 2nd day: 2, 4 3rd day: 1, 4

LEETCODE_SOLUTION_UNITTEST(1011, CapacityToShipPackagesWithinDDays, example_2) {
  auto        solution = MakeSolution();
  vector<int> weights  = {3, 2, 2, 4, 1, 4};
  int         days     = 3;
  int         expect   = 6;
  int         actual   = solution->shipWithinDays(weights, days);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: weights = [1,2,3,1,1], days = 4
// Output: 3
//
// 1st day: 1
// 2nd day: 2
// 3rd day: 3
// 4th day: 1, 1

LEETCODE_SOLUTION_UNITTEST(1011, CapacityToShipPackagesWithinDDays, example_3) {
  auto        solution = MakeSolution();
  vector<int> weights  = {1, 2, 3, 1, 1};
  int         days     = 4;
  int         expect   = 3;
  int         actual   = solution->shipWithinDays(weights, days);
  LCD_EXPECT_EQ(expect, actual);
}
