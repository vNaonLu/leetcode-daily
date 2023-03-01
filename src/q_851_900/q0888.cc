// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Fair Candy Swap
//
// https://leetcode.com/problems/fair-candy-swap/
//
// Question ID: 888
// Difficult  : Easy
// Solve Date : 2021/11/12 18:29

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |888. Fair Candy Swap|:
//
// Alice and Bob have a different total number of candies. You are given two
// integer arrays |aliceSizes| and |bobSizes| where |aliceSizes[i]| is the
// number of candies of the |iᵗʰ| box of candy that Alice has and |bobSizes[j]|
// is the number of candies of the |jᵗʰ| box of candy that Bob has. Since they
// are friends, they would like to exchange one candy box each so that after the
// exchange, they both have the same total amount of candy. The total amount of
// candy a person has is the sum of the number of candies in each box they have.
// Return an integer array |answer| where |answer[0]| is the number of candies
// in the box that Alice must exchange, and |answer[1]| is the number of candies
// in the box that Bob must exchange. If there are multiple answers, you may
// return any one of them. It is guaranteed that at least one answer exists.  
//

LEETCODE_BEGIN_RESOLVING(888, FairCandySwap, Solution);

class Solution {
public:
  vector<int> fairCandySwap(vector<int> &aliceSizes, vector<int> &bobSizes) {
    int alice_candy = 0, bob_candy = 0;
    for (const auto &x : aliceSizes)
      alice_candy += x;
    for (const auto &x : bobSizes)
      bob_candy += x;
    int                delta = (bob_candy - alice_candy) / 2;
    unordered_set<int> bob_set;
    for (const auto &x : bobSizes)
      bob_set.insert(x);
    for (const auto &x : aliceSizes)
      if (bob_set.count(delta + x))
        return vector<int>{x, x + delta};
    assert(false);
    return vector<int>{};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= aliceSizes.length, bobSizes.length <= 10⁴|
// * |1 <= aliceSizes[i], bobSizes[j] <= 10⁵|
// * Alice and Bob have a different total number of candies.
// * There will be at least one valid answer for the given input.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: aliceSizes = [1,1], bobSizes = [2,2]
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(888, FairCandySwap, example_1) {
  auto        solution   = MakeSolution();
  vector<int> aliceSizes = {1, 1};
  vector<int> bobSizes   = {2, 2};
  vector<int> expect     = {1, 2};
  vector<int> actual     = solution->fairCandySwap(aliceSizes, bobSizes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: aliceSizes = [1,2], bobSizes = [2,3]
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(888, FairCandySwap, example_2) {
  auto        solution   = MakeSolution();
  vector<int> aliceSizes = {1, 2};
  vector<int> bobSizes   = {2, 3};
  vector<int> expect     = {1, 2};
  vector<int> actual     = solution->fairCandySwap(aliceSizes, bobSizes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: aliceSizes = [2], bobSizes = [1,3]
// Output: [2,3]
//

LEETCODE_SOLUTION_UNITTEST(888, FairCandySwap, example_3) {
  auto        solution   = MakeSolution();
  vector<int> aliceSizes = {2};
  vector<int> bobSizes   = {1, 3};
  vector<int> expect     = {2, 3};
  vector<int> actual     = solution->fairCandySwap(aliceSizes, bobSizes);
  LCD_EXPECT_EQ(expect, actual);
}
