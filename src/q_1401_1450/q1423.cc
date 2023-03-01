// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Points You Can Obtain from Cards
//
// https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/
//
// Question ID: 1423
// Difficult  : Medium
// Solve Date : 2022/06/26 14:36

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1423. Maximum Points You Can Obtain from Cards|:
//
// There are several cards arranged in a row, and each card has an associated
// number of points. The points are given in the integer array |cardPoints|. In
// one step, you can take one card from the beginning or from the end of the
// row. You have to take exactly |k| cards. Your score is the sum of the points
// of the cards you have taken. Given the integer array |cardPoints| and the
// integer |k|, return the maximum score you can obtain.
//

LEETCODE_BEGIN_RESOLVING(1423, MaximumPointsYouCanObtainFromCards, Solution);

class Solution {
public:
  int maxScore(vector<int> &cardPoints, int k) {
    int res  = accumulate(cardPoints.begin(), cardPoints.begin() + k, 0);
    int curr = res, l = k, r = cardPoints.size() - 1;

    while (l) {
      curr -= cardPoints[l - 1];
      curr += cardPoints[r];
      res = max(curr, res);

      --l;
      --r;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= cardPoints.length <= 10⁵|
// * |1 <= cardPoints[i] <= 10⁴|
// * |1 <= k <= cardPoints.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: cardPoints = [1,2,3,4,5,6,1], k = 3
// Output: 12
//
// After the first step, your score will always be 1. However, choosing the
// rightmost card first will maximize your total score. The optimal strategy is
// to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.

LEETCODE_SOLUTION_UNITTEST(1423, MaximumPointsYouCanObtainFromCards,
                           example_1) {
  auto        solution   = MakeSolution();
  vector<int> cardPoints = {1, 2, 3, 4, 5, 6, 1};
  int         k          = 3;
  int         expect     = 12;
  int         actual     = solution->maxScore(cardPoints, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: cardPoints = [2,2,2], k = 2
// Output: 4
//
// Regardless of which two cards you take, your score will always be 4.

LEETCODE_SOLUTION_UNITTEST(1423, MaximumPointsYouCanObtainFromCards,
                           example_2) {
  auto        solution   = MakeSolution();
  vector<int> cardPoints = {2, 2, 2};
  int         k          = 2;
  int         expect     = 4;
  int         actual     = solution->maxScore(cardPoints, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: cardPoints = [9,7,7,9,7,7,9], k = 7
// Output: 55
//
// You have to take all the cards. Your score is the sum of points of all cards.

LEETCODE_SOLUTION_UNITTEST(1423, MaximumPointsYouCanObtainFromCards,
                           example_3) {
  auto        solution   = MakeSolution();
  vector<int> cardPoints = {9, 7, 7, 9, 7, 7, 9};
  int         k          = 7;
  int         expect     = 55;
  int         actual     = solution->maxScore(cardPoints, k);
  LCD_EXPECT_EQ(expect, actual);
}
