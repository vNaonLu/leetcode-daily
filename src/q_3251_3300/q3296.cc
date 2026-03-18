// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Number of Seconds to Make Mountain Height Zero
//
// https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/
//
// Question ID: 3296
// Difficult  : Medium
// Solve Date : 2026/03/18 19:31

#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3296. Minimum Number of Seconds to Make Mountain Height
// Zero|:
//
// You are given an integer |mountainHeight| denoting the height of a mountain.
// You are also given an integer array |workerTimes| representing the work time
// of workers in seconds. The workers work simultaneously to reduce the height
// of the mountain. For worker |i|:
//
//  • To decrease the mountain's height by |x|, it takes |workerTimes[i] +
//  workerTimes[i] * 2 + ... + workerTimes[i] * x| seconds. For example:
//
//
//    • To reduce the height of the mountain by 1, it takes |workerTimes[i]|
//    seconds.
//
//    • To reduce the height of the mountain by 2, it takes |workerTimes[i] +
//    workerTimes[i] * 2| seconds, and so on.
//
//
// Return an integer representing the minimum number of seconds required for the
// workers to make the height of the mountain 0.
//
//

LEETCODE_BEGIN_RESOLVING(3296, MinimumNumberOfSecondsToMakeMountainHeightZero,
                         Solution);

class Solution {
public:
  long long minNumberOfSeconds(int height, vector<int> &times) {
    using ll = long long;
    ll lo    = 1;
    ll hi    = 1e16;

    while (lo < hi) {
      ll mid = (lo + hi) >> 1;
      ll tot = 0;
      for (int i = 0; i < times.size() && tot < height; i++)
        tot += (ll)(sqrt((double)mid / times[i] * 2 + 0.25) - 0.5);
      if (tot >= height)
        hi = mid;
      else
        lo = mid + 1;
    }

    return lo;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= mountainHeight <= 10⁵|
// * |1 <= workerTimes.length <= 10⁴|
// * |1 <= workerTimes[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mountainHeight = 4, workerTimes = [2,1,1]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3296, MinimumNumberOfSecondsToMakeMountainHeightZero,
                           example_1) {
  auto        solution       = MakeSolution();
  int         mountainHeight = 4;
  vector<int> workerTimes    = {2, 1, 1};
  long long   expect         = 3;
  long long actual = solution->minNumberOfSeconds(mountainHeight, workerTimes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mountainHeight = 10, workerTimes = [3,2,2,4]
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(3296, MinimumNumberOfSecondsToMakeMountainHeightZero,
                           example_2) {
  auto        solution       = MakeSolution();
  int         mountainHeight = 10;
  vector<int> workerTimes    = {3, 2, 2, 4};
  long long   expect         = 12;
  long long actual = solution->minNumberOfSeconds(mountainHeight, workerTimes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: mountainHeight = 5, workerTimes = [1]
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(3296, MinimumNumberOfSecondsToMakeMountainHeightZero,
                           example_3) {
  auto        solution       = MakeSolution();
  int         mountainHeight = 5;
  vector<int> workerTimes    = {1};
  long long   expect         = 15;
  long long actual = solution->minNumberOfSeconds(mountainHeight, workerTimes);
  LCD_EXPECT_EQ(expect, actual);
}
