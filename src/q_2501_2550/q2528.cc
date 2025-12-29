// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximize the Minimum Powered City
//
// https://leetcode.com/problems/maximize-the-minimum-powered-city/
//
// Question ID: 2528
// Difficult  : Hard
// Solve Date : 2025/11/07 19:12

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2528. Maximize the Minimum Powered City|:
//
// You are given a 0-indexed integer array |stations| of length |n|, where
// |stations[i]| represents the number of power stations in the |iᵗʰ| city. Each
// power station can provide power to every city in a fixed range. In other
// words, if the range is denoted by |r|, then a power station at city |i| can
// provide power to all cities |j| such that ||i - j| <= r| and |0 <= i, j <= n
// - 1|.
//
//  • Note that ||x|| denotes absolute value. For example, ||7 - 5| = 2| and ||3
//  - 10| = 7|.
// The power of a city is the total number of power stations it is being
// provided power from. The government has sanctioned building |k| more power
// stations, each of which can be built in any city, and have the same range as
// the pre-existing ones. Given the two integers |r| and |k|, return the maximum
// possible minimum power of a city, if the additional power stations are built
// optimally. Note that you can build the |k| power stations in multiple cities.
//
//

LEETCODE_BEGIN_RESOLVING(2528, MaximizeTheMinimumPoweredCity, Solution);

class Solution {
public:
  static bool check(long long minPower, vector<int> stations, int r,
                    long long k, int n) {
    long long power = reduce(stations.begin(), stations.begin() + r + 1, 0LL);

    for (int i = 0; i < n; i++) {
      if (power < minPower) {
        long long need = minPower - power;
        if (need > k)
          return 0;
        k -= need;

        int pos = min(n - 1, i + r);
        stations[pos] += need;
        power += need;
      }

      if (i >= r)
        power -= stations[i - r];
      if (i + r + 1 < n)
        power += stations[i + r + 1];
    }
    return 1;
  }

  static long long maxPower(vector<int> &stations, int r, int k) {
    const int n     = stations.size();
    long long left  = 0,
              right = reduce(stations.begin(), stations.end(), 0LL) + k;
    long long ans   = 0;

    while (left <= right) {
      long long mid = left + (right - left) / 2;
      ;
      if (check(mid, stations, r, k, n)) {
        ans  = mid;
        left = mid + 1;
      } else
        right = mid - 1;
    }
    return ans;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == stations.length|
// * |1 <= n <= 10⁵|
// * |0 <= stations[i] <= 10⁵|
// * |0 <= r <= n - 1|
// * |0 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: stations = [1,2,4,5,0], r = 1, k = 2
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2528, MaximizeTheMinimumPoweredCity, example_1) {
  auto        solution = MakeSolution();
  vector<int> stations = {1, 2, 4, 5, 0};
  int         r        = 1;
  int         k        = 2;
  long long   expect   = 5;
  long long   actual   = solution->maxPower(stations, r, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: stations = [4,4,4,4], r = 0, k = 3
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2528, MaximizeTheMinimumPoweredCity, example_2) {
  auto        solution = MakeSolution();
  vector<int> stations = {4, 4, 4, 4};
  int         r        = 0;
  int         k        = 3;
  long long   expect   = 4;
  long long   actual   = solution->maxPower(stations, r, k);
  LCD_EXPECT_EQ(expect, actual);
}
