// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Flowers in Full Bloom
//
// https://leetcode.com/problems/number-of-flowers-in-full-bloom/
//
// Question ID: 2251
// Difficult  : Hard
// Solve Date : 2023/10/11 20:42

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2251. Number of Flowers in Full Bloom|:
//
// You are given a 0-indexed 2D integer array |flowers|, where |flowers[i] =
// [startᵢ, endᵢ]| means the |iᵗʰ| flower will be in full bloom from |startᵢ| to
// |endᵢ| (inclusive). You are also given a 0-indexed integer array |people| of
// size |n|, where |people[i]| is the time that the |iᵗʰ| person will arrive to
// see the flowers. Return an integer array |answer| of size |n|, where
// |answer[i]| is the number of flowers that are in full bloom when the |iᵗʰ|
// person arrives.
//
//

LEETCODE_BEGIN_RESOLVING(2251, NumberOfFlowersInFullBloom, Solution);

class Solution {
public:
  vector<int> fullBloomFlowers(vector<vector<int>> &flowers,
                               vector<int>         &people) {
    vector<int> st;
    vector<int> bl;
    for (auto &x : flowers) {
      st.emplace_back(x[0]);
      bl.emplace_back(x[1]);
    }

    sort(st.begin(), st.end());
    sort(bl.begin(), bl.end());

    vector<int> res;
    for (auto x : people) {
      int p = upper_bound(st.begin(), st.end(), x) - st.begin();
      int q = lower_bound(bl.begin(), bl.end(), x) - bl.begin();
      res.emplace_back(p - q);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= flowers.length <= 5 * 10⁴|
// * |flowers[i].length == 2|
// * |1 <= startᵢ <= endᵢ <= 10⁹|
// * |1 <= people.length <= 5 * 10⁴|
// * |1 <= people[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: flowers = [[1,6],[3,7],[9,12],[4,13]], poeple = [2,3,7,11]
// Output: [1,2,2,2]
//
// The figure above shows the times when the flowers are in full bloom and when
// the people arrive. For each person, we return the number of flowers in full
// bloom during their arrival.

LEETCODE_SOLUTION_UNITTEST(2251, NumberOfFlowersInFullBloom, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> flowers  = {
      {1,  6},
      {3,  7},
      {9, 12},
      {4, 13}
  };
  vector<int> people = {2, 3, 7, 11};
  vector<int> expect = {1, 2, 2, 2};
  vector<int> actual = solution->fullBloomFlowers(flowers, people);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: flowers = [[1,10],[3,3]], poeple = [3,3,2]
// Output: [2,2,1]
//
// The figure above shows the times when the flowers are in full bloom and when
// the people arrive. For each person, we return the number of flowers in full
// bloom during their arrival.

LEETCODE_SOLUTION_UNITTEST(2251, NumberOfFlowersInFullBloom, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> flowers  = {
      {1, 10},
      {3,  3}
  };
  vector<int> people = {3, 3, 2};
  vector<int> expect = {2, 2, 1};
  vector<int> actual = solution->fullBloomFlowers(flowers, people);
  LCD_EXPECT_EQ(expect, actual);
}
