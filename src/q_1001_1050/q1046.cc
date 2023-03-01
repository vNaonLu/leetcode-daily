// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Last Stone Weight
//
// https://leetcode.com/problems/last-stone-weight/
//
// Question ID: 1046
// Difficult  : Easy
// Solve Date : 2022/04/07 18:27

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1046. Last Stone Weight|:
//
// You are given an array of integers |stones| where |stones[i]| is the weight
// of the |iᵗʰ| stone. We are playing a game with the stones. On each turn, we
// choose the heaviest two stones and smash them together. Suppose the heaviest
// two stones have weights |x| and |y| with |x <= y|. The result of this smash
// is:
//
//  • If |x == y|, both stones are destroyed, and
//
//  • If |x != y|, the stone of weight |x| is destroyed, and the stone of weight
//  |y| has new weight |y - x|.
// At the end of the game, there is at most one stone left.
// Return the weight of the last remaining stone. If there are no stones left,
// return |0|.  
//

LEETCODE_BEGIN_RESOLVING(1046, LastStoneWeight, Solution);

class Solution {
public:
  int lastStoneWeight(vector<int> &stones) {
    priority_queue<int> pq;
    for (auto &x : stones) {
      pq.emplace(x);
    }

    while (pq.size() > 1) {
      auto x = pq.top();
      pq.pop();
      auto y = pq.top();
      pq.pop();
      if (x != y) {
        pq.emplace(x - y);
      }
    }

    return pq.empty() ? 0 : pq.top();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= stones.length <= 30|
// * |1 <= stones[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: stones = [2,7,4,1,8,1]
// Output: 1
//
// We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
// we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
// we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
// we combine 1 and 1 to get 0 so the array converts to [1] then that's the
// value of the last stone.

LEETCODE_SOLUTION_UNITTEST(1046, LastStoneWeight, example_1) {
  auto        solution = MakeSolution();
  vector<int> stones   = {2, 7, 4, 1, 8, 1};
  int         expect   = 1;
  int         actual   = solution->lastStoneWeight(stones);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: stones = [1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1046, LastStoneWeight, example_2) {
  auto        solution = MakeSolution();
  vector<int> stones   = {1};
  int         expect   = 1;
  int         actual   = solution->lastStoneWeight(stones);
  LCD_EXPECT_EQ(expect, actual);
}
