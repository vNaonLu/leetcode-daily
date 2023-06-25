// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count All Possible Routes
//
// https://leetcode.com/problems/count-all-possible-routes/
//
// Question ID: 1575
// Difficult  : Hard
// Solve Date : 2023/06/25 13:01

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1575. Count All Possible Routes|:
//
// You are given an array of distinct positive integers locations where
// |locations[i]| represents the position of city |i|. You are also given
// integers |start|, |finish| and |fuel| representing the starting city, ending
// city, and the initial amount of fuel you have, respectively. At each step, if
// you are at city |i|, you can pick any city |j| such that |j != i| and |0 <= j
// < locations.length| and move to city |j|. Moving from city |i| to city |j|
// reduces the amount of fuel you have by ||locations[i] - locations[j]||.
// Please notice that ||x|| denotes the absolute value of |x|. Notice that
// |fuel| cannot become negative at any point in time, and that you are allowed
// to visit any city more than once (including |start| and |finish|). Return the
// count of all possible routes from |start| to |finish|. Since the answer may
// be too large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1575, CountAllPossibleRoutes, Solution);

class Solution {
public:
  int countRoutes(vector<int> &locations, int start, int finish, int fuel) {
    int                 n = locations.size();
    vector<vector<int>> dp(n, vector<int>(fuel + 1, 0));
    int                 res = 0;
    dp[start][fuel]         = 1;
    for (int f = fuel; f >= 0; --f) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          int diff = abs(locations[i] - locations[j]);
          if (i != j && f >= diff) {
            dp[j][f - diff] = (dp[j][f - diff] + dp[i][f]) % kMod;
          }
        }
      }
    }
    for (int i = 0; i <= fuel; ++i) {
      res = (res + dp[finish][i]) % kMod;
    }
    return res;
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= locations.length <= 100|
// * |1 <= locations[i] <= 10⁹|
// * All integers in |locations| are distinct.
// * |0 <= start, finish < locations.length|
// * |1 <= fuel <= 200|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
// Output: 4
//
// The following are all possible routes, each uses 5 units of fuel:
// 1 -> 3
// 1 -> 2 -> 3
// 1 -> 4 -> 3
// 1 -> 4 -> 2 -> 3

LEETCODE_SOLUTION_UNITTEST(1575, CountAllPossibleRoutes, example_1) {
  auto        solution  = MakeSolution();
  vector<int> locations = {2, 3, 6, 8, 4};
  int         start     = 1;
  int         finish    = 3;
  int         fuel      = 5;
  int         expect    = 4;
  int         actual    = solution->countRoutes(locations, start, finish, fuel);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
// Output: 5
//
// The following are all possible routes:
// 1 -> 0, used fuel = 1
// 1 -> 2 -> 0, used fuel = 5
// 1 -> 2 -> 1 -> 0, used fuel = 5
// 1 -> 0 -> 1 -> 0, used fuel = 3
// 1 -> 0 -> 1 -> 0 -> 1 -> 0, used fuel = 5

LEETCODE_SOLUTION_UNITTEST(1575, CountAllPossibleRoutes, example_2) {
  auto        solution  = MakeSolution();
  vector<int> locations = {4, 3, 1};
  int         start     = 1;
  int         finish    = 0;
  int         fuel      = 6;
  int         expect    = 5;
  int         actual    = solution->countRoutes(locations, start, finish, fuel);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: locations = [5,2,1], start = 0, finish = 2, fuel = 3
// Output: 0
//
// It is impossible to get from 0 to 2 using only 3 units of fuel since the
// shortest route needs 4 units of fuel.

LEETCODE_SOLUTION_UNITTEST(1575, CountAllPossibleRoutes, example_3) {
  auto        solution  = MakeSolution();
  vector<int> locations = {5, 2, 1};
  int         start     = 0;
  int         finish    = 2;
  int         fuel      = 3;
  int         expect    = 0;
  int         actual    = solution->countRoutes(locations, start, finish, fuel);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [2,1,5]
// 0
// 0
// 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1575, CountAllPossibleRoutes, extra_testcase_1) {
  auto        solution  = MakeSolution();
  vector<int> locations = {2, 1, 5};
  int         start     = 0;
  int         finish    = 0;
  int         fuel      = 3;
  int         expect    = 2;
  int         actual    = solution->countRoutes(locations, start, finish, fuel);
  LCD_EXPECT_EQ(expect, actual);
}
