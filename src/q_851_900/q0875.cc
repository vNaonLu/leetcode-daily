// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Koko Eating Bananas
//
// https://leetcode.com/problems/koko-eating-bananas/
//
// Question ID: 875
// Difficult  : Medium
// Solve Date : 2022/01/20 18:13

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |875. Koko Eating Bananas|:
//
// Koko loves to eat bananas. There are |n| piles of bananas, the |iᵗʰ| pile has
// |piles[i]| bananas. The guards have gone and will come back in |h| hours.
// Koko can decide her bananas-per-hour eating speed of |k|. Each hour, she
// chooses some pile of bananas and eats |k| bananas from that pile. If the pile
// has less than |k| bananas, she eats all of them instead and will not eat any
// more bananas during this hour. Koko likes to eat slowly but still wants to
// finish eating all the bananas before the guards return. Return the minimum
// integer |k| such that she can eat all the bananas within |h| hours.  
//

LEETCODE_BEGIN_RESOLVING(875, KokoEatingBananas, Solution);

class Solution {
public:
  int minEatingSpeed(vector<int> &piles, int h) {
    int left = 1, right = *max_element(piles.begin(), piles.end());

    while (left < right) {
      int mid   = left + (right - left) / 2;
      int spent = 0;

      for (int pile : piles) {
        spent += pile / mid + (pile % mid == 0 ? 0 : 1);
      }

      if (spent <= h) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }

    return right;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= piles.length <= 10⁴|
// * |piles.length <= h <= 10⁹|
// * |1 <= piles[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: piles = [3,6,7,11], h = 8
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(875, KokoEatingBananas, example_1) {
  auto        solution = MakeSolution();
  vector<int> piles    = {3, 6, 7, 11};
  int         h        = 8;
  int         expect   = 4;
  int         actual   = solution->minEatingSpeed(piles, h);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: piles = [30,11,23,4,20], h = 5
// Output: 30
//

LEETCODE_SOLUTION_UNITTEST(875, KokoEatingBananas, example_2) {
  auto        solution = MakeSolution();
  vector<int> piles    = {30, 11, 23, 4, 20};
  int         h        = 5;
  int         expect   = 30;
  int         actual   = solution->minEatingSpeed(piles, h);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: piles = [30,11,23,4,20], h = 6
// Output: 23
//

LEETCODE_SOLUTION_UNITTEST(875, KokoEatingBananas, example_3) {
  auto        solution = MakeSolution();
  vector<int> piles    = {30, 11, 23, 4, 20};
  int         h        = 6;
  int         expect   = 23;
  int         actual   = solution->minEatingSpeed(piles, h);
  LCD_EXPECT_EQ(expect, actual);
}
