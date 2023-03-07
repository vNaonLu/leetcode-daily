// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Time to Complete Trips
//
// https://leetcode.com/problems/minimum-time-to-complete-trips/
//
// Question ID: 2187
// Difficult  : Medium
// Solve Date : 2023/03/07 20:26

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2187. Minimum Time to Complete Trips|:
//
// You are given an array |time| where |time[i]| denotes the time taken by the
// |iᵗʰ| bus to complete one trip. Each bus can make multiple trips
// successively; that is, the next trip can start immediately after completing
// the current trip. Also, each bus operates independently; that is, the trips
// of one bus do not influence the trips of any other bus. You are also given an
// integer |totalTrips|, which denotes the number of trips all buses should make
// in total. Return the minimum time required for all buses to complete at least
// |totalTrips| trips.
//

LEETCODE_BEGIN_RESOLVING(2187, MinimumTimeToCompleteTrips, Solution);

class Solution {
public:
  long long minimumTime(vector<int> &time, int totalTrips) {
    int64_t res = totalTrips * static_cast<int64_t>(time.front());
    int64_t lo  = 0;
    int64_t hi  = res;
    while (lo < hi) {
      auto    mid = lo + (hi - lo) / 2;
      int64_t cnt = 0;
      for (auto x : time) {
        cnt += mid / x;
      }
      if (cnt >= totalTrips) {
        res = min(res, mid);
        hi  = mid;
      } else {
        lo = mid + 1;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= time.length <= 10⁵|
// * |1 <= time[i], totalTrips <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: time = [1,2,3], totalTrips = 5
// Output: 3
//
// - At time t = 1, the number of trips completed by each bus are [1,0,0].
//  The total number of trips completed is 1 + 0 + 0 = 1.
// - At time t = 2, the number of trips completed by each bus are [2,1,0].
//  The total number of trips completed is 2 + 1 + 0 = 3.
// - At time t = 3, the number of trips completed by each bus are [3,1,1].
//  The total number of trips completed is 3 + 1 + 1 = 5.
// So the minimum time needed for all buses to complete at least 5 trips is 3.

LEETCODE_SOLUTION_UNITTEST(2187, MinimumTimeToCompleteTrips, example_1) {
  auto        solution   = MakeSolution();
  vector<int> time       = {1, 2, 3};
  int         totalTrips = 5;
  long long   expect     = 3;
  long long   actual     = solution->minimumTime(time, totalTrips);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: time = [2], totalTrips = 1
// Output: 2
//
// There is only one bus, and it will complete its first trip at t = 2.
// So the minimum time needed to complete 1 trip is 2.

LEETCODE_SOLUTION_UNITTEST(2187, MinimumTimeToCompleteTrips, example_2) {
  auto        solution   = MakeSolution();
  vector<int> time       = {2};
  int         totalTrips = 1;
  long long   expect     = 2;
  long long   actual     = solution->minimumTime(time, totalTrips);
  LCD_EXPECT_EQ(expect, actual);
}
