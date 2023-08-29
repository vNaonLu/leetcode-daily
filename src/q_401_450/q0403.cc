// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Frog Jump
//
// https://leetcode.com/problems/frog-jump/
//
// Question ID: 403
// Difficult  : Hard
// Solve Date : 2023/08/27 14:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |403. Frog Jump|:
//
// A frog is crossing a river. The river is divided into some number of units,
// and at each unit, there may or may not exist a stone. The frog can jump on a
// stone, but it must not jump into the water. Given a list of |stones|'
// positions (in units) in sorted ascending order, determine if the frog can
// cross the river by landing on the last stone. Initially, the frog is on the
// first stone and assumes the first jump must be |1| unit. If the frog's last
// jump was |k| units, its next jump must be either |k - 1|, |k|, or |k + 1|
// units. The frog can only jump in the forward direction.
//
//

LEETCODE_BEGIN_RESOLVING(403, FrogJump, Solution);

class Solution {
public:
  bool canCross(vector<int> &stones) {
    vector<vector<int>> dp(stones.size(), vector<int>(stones.size() + 1, -1));
    return helper(stones, 0, 0, &dp);
  }

private:
  bool helper(const vector<int> &stones, int i, int k,
              vector<vector<int>> *dp) {
    if (i == stones.size() - 1) {
      return true;
    }
    if (i >= stones.size()) {
      return false;
    }

    if ((*dp)[i][k] != -1) {
      return (*dp)[i][k];
    }
    int res = false;
    for (auto j : {k - 1, k, k + 1}) {
      if (j == 0) {
        continue;
      }

      auto nxt =
          lower_bound(stones.begin() + (i + 1), stones.end(), stones[i] + j);
      if (nxt == stones.end() || *nxt != stones[i] + j) {
        continue;
      }

      res |= helper(stones, distance(stones.begin(), nxt), j, dp);
    }
    return (*dp)[i][k] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= stones.length <= 2000|
// * |0 <= stones[i] <= 2³¹ - 1|
// * |stones[0] == 0|
// * |stones| is sorted in a strictly increasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: stones = [0,1,3,5,6,8,12,17]
// Output: true
//
// The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then
// 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the
// 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.

LEETCODE_SOLUTION_UNITTEST(403, FrogJump, example_1) {
  auto        solution = MakeSolution();
  vector<int> stones   = {0, 1, 3, 5, 6, 8, 12, 17};
  bool        expect   = true;
  bool        actual   = solution->canCross(stones);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: stones = [0,1,2,3,4,8,9,11]
// Output: false
//
// There is no way to jump to the last stone as the gap between the 5th and 6th
// stone is too large.

LEETCODE_SOLUTION_UNITTEST(403, FrogJump, example_2) {
  auto        solution = MakeSolution();
  vector<int> stones   = {0, 1, 2, 3, 4, 8, 9, 11};
  bool        expect   = false;
  bool        actual   = solution->canCross(stones);
  LCD_EXPECT_EQ(expect, actual);
}
