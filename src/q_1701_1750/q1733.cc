// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Number of People to Teach
//
// https://leetcode.com/problems/minimum-number-of-people-to-teach/
//
// Question ID: 1733
// Difficult  : Medium
// Solve Date : 2025/09/10 19:01

#include <bitset>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1733. Minimum Number of People to Teach|:
//
// On a social network consisting of |m| users and some friendships between
// users, two users can communicate with each other if they know a common
// language. You are given an integer |n|, an array |languages|, and an array
// |friendships| where:
//
//  • There are |n| languages numbered |1| through |n|,
//
//  • |languages[i]| is the set of languages the
//  |i^{​​​​​​th}|​​​​ user knows, and
//
//  • |friendships[i] = [u_{​​​​​​i}​​​,
//  v_{​​​​​​i}]| denotes a friendship between the users
//  |u^{​​​​​}_{​​​​​​i}|​​​​​ and |vᵢ|.
// You can choose one language and teach it to some users so that all friends
// can communicate with each other. Return the minimum number of users you need
// to teach. Note that friendships are not transitive, meaning if |x| is a
// friend of |y| and |y| is a friend of |z|, this doesn't guarantee that |x| is
// a friend of |z|.
//
//

LEETCODE_BEGIN_RESOLVING(1733, MinimumNumberOfPeopleToTeach, Solution);

class Solution {
public:
  int minimumTeachings(int n, vector<vector<int>> &languages,
                       vector<vector<int>> &friendships) {
    int                 m = languages.size();
    vector<bitset<501>> know(languages.size());
    for (int i = 0; i < m; ++i) {
      for (auto l : languages[i]) {
        know[i][l] = 1;
      }
    }

    bitset<501> need = 0;
    for (auto &v : friendships) {
      int a = v[0] - 1;
      int b = v[1] - 1;
      if ((know[a] & know[b]).any()) {
        continue;
      }
      need[a] = need[b] = 1;
    }

    if (need.count() == 0) {
      return 0;
    }

    int res = numeric_limits<int>::max();
    for (int l = 1; l <= n; ++l) {
      int cnt = 0;
      for (int i = 0; i < m; ++i) {
        if (need[i] & !know[i][l]) {
          ++cnt;
        }
      }
      res = min(res, cnt);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 500|
// * |languages.length == m|
// * |1 <= m <= 500|
// * |1 <= languages[i].length <= n|
// * |1 <= languages[i][j] <= n|
// * |1 <= u_{​​​​​​i} < v_{​​​​​​i} <=
// languages.length|
// * |1 <= friendships.length <= 500|
// * All tuples |(u_{​​​​​i, }v_{​​​​​​i})| are unique
// * |languages[i]| contains only unique values
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1733, MinimumNumberOfPeopleToTeach, example_1) {
  auto                solution  = MakeSolution();
  int                 n         = 2;
  vector<vector<int>> languages = {
      {1},
      {2},
      {1, 2}
  };
  vector<vector<int>> friendships = {
      {1, 2},
      {1, 3},
      {2, 3}
  };
  int expect = 1;
  int actual = solution->minimumTeachings(n, languages, friendships);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships =
//  [[1,4],[1,2],[3,4],[2,3]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1733, MinimumNumberOfPeopleToTeach, example_2) {
  auto                solution  = MakeSolution();
  int                 n         = 3;
  vector<vector<int>> languages = {
      {2},
      {1, 3},
      {1, 2},
      {3}
  };
  vector<vector<int>> friendships = {
      {1, 4},
      {1, 2},
      {3, 4},
      {2, 3}
  };
  int expect = 2;
  int actual = solution->minimumTeachings(n, languages, friendships);
  LCD_EXPECT_EQ(expect, actual);
}
