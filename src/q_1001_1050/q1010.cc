// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Pairs of Songs With Total Durations Divisible by 60
//
// https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/
//
// Question ID: 1010
// Difficult  : Medium
// Solve Date : 2022/01/02 15:26

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1010. Pairs of Songs With Total Durations Divisible by 60|:
//
// You are given a list of songs where the |iᵗʰ| song has a duration of
// |time[i]| seconds. Return the number of pairs of songs for which their total
// duration in seconds is divisible by |60|. Formally, we want the number of
// indices |i|, |j| such that |i < j| with |(time[i] + time[j]) % 60 == 0|.  
//

LEETCODE_BEGIN_RESOLVING(1010, PairsOfSongsWithTotalDurationsDivisibleBy60,
                         Solution);

class Solution {
public:
  int numPairsDivisibleBy60(vector<int> &time) {
    int                     res = 0;
    unordered_map<int, int> hash;
    for (auto &x : time)
      x %= 60;
    for (const auto &x : time) {
      int f = 60 - x;
      if (f == 60 && hash.count(0))
        res += hash[0];
      else if (hash.count(f))
        res += hash[f];
      ++hash[x];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= time.length <= 6 * 10⁴|
// * |1 <= time[i] <= 500|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: time = [30,20,150,100,40]
// Output: 3
//
// Three pairs have a total duration divisible by 60:
// (time[0] = 30, time[2] = 150): total duration 180
// (time[1] = 20, time[3] = 100): total duration 120
// (time[1] = 20, time[4] = 40): total duration 60

LEETCODE_SOLUTION_UNITTEST(1010, PairsOfSongsWithTotalDurationsDivisibleBy60,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> time     = {30, 20, 150, 100, 40};
  int         expect   = 3;
  int         actual   = solution->numPairsDivisibleBy60(time);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: time = [60,60,60]
// Output: 3
//
// All three pairs have a total duration of 120, which is divisible by 60.

LEETCODE_SOLUTION_UNITTEST(1010, PairsOfSongsWithTotalDurationsDivisibleBy60,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> time     = {60, 60, 60};
  int         expect   = 3;
  int         actual   = solution->numPairsDivisibleBy60(time);
  LCD_EXPECT_EQ(expect, actual);
}
