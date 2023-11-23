// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Take Gifts From the Richest Pile
//
// https://leetcode.com/problems/take-gifts-from-the-richest-pile/
//
// Question ID: 2558
// Difficult  : Easy
// Solve Date : 2023/11/23 19:23

#include <cmath>
#include <iosfwd>
#include <numeric>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2558. Take Gifts From the Richest Pile|:
//
// You are given an integer array |gifts| denoting the number of gifts in
// various piles. Every second, you do the following:
//
//  • Choose the pile with the maximum number of gifts.
//
//  • If there is more than one pile with the maximum number of gifts, choose
//  any.
//
//  • Leave behind the floor of the square root of the number of gifts in the
//  pile. Take the rest of the gifts.
// Return the number of gifts remaining after |k| seconds.
//
//

LEETCODE_BEGIN_RESOLVING(2558, TakeGiftsFromTheRichestPile, Solution);

class Solution {
public:
  long long pickGifts(vector<int> &gifts, int k) {
    priority_queue<int> pq{gifts.begin(), gifts.end()};
    while (k--) {
      if (pq.top() == 1) {
        break;
      }

      auto t = pq.top();
      pq.pop();
      pq.emplace(sqrt(t));
    }
    int64_t res = 0;
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
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= gifts.length <= 10³|
// * |1 <= gifts[i] <= 10⁹|
// * |1 <= k <= 10³|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: gifts = [25,64,9,4,100], k = 4
// Output: 29
//
// The gifts are taken in the following way:
// - In the first second, the last pile is chosen and 10 gifts are left behind.
// - Then the second pile is chosen and 8 gifts are left behind.
// - After that the first pile is chosen and 5 gifts are left behind.
// - Finally, the last pile is chosen again and 3 gifts are left behind.
// The final remaining gifts are [5,8,9,4,3], so the total number of gifts
// remaining is 29.

LEETCODE_SOLUTION_UNITTEST(2558, TakeGiftsFromTheRichestPile, example_1) {
  auto        solution = MakeSolution();
  vector<int> gifts    = {25, 64, 9, 4, 100};
  int         k        = 4;
  long long   expect   = 29;
  long long   actual   = solution->pickGifts(gifts, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: gifts = [1,1,1,1], k = 4
// Output: 4
//
// In this case, regardless which pile you choose, you have to leave behind 1
// gift in each pile. That is, you can't take any pile with you. So, the total
// gifts remaining are 4.

LEETCODE_SOLUTION_UNITTEST(2558, TakeGiftsFromTheRichestPile, example_2) {
  auto        solution = MakeSolution();
  vector<int> gifts    = {1, 1, 1, 1};
  int         k        = 4;
  long long   expect   = 4;
  long long   actual   = solution->pickGifts(gifts, k);
  LCD_EXPECT_EQ(expect, actual);
}
