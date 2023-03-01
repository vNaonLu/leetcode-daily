// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Recent Calls
//
// https://leetcode.com/problems/number-of-recent-calls/
//
// Question ID: 933
// Difficult  : Easy
// Solve Date : 2022/10/06 10:20

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |933. Number of Recent Calls|:
//
// You have a |RecentCounter| class which counts the number of recent requests
// within a certain time frame. Implement the |RecentCounter| class:
//
//  • |RecentCounter()| Initializes the counter with zero recent requests.
//
//  • |int ping(int t)| Adds a new request at time |t|, where |t| represents
//  some time in milliseconds, and returns the number of requests that has
//  happened in the past |3000| milliseconds (including the new request).
//  Specifically, return the number of requests that have happened in the
//  inclusive range |[t - 3000, t]|.
// It is guaranteed that every call to |ping| uses a strictly larger value of
// |t| than the previous call.
//

LEETCODE_BEGIN_RESOLVING(933, NumberOfRecentCalls, RecentCounter);

class RecentCounter {
private:
  vector<int> reqs;

public:
  RecentCounter() {}

  int ping(int t) {
    auto pos = upper_bound(reqs.begin(), reqs.end(), t);
    reqs.insert(pos, t);
    auto end = upper_bound(reqs.begin(), reqs.end(), t);
    auto fst = upper_bound(reqs.begin(), end, t - 3001);
    return distance(fst, end);
  }
};

LEETCODE_END_RESOLVING(RecentCounter);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= t <= 10⁹|
// * Each test case will call |ping| with strictly increasing values of |t|.
// * At most |10⁴| calls will be made to |ping|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["RecentCounter", "ping", "ping", "ping", "ping"]
// [[], [1], [100], [3001], [3002]]
// Output: [null, 1, 2, 3, 3]
//
// RecentCounter recentCounter = new RecentCounter();
// recentCounter.ping(1); // requests = [1], range is [-2999,1], return 1
// recentCounter.ping(100); // requests = [1, 100], range is [-2900,100], return
// 2 recentCounter.ping(3001); // requests = [1, 100, 3001], range is [1,3001],
// return 3 recentCounter.ping(3002); // requests = [1, 100, 3001, 3002], range
// is [2,3002], return 3

LEETCODE_SOLUTION_UNITTEST(933, NumberOfRecentCalls, example_1) {
  auto recent_counter = MakeRecentCounter();
  int  s1_t           = 1;
  int  s1_expect      = 1;
  int  s1_actual      = recent_counter->ping(s1_t);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_t      = 100;
  int s2_expect = 2;
  int s2_actual = recent_counter->ping(s2_t);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_t      = 3001;
  int s3_expect = 3;
  int s3_actual = recent_counter->ping(s3_t);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_t      = 3002;
  int s4_expect = 3;
  int s4_actual = recent_counter->ping(s4_t);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
}
