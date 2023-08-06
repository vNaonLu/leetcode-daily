// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Music Playlists
//
// https://leetcode.com/problems/number-of-music-playlists/
//
// Question ID: 920
// Difficult  : Hard
// Solve Date : 2023/08/06 15:10

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |920. Number of Music Playlists|:
//
// Your music player contains |n| different songs. You want to listen to |goal|
// songs (not necessarily different) during your trip. To avoid boredom, you
// will create a playlist so that:
//
//  • Every song is played at least once.
//
//  • A song can only be played again only if |k| other songs have been played.
// Given |n|, |goal|, and |k|, return the number of possible playlists that you
// can create. Since the answer can be very large, return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(920, NumberOfMusicPlaylists, Solution);

class Solution {
public:
  int numMusicPlaylists(int n, int goal, int k) {
    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(goal + 1));
    dp[0][0] = 0;
    dp[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
      dp[i][i] = (dp[i - 1][i - 1] * i) % kMod;
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = i + 1; j <= goal; ++j) {
        dp[i][j] =
            (dp[i][j - 1] * max<int64_t>(0, i - k) + dp[i - 1][j - 1] * i) %
            kMod;
      }
    }
    return dp.back().back();
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= k < n <= goal <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, goal = 3, k = 1
// Output: 6
//
// There are 6 possible playlists: [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1],
// [3, 1, 2], and [3, 2, 1].

LEETCODE_SOLUTION_UNITTEST(920, NumberOfMusicPlaylists, example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  goal     = 3;
  int  k        = 1;
  int  expect   = 6;
  int  actual   = solution->numMusicPlaylists(n, goal, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, goal = 3, k = 0
// Output: 6
//
// There are 6 possible playlists: [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2, 1],
// [2, 1, 2], and [1, 2, 2].

LEETCODE_SOLUTION_UNITTEST(920, NumberOfMusicPlaylists, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  goal     = 3;
  int  k        = 0;
  int  expect   = 6;
  int  actual   = solution->numMusicPlaylists(n, goal, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2, goal = 3, k = 1
// Output: 2
//
// There are 2 possible playlists: [1, 2, 1] and [2, 1, 2].

LEETCODE_SOLUTION_UNITTEST(920, NumberOfMusicPlaylists, example_3) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  goal     = 3;
  int  k        = 1;
  int  expect   = 2;
  int  actual   = solution->numMusicPlaylists(n, goal, k);
  LCD_EXPECT_EQ(expect, actual);
}
