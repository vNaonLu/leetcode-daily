// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Running Time of N Computers
//
// https://leetcode.com/problems/maximum-running-time-of-n-computers/
//
// Question ID: 2141
// Difficult  : Hard
// Solve Date : 2023/07/27 10:49

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2141. Maximum Running Time of N Computers|:
//
// You have |n| computers. You are given the integer |n| and a 0-indexed integer
// array |batteries| where the |iᵗʰ| battery can run a computer for
// |batteries[i]| minutes. You are interested in running all |n| computers
// simultaneously using the given batteries. Initially, you can insert at most
// one battery into each computer. After that and at any integer time moment,
// you can remove a battery from a computer and insert another battery any
// number of times. The inserted battery can be a totally new battery or a
// battery from another computer. You may assume that the removing and inserting
// processes take no time. Note that the batteries cannot be recharged. Return
// the maximum number of minutes you can run all the |n| computers
// simultaneously.
//
//

LEETCODE_BEGIN_RESOLVING(2141, MaximumRunningTimeOfNComputers, Solution);

class Solution {
public:
  long long maxRunTime(int n, vector<int> &batteries) {
    int64_t lo = 1;
    int64_t hi = accumulate(batteries.begin(), batteries.end(), 0ll) / n;

    sort(batteries.begin(), batteries.end());
    while (lo < hi) {
      int64_t mid = lo + (hi - lo + 1) / 2;

      if (possible(n, batteries, mid)) {
        lo = mid;
      } else {
        hi = mid - 1;
      }
    }

    return lo;
  }

private:
  bool possible(int n, vector<int> &batteries, int64_t hrs) {
    int64_t s = 0;
    for (int i = 0; i < batteries.size(); ++i) {
      s += batteries[i];
      if (s >= hrs) {
        s -= hrs;
        --n;
      }
      if (n == 0) {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= batteries.length <= 10⁵|
// * |1 <= batteries[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2, batteries = [3,3,3]
// Output: 4
//
// Initially, insert battery 0 into the first computer and battery 1 into the
// second computer. After two minutes, remove battery 1 from the second computer
// and insert battery 2 instead. Note that battery 1 can still run for one
// minute. At the end of the third minute, battery 0 is drained, and you need to
// remove it from the first computer and insert battery 1 instead. By the end of
// the fourth minute, battery 1 is also drained, and the first computer is no
// longer running. We can run the two computers simultaneously for at most 4
// minutes, so we return 4.

LEETCODE_SOLUTION_UNITTEST(2141, MaximumRunningTimeOfNComputers, example_1) {
  auto        solution  = MakeSolution();
  int         n         = 2;
  vector<int> batteries = {3, 3, 3};
  long long   expect    = 4;
  long long   actual    = solution->maxRunTime(n, batteries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, batteries = [1,1,1,1]
// Output: 2
//
// Initially, insert battery 0 into the first computer and battery 2 into the
// second computer. After one minute, battery 0 and battery 2 are drained so you
// need to remove them and insert battery 1 into the first computer and battery
// 3 into the second computer. After another minute, battery 1 and battery 3 are
// also drained so the first and second computers are no longer running. We can
// run the two computers simultaneously for at most 2 minutes, so we return 2.

LEETCODE_SOLUTION_UNITTEST(2141, MaximumRunningTimeOfNComputers, example_2) {
  auto        solution  = MakeSolution();
  int         n         = 2;
  vector<int> batteries = {1, 1, 1, 1};
  long long   expect    = 2;
  long long   actual    = solution->maxRunTime(n, batteries);
  LCD_EXPECT_EQ(expect, actual);
}
