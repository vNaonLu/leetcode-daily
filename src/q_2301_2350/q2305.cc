// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Fair Distribution of Cookies
//
// https://leetcode.com/problems/fair-distribution-of-cookies/
//
// Question ID: 2305
// Difficult  : Medium
// Solve Date : 2023/07/01 16:47

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2305. Fair Distribution of Cookies|:
//
// You are given an integer array |cookies|, where |cookies[i]| denotes the
// number of cookies in the |iᵗʰ| bag. You are also given an integer |k| that
// denotes the number of children to distribute all the bags of cookies to. All
// the cookies in the same bag must go to the same child and cannot be split up.
// The unfairness of a distribution is defined as the maximum total cookies
// obtained by a single child in the distribution. Return the minimum unfairness
// of all distributions.
//
//

LEETCODE_BEGIN_RESOLVING(2305, FairDistributionOfCookies, Solution);

class Solution {
public:
  int distributeCookies(vector<int> &cookies, int k) {
    int         res = numeric_limits<int>::max();
    vector<int> tmp(k);
    solve(0, cookies, tmp, k, res);
    return res;
  }

private:
  void solve(int beg, vector<int> &cookies, vector<int> &tmp, int k, int &res) {
    int n = cookies.size();
    if (beg == n) {
      res = min(res, *max_element(tmp.begin(), tmp.end()));
      return;
    }

    for (int i = 0; i < k; ++i) {
      tmp[i] += cookies[beg];
      solve(beg + 1, cookies, tmp, k, res);
      tmp[i] -= cookies[beg];
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= cookies.length <= 8|
// * |1 <= cookies[i] <= 10⁵|
// * |2 <= k <= cookies.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: cookies = [8,15,10,20,8], k = 2
// Output: 31
//
// One optimal distribution is [8,15,8] and [10,20]
// - The 1ˢᵗ child receives [8,15,8] which has a total of 8 + 15 + 8 = 31
// cookies.
// - The 2ⁿᵈ child receives [10,20] which has a total of 10 + 20 = 30 cookies.
// The unfairness of the distribution is max(31,30) = 31.
// It can be shown that there is no distribution with an unfairness less
// than 31.

LEETCODE_SOLUTION_UNITTEST(2305, FairDistributionOfCookies, example_1) {
  auto        solution = MakeSolution();
  vector<int> cookies  = {8, 15, 10, 20, 8};
  int         k        = 2;
  int         expect   = 31;
  int         actual   = solution->distributeCookies(cookies, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: cookies = [6,1,3,2,2,4,1,2], k = 3
// Output: 7
//
// One optimal distribution is [6,1], [3,2,2], and [4,1,2]
// - The 1ˢᵗ child receives [6,1] which has a total of 6 + 1 = 7 cookies.
// - The 2ⁿᵈ child receives [3,2,2] which has a total of 3 + 2 + 2 = 7 cookies.
// - The 3ʳᵈ child receives [4,1,2] which has a total of 4 + 1 + 2 = 7 cookies.
// The unfairness of the distribution is max(7,7,7) = 7.
// It can be shown that there is no distribution with an unfairness less than 7.

LEETCODE_SOLUTION_UNITTEST(2305, FairDistributionOfCookies, example_2) {
  auto        solution = MakeSolution();
  vector<int> cookies  = {6, 1, 3, 2, 2, 4, 1, 2};
  int         k        = 3;
  int         expect   = 7;
  int         actual   = solution->distributeCookies(cookies, k);
  LCD_EXPECT_EQ(expect, actual);
}
