// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Relative Ranks
//
// https://leetcode.com/problems/relative-ranks/
//
// Question ID: 506
// Difficult  : Easy
// Solve Date : 2023/06/04 19:14

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |506. Relative Ranks|:
//
// You are given an integer array |score| of size |n|, where |score[i]| is the
// score of the |iᵗʰ| athlete in a competition. All the scores are guaranteed to
// be unique. The athletes are placed based on their scores, where the |1ˢᵗ|
// place athlete has the highest score, the |2ⁿᵈ| place athlete has the |2ⁿᵈ|
// highest score, and so on. The placement of each athlete determines their
// rank:
//
//  • The |1ˢᵗ| place athlete's rank is |"Gold Medal"|.
//
//  • The |2ⁿᵈ| place athlete's rank is |"Silver Medal"|.
//
//  • The |3ʳᵈ| place athlete's rank is |"Bronze Medal"|.
//
//  • For the |4ᵗʰ| place to the |nᵗʰ| place athlete, their rank is their
//  placement number (i.e., the |xᵗʰ| place athlete's rank is |"x"|).
// Return an array |answer| of size |n| where |answer[i]| is the rank of the
// |iᵗʰ| athlete.
//
//

LEETCODE_BEGIN_RESOLVING(506, RelativeRanks, Solution);

class Solution {
public:
  vector<string> findRelativeRanks(vector<int> &score) {
    map<int, int, greater<int>> memo;
    vector<string>              res(score.size());
    for (int i = 0; i < score.size(); ++i) {
      memo[score[i]] = i;
    }
    int rank = 1;
    for (auto &[score, index] : memo) {
      auto iter = kName.find(rank);
      if (iter != kName.end()) {
        res[index] = iter->second;
      } else {
        res[index] = to_string(rank);
      }
      ++rank;
    }
    return res;
  }

private:
  const map<int, string> kName = {
      {1,   "Gold Medal"},
      {2, "Silver Medal"},
      {3, "Bronze Medal"}
  };
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == score.length|
// * |1 <= n <= 10⁴|
// * |0 <= score[i] <= 10⁶|
// * All the values in |score| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: score = [5,4,3,2,1]
// Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
//
// The placements are [1ˢᵗ, 2ⁿᵈ, 3ʳᵈ, 4ᵗʰ, 5ᵗʰ].

LEETCODE_SOLUTION_UNITTEST(506, RelativeRanks, example_1) {
  auto           solution = MakeSolution();
  vector<int>    score    = {5, 4, 3, 2, 1};
  vector<string> expect   = {"Gold Medal", "Silver Medal", "Bronze Medal", "4",
                             "5"};
  vector<string> actual   = solution->findRelativeRanks(score);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: score = [10,3,8,9,4]
// Output: ["Gold Medal","5","Bronze Medal","Silver Medal","4"]
//
// The placements are [1ˢᵗ, 5ᵗʰ, 3ʳᵈ, 2ⁿᵈ, 4ᵗʰ].

LEETCODE_SOLUTION_UNITTEST(506, RelativeRanks, example_2) {
  auto           solution = MakeSolution();
  vector<int>    score    = {10, 3, 8, 9, 4};
  vector<string> expect   = {"Gold Medal", "5", "Bronze Medal", "Silver Medal",
                             "4"};
  vector<string> actual   = solution->findRelativeRanks(score);
  LCD_EXPECT_EQ(expect, actual);
}
