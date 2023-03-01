// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Speed to Arrive on Time
//
// https://leetcode.com/problems/minimum-speed-to-arrive-on-time/
//
// Question ID: 1870
// Difficult  : Medium
// Solve Date : 2022/07/19 12:37

#include <iosfwd>
#include <cmath>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1870. Minimum Speed to Arrive on Time|:
//
// You are given a floating-point number |hour|, representing the amount of time
// you have to reach the office. To commute to the office, you must take |n|
// trains in sequential order. You are also given an integer array |dist| of
// length |n|, where |dist[i]| describes the distance (in kilometers) of the
// |iᵗʰ| train ride. Each train can only depart at an integer hour, so you may
// need to wait in between each train ride.
//
//  • For example, if the |1ˢᵗ| train ride takes |1.5| hours, you must wait for
//  an additional |0.5| hours before you can depart on the |2ⁿᵈ| train ride at
//  the 2 hour mark.
// Return the minimum positive integer speed (in kilometers per hour) that all
// the trains must travel at for you to reach the office on time, or |-1| if it
// is impossible to be on time. Tests are generated such that the answer will
// not exceed |10⁷| and |hour| will have at most two digits after the decimal
// point.
//

LEETCODE_BEGIN_RESOLVING(1870, MinimumSpeedToArriveOnTime, Solution);

class Solution {
private:
  double helper(vector<int> &d, int m) {
    double res = 0;
    for (int i = 0; i < d.size(); ++i) {
      double k = d[i];
      k /= m;
      res += i == d.size() - 1 ? k : ceil(k);
    }

    return res;
  }

public:
  int minSpeedOnTime(vector<int> &dist, double hour) {
    if (dist.size() - 1 >= hour) {

      return -1;
    }

    int lo = 1, hi = numeric_limits<int>::max() - 1;
    while (lo <= hi) {
      auto mid   = lo + (hi - lo) / 2;
      auto spend = helper(dist, mid);

      if (spend == hour) {
        return mid;
      } else if (spend > hour) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return lo;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == dist.length|
// * |1 <= n <= 10⁵|
// * |1 <= dist[i] <= 10⁵|
// * |1 <= hour <= 10⁹|
// * There will be at most two digits after the decimal point in |hour|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: dist = [1,3,2], hour = 6
// Output: 1
//
// At speed 1:
// - The first train ride takes 1/1 = 1 hour.
// - Since we are already at an integer hour, we depart immediately at the 1
// hour mark. The second train takes 3/1 = 3 hours.
// - Since we are already at an integer hour, we depart immediately at the 4
// hour mark. The third train takes 2/1 = 2 hours.
// - You will arrive at exactly the 6 hour mark.

LEETCODE_SOLUTION_UNITTEST(1870, MinimumSpeedToArriveOnTime, example_1) {
  auto        solution = MakeSolution();
  vector<int> dist     = {1, 3, 2};
  double      hour     = 6;
  int         expect   = 1;
  int         actual   = solution->minSpeedOnTime(dist, hour);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: dist = [1,3,2], hour = 2.7
// Output: 3
//
// At speed 3:
// - The first train ride takes 1/3 = 0.33333 hours.
// - Since we are not at an integer hour, we wait until the 1 hour mark to
// depart. The second train ride takes 3/3 = 1 hour.
// - Since we are already at an integer hour, we depart immediately at the 2
// hour mark. The third train takes 2/3 = 0.66667 hours.
// - You will arrive at the 2.66667 hour mark.

LEETCODE_SOLUTION_UNITTEST(1870, MinimumSpeedToArriveOnTime, example_2) {
  auto        solution = MakeSolution();
  vector<int> dist     = {1, 3, 2};
  double      hour     = 2.7;
  int         expect   = 3;
  int         actual   = solution->minSpeedOnTime(dist, hour);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: dist = [1,3,2], hour = 1.9
// Output: -1
//
// It is impossible because the earliest the third train can depart is at the 2
// hour mark.

LEETCODE_SOLUTION_UNITTEST(1870, MinimumSpeedToArriveOnTime, example_3) {
  auto        solution = MakeSolution();
  vector<int> dist     = {1, 3, 2};
  double      hour     = 1.9;
  int         expect   = -1;
  int         actual   = solution->minSpeedOnTime(dist, hour);
  LCD_EXPECT_EQ(expect, actual);
}
