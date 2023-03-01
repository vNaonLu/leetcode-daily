// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Stones to Minimize the Total
//
// https://leetcode.com/problems/remove-stones-to-minimize-the-total/
//
// Question ID: 1962
// Difficult  : Medium
// Solve Date : 2022/12/28 10:47

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1962. Remove Stones to Minimize the Total|:
//
// You are given a 0-indexed integer array |piles|, where |piles[i]| represents
// the number of stones in the |iᵗʰ| pile, and an integer |k|. You should apply
// the following operation exactly |k| times:
//
//  • Choose any |piles[i]| and remove |floor(piles[i] / 2)| stones from it.
// Notice that you can apply the operation on the same pile more than once.
// Return the minimum possible total number of stones remaining after applying
// the |k| operations. |floor(x)| is the greatest integer that is smaller than
// or equal to |x| (i.e., rounds |x| down).
//

LEETCODE_BEGIN_RESOLVING(1962, RemoveStonesToMinimizeTheTotal, Solution);

class Solution {
public:
  int minStoneSum(vector<int> &piles, int k) {
    auto pq = priority_queue<int>();
    for (auto x : piles) {
      pq.emplace(x);
    }
    while (k--) {
      auto n = pq.top();
      pq.pop();
      pq.emplace(n - n / 2);
    }
    auto res = (int)0;
    while (!pq.empty()) {
      res += pq.top();
      pq.pop();
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= piles.length <= 10⁵|
// * |1 <= piles[i] <= 10⁴|
// * |1 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: piles = [5,4,9], k = 2
// Output: 12
//
// Steps of a possible scenario are:
// - Apply the operation on pile 2. The resulting piles are [5,4,5].
// - Apply the operation on pile 0. The resulting piles are [3,4,5].
// The total number of stones in [3,4,5] is 12.

LEETCODE_SOLUTION_UNITTEST(1962, RemoveStonesToMinimizeTheTotal, example_1) {
  auto        solution = MakeSolution();
  vector<int> piles    = {5, 4, 9};
  int         k        = 2;
  int         expect   = 12;
  int         actual   = solution->minStoneSum(piles, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: piles = [4,3,6,7], k = 3
// Output: 12
//
// Steps of a possible scenario are:
// - Apply the operation on pile 2. The resulting piles are [4,3,3,7].
// - Apply the operation on pile 3. The resulting piles are [4,3,3,4].
// - Apply the operation on pile 0. The resulting piles are [2,3,3,4].
// The total number of stones in [2,3,3,4] is 12.

LEETCODE_SOLUTION_UNITTEST(1962, RemoveStonesToMinimizeTheTotal, example_2) {
  auto        solution = MakeSolution();
  vector<int> piles    = {4, 3, 6, 7};
  int         k        = 3;
  int         expect   = 12;
  int         actual   = solution->minStoneSum(piles, k);
  LCD_EXPECT_EQ(expect, actual);
}
