// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Length of Pair Chain
//
// https://leetcode.com/problems/maximum-length-of-pair-chain/
//
// Question ID: 646
// Difficult  : Medium
// Solve Date : 2023/08/26 14:55

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |646. Maximum Length of Pair Chain|:
//
// You are given an array of |n| pairs |pairs| where |pairs[i] = [leftᵢ,
// rightᵢ]| and |leftᵢ < rightᵢ|. A pair |p2 = [c, d]| follows a pair |p1 = [a,
// b]| if |b < c|. A chain of pairs can be formed in this fashion. Return the
// length longest chain which can be formed. You do not need to use up all the
// given intervals. You can select pairs in any order.
//
//

LEETCODE_BEGIN_RESOLVING(646, MaximumLengthOfPairChain, Solution);

class Solution {
public:
  int findLongestChain(vector<vector<int>> &pairs) {
    sort(pairs.begin(), pairs.end());
    vector<vector<int>> dp(pairs.size(), vector<int>(2010, -1));
    return helper(0, pairs, -1001, &dp);
  }

private:
  int helper(int i, const vector<vector<int>> &pairs, int mx,
             vector<vector<int>> *dp) {
    if (pairs.size() == i) {
      return 0;
    }
    if ((*dp)[i][mx + 1001] != -1) {
      return (*dp)[i][mx + 1001];
    }
    int res = helper(i + 1, pairs, mx, dp);
    if (pairs[i][0] > mx) {
      res = max(res, 1 + helper(i + 1, pairs, pairs[i][1], dp));
    }
    return (*dp)[i][mx + 1001] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == pairs.length|
// * |1 <= n <= 1000|
// * |-1000 <= leftᵢ < rightᵢ <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: pairs = [[1,2],[2,3],[3,4]]
// Output: 2
//
// The longest chain is [1,2] -> [3,4].

LEETCODE_SOLUTION_UNITTEST(646, MaximumLengthOfPairChain, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> pairs    = {
      {1, 2},
      {2, 3},
      {3, 4}
  };
  int expect = 2;
  int actual = solution->findLongestChain(pairs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: pairs = [[1,2],[7,8],[4,5]]
// Output: 3
//
// The longest chain is [1,2] -> [4,5] -> [7,8].

LEETCODE_SOLUTION_UNITTEST(646, MaximumLengthOfPairChain, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> pairs    = {
      {1, 2},
      {7, 8},
      {4, 5}
  };
  int expect = 3;
  int actual = solution->findLongestChain(pairs);
  LCD_EXPECT_EQ(expect, actual);
}
