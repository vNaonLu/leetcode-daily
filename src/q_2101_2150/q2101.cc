// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Detonate the Maximum Bombs
//
// https://leetcode.com/problems/detonate-the-maximum-bombs/
//
// Question ID: 2101
// Difficult  : Medium
// Solve Date : 2023/06/02 14:55

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2101. Detonate the Maximum Bombs|:
//
// You are given a list of bombs. The range of a bomb is defined as the area
// where its effect can be felt. This area is in the shape of a circle with the
// center as the location of the bomb. The bombs are represented by a 0-indexed
// 2D integer array |bombs| where |bombs[i] = [xᵢ, yᵢ, rᵢ]|. |xᵢ| and |yᵢ|
// denote the X-coordinate and Y-coordinate of the location of the |iᵗʰ| bomb,
// whereas |rᵢ| denotes the radius of its range. You may choose to detonate a
// single bomb. When a bomb is detonated, it will detonate all bombs that lie in
// its range. These bombs will further detonate the bombs that lie in their
// ranges. Given the list of |bombs|, return the maximum number of bombs that
// can be detonated if you are allowed to detonate only one bomb.
//
//

LEETCODE_BEGIN_RESOLVING(2101, DetonateTheMaximumBombs, Solution);

class Solution {
public:
  int maximumDetonation(vector<vector<int>> &bombs) {
    int                 n = bombs.size();
    vector<vector<int>> detonate(n);
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (willDetonate(bombs[i], bombs[j])) {
          detonate[i].emplace_back(j);
        }
        if (willDetonate(bombs[j], bombs[i])) {
          detonate[j].emplace_back(i);
        }
      }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
      queue<int>   q;
      vector<bool> vis(n, false);
      int          cur = 0;
      q.emplace(i);
      vis[i] = true;
      while (!q.empty()) {
        auto tmp = std::move(q);
        while (!tmp.empty()) {
          auto b = tmp.front();
          tmp.pop();
          ++cur;
          for (auto nxt : detonate[b]) {
            if (!vis[nxt]) {
              q.emplace(nxt);
              vis[nxt] = true;
            }
          }
        }
        res = max(res, cur);
      }
    }
    return res;
  }

private:
  bool willDetonate(vector<int> &b1, vector<int> &b2) {
    int64_t b1x = b1[0];
    int64_t b1y = b1[1];
    int64_t b1r = b1[2];
    int64_t b2x = b2[0];
    int64_t b2y = b2[1];
    return b1r * b1r >=
           ((b2x - b1x) * (b2x - b1x)) + ((b2y - b1y) * (b2y - b1y));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= bombs.length <= 100|
// * |bombs[i].length == 3|
// * |1 <= xᵢ, yᵢ, rᵢ <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: bombs = [[2,1,3],[6,1,4]]
// Output: 2
//
// The above figure shows the positions and ranges of the 2 bombs.
// If we detonate the left bomb, the right bomb will not be affected.
// But if we detonate the right bomb, both bombs will be detonated.
// So the maximum bombs that can be detonated is max(1, 2) = 2.

LEETCODE_SOLUTION_UNITTEST(2101, DetonateTheMaximumBombs, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> bombs    = {
      {2, 1, 3},
      {6, 1, 4}
  };
  int expect = 2;
  int actual = solution->maximumDetonation(bombs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: bombs = [[1,1,5],[10,10,5]]
// Output: 1
// Explanation:
// Detonating either bomb will not detonate the other bomb, so the maximum
// number of bombs that can be detonated is 1.
//

LEETCODE_SOLUTION_UNITTEST(2101, DetonateTheMaximumBombs, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> bombs    = {
      { 1,  1, 5},
      {10, 10, 5}
  };
  int expect = 1;
  int actual = solution->maximumDetonation(bombs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
// Output: 5
//
// The best bomb to detonate is bomb 0 because:
// - Bomb 0 detonates bombs 1 and 2. The red circle denotes the range of bomb 0.
// - Bomb 2 detonates bomb 3. The blue circle denotes the range of bomb 2.
// - Bomb 3 detonates bomb 4. The green circle denotes the range of bomb 3.
// Thus all 5 bombs are detonated.

LEETCODE_SOLUTION_UNITTEST(2101, DetonateTheMaximumBombs, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> bombs    = {
      {1, 2, 3},
      {2, 3, 1},
      {3, 4, 2},
      {4, 5, 3},
      {5, 6, 4}
  };
  int expect = 5;
  int actual = solution->maximumDetonation(bombs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[1,1,100000],[100000,100000,1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2101, DetonateTheMaximumBombs, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> bombs    = {
      {     1,      1, 100000},
      {100000, 100000,      1}
  };
  int expect = 1;
  int actual = solution->maximumDetonation(bombs);
  LCD_EXPECT_EQ(expect, actual);
}
