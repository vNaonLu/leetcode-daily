// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Kids With the Greatest Number of Candies
//
// https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/
//
// Question ID: 1431
// Difficult  : Easy
// Solve Date : 2023/04/17 19:54

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1431. Kids With the Greatest Number of Candies|:
//
// There are |n| kids with candies. You are given an integer array |candies|,
// where each |candies[i]| represents the number of candies the |iᵗʰ| kid has,
// and an integer |extraCandies|, denoting the number of extra candies that you
// have. Return a boolean array |result| of length |n|, where |result[i]| is
// |true| if, after giving the |iᵗʰ| kid all the |extraCandies|, they will have
// the greatest number of candies among all the kids, or |false| otherwise. Note
// that multiple kids can have the greatest number of candies.
//
//

LEETCODE_BEGIN_RESOLVING(1431, KidsWithTheGreatestNumberOfCandies, Solution);

class Solution {
public:
  vector<bool> kidsWithCandies(vector<int> &candies, int extraCandies) {
    vector<bool> res(candies.size(), false);
    int          mx = *max_element(candies.begin(), candies.end());
    for (int i = 0; i < candies.size(); ++i) {
      res[i] = candies[i] + extraCandies >= mx;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == candies.length|
// * |2 <= n <= 100|
// * |1 <= candies[i] <= 100|
// * |1 <= extraCandies <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: candies = [2,3,5,1,3], extraCandies = 3
// Output: [true,true,true,false,true]
//
// If you give all extraCandies to:
// - Kid 1, they will have 2 + 3 = 5 candies, which is the greatest among the
// kids.
// - Kid 2, they will have 3 + 3 = 6 candies, which is the greatest among the
// kids.
// - Kid 3, they will have 5 + 3 = 8 candies, which is the greatest among the
// kids.
// - Kid 4, they will have 1 + 3 = 4 candies, which is not the greatest among
// the kids.
// - Kid 5, they will have 3 + 3 = 6 candies, which is the greatest among the
// kids.

LEETCODE_SOLUTION_UNITTEST(1431, KidsWithTheGreatestNumberOfCandies,
                           example_1) {
  auto         solution     = MakeSolution();
  vector<int>  candies      = {2, 3, 5, 1, 3};
  int          extraCandies = 3;
  vector<bool> expect       = {true, true, true, false, true};
  vector<bool> actual       = solution->kidsWithCandies(candies, extraCandies);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: candies = [4,2,1,1,2], extraCandies = 1
// Output: [true,false,false,false,false]
//
// There is only 1 extra candy.
// Kid 1 will always have the greatest number of candies, even if a different
// kid is given the extra candy.

LEETCODE_SOLUTION_UNITTEST(1431, KidsWithTheGreatestNumberOfCandies,
                           example_2) {
  auto         solution     = MakeSolution();
  vector<int>  candies      = {4, 2, 1, 1, 2};
  int          extraCandies = 1;
  vector<bool> expect       = {true, false, false, false, false};
  vector<bool> actual       = solution->kidsWithCandies(candies, extraCandies);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: candies = [12,1,12], extraCandies = 10
// Output: [true,false,true]
//

LEETCODE_SOLUTION_UNITTEST(1431, KidsWithTheGreatestNumberOfCandies,
                           example_3) {
  auto         solution     = MakeSolution();
  vector<int>  candies      = {12, 1, 12};
  int          extraCandies = 10;
  vector<bool> expect       = {true, false, true};
  vector<bool> actual       = solution->kidsWithCandies(candies, extraCandies);
  LCD_EXPECT_EQ(expect, actual);
}
