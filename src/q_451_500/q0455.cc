// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Assign Cookies
//
// https://leetcode.com/problems/assign-cookies/
//
// Question ID: 455
// Difficult  : Easy
// Solve Date : 2022/10/01 12:12

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |455. Assign Cookies|:
//
// Assume you are an awesome parent and want to give your children some cookies.
// But, you should give each child at most one cookie. Each child |i| has a
// greed factor |g[i]|, which is the minimum size of a cookie that the child
// will be content with; and each cookie |j| has a size |s[j]|. If |s[j] >=
// g[i]|, we can assign the cookie |j| to the child |i|, and the child |i| will
// be content. Your goal is to maximize the number of your content children and
// output the maximum number.
//

LEETCODE_BEGIN_RESOLVING(455, AssignCookies, Solution);

class Solution {
public:
  int findContentChildren(vector<int> &g, vector<int> &s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    auto gbeg = g.begin();
    auto sbeg = s.begin();
    auto res  = (int)0;
    while (gbeg != g.end() && sbeg != s.end()) {
      if (*sbeg >= *gbeg) {
        ++sbeg;
        ++gbeg;
        ++res;
      } else if (*gbeg > *sbeg) {
        ++sbeg;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= g.length <= 3 * 10⁴|
// * |0 <= s.length <= 3 * 10⁴|
// * |1 <= g[i], s[j] <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: g = [1,2,3], s = [1,1]
// Output: 1
//
// You have 3 children and 2 cookies. The greed factors of 3 children are 1,
// 2, 3. And even though you have 2 cookies, since their size is both 1, you
// could only make the child whose greed factor is 1 content. You need to
// output 1.

LEETCODE_SOLUTION_UNITTEST(455, AssignCookies, example_1) {
  auto        solution = MakeSolution();
  vector<int> g        = {1, 2, 3};
  vector<int> s        = {1, 1};
  int         expect   = 1;
  int         actual   = solution->findContentChildren(g, s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: g = [1,2], s = [1,2,3]
// Output: 2
//
// You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
// You have 3 cookies and their sizes are big enough to gratify all of the
// children, You need to output 2.

LEETCODE_SOLUTION_UNITTEST(455, AssignCookies, example_2) {
  auto        solution = MakeSolution();
  vector<int> g        = {1, 2};
  vector<int> s        = {1, 2, 3};
  int         expect   = 2;
  int         actual   = solution->findContentChildren(g, s);
  LCD_EXPECT_EQ(expect, actual);
}
