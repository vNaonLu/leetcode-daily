// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Earliest Possible Day of Full Bloom
//
// https://leetcode.com/problems/earliest-possible-day-of-full-bloom/
//
// Question ID: 2136
// Difficult  : Hard
// Solve Date : 2022/10/29 11:47

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2136. Earliest Possible Day of Full Bloom|:
//
// You have |n| flower seeds. Every seed must be planted first before it can
// begin to grow, then bloom. Planting a seed takes time and so does the growth
// of a seed. You are given two 0-indexed integer arrays |plantTime| and
// |growTime|, of length |n| each:
//
//  • |plantTime[i]| is the number of full days it takes you to plant the |iᵗʰ|
//  seed. Every day, you can work on planting exactly one seed. You do not have
//  to work on planting the same seed on consecutive days, but the planting of a
//  seed is not complete until you have worked |plantTime[i]| days on planting
//  it in total.
//
//  • |growTime[i]| is the number of full days it takes the |iᵗʰ| seed to grow
//  after being completely planted. After the last day of its growth, the flower
//  blooms and stays bloomed forever.
// From the beginning of day |0|, you can plant the seeds in any order.
// Return the earliest possible day where all seeds are blooming.
//

LEETCODE_BEGIN_RESOLVING(2136, EarliestPossibleDayOfFullBloom, Solution);

class Solution {
public:
  int earliestFullBloom(vector<int> &plantTime, vector<int> &growTime) {
    auto idx = vector<int>(plantTime.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
         [&](int i, int j) { return growTime[i] > growTime[j]; });
    auto res = (int)0;
    auto cur = (int)0;
    for (auto i : idx) {
      cur += plantTime[i];
      res = max(res, cur + growTime[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == plantTime.length == growTime.length|
// * |1 <= n <= 10⁵|
// * |1 <= plantTime[i], growTime[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: plantTime = [1,4,3], growTime = [2,3,1]
// Output: 9
//
// The grayed out pots represent planting days, colored pots represent growing
// days, and the flower represents the day it blooms. One optimal way is: On day
// 0, plant the 0ᵗʰ seed. The seed grows for 2 full days and blooms on day 3. On
// days 1, 2, 3, and 4, plant the 1ˢᵗ seed. The seed grows for 3 full days and
// blooms on day 8. On days 5, 6, and 7, plant the 2ⁿᵈ seed. The seed grows for
// 1 full day and blooms on day 9. Thus, on day 9, all the seeds are blooming.

LEETCODE_SOLUTION_UNITTEST(2136, EarliestPossibleDayOfFullBloom, example_1) {
  auto        solution  = MakeSolution();
  vector<int> plantTime = {1, 4, 3};
  vector<int> growTime  = {2, 3, 1};
  int         expect    = 9;
  int         actual    = solution->earliestFullBloom(plantTime, growTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: plantTime = [1,2,3,2], growTime = [2,1,2,1]
// Output: 9
//
// The grayed out pots represent planting days, colored pots represent growing
// days, and the flower represents the day it blooms. One optimal way is: On day
// 1, plant the 0ᵗʰ seed. The seed grows for 2 full days and blooms on day 4. On
// days 0 and 3, plant the 1ˢᵗ seed. The seed grows for 1 full day and blooms on
// day 5. On days 2, 4, and 5, plant the 2ⁿᵈ seed. The seed grows for 2 full
// days and blooms on day 8. On days 6 and 7, plant the 3ʳᵈ seed. The seed grows
// for 1 full day and blooms on day 9. Thus, on day 9, all the seeds are
// blooming.

LEETCODE_SOLUTION_UNITTEST(2136, EarliestPossibleDayOfFullBloom, example_2) {
  auto        solution  = MakeSolution();
  vector<int> plantTime = {1, 2, 3, 2};
  vector<int> growTime  = {2, 1, 2, 1};
  int         expect    = 9;
  int         actual    = solution->earliestFullBloom(plantTime, growTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: plantTime = [1], growTime = [1]
// Output: 2
//
// On day 0, plant the 0ᵗʰ seed. The seed grows for 1 full day and blooms on
// day 2. Thus, on day 2, all the seeds are blooming.

LEETCODE_SOLUTION_UNITTEST(2136, EarliestPossibleDayOfFullBloom, example_3) {
  auto        solution  = MakeSolution();
  vector<int> plantTime = {1};
  vector<int> growTime  = {1};
  int         expect    = 2;
  int         actual    = solution->earliestFullBloom(plantTime, growTime);
  LCD_EXPECT_EQ(expect, actual);
}
