// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Town Judge
//
// https://leetcode.com/problems/find-the-town-judge/
//
// Question ID: 997
// Difficult  : Easy
// Solve Date : 2021/10/07 10:11

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |997. Find the Town Judge|:
//
// In a town, there are |n| people labeled from |1| to |n|. There is a rumor
// that one of these people is secretly the town judge. If the town judge
// exists, then:
//
//  1. The town judge trusts nobody.
//
//  2. Everybody (except for the town judge) trusts the town judge.
//
//  3. There is exactly one person that satisfies properties 1 and 2.
// You are given an array |trust| where |trust[i] = [aᵢ, bᵢ]| representing that
// the person labeled |aᵢ| trusts the person labeled |bᵢ|. If a trust
// relationship does not exist in |trust| array, then such a trust relationship
// does not exist. Return the label of the town judge if the town judge exists
// and can be identified, or return |-1| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(997, FindTheTownJudge, Solution);

class Solution {
public:
  int findJudge(int n, vector<vector<int>> &trust) {
    vector<pair<int, int>> trust_map(n, make_pair(0, 0));
    for (const auto &t : trust) {
      ++trust_map[t[0] - 1].first;
      ++trust_map[t[1] - 1].second;
    }
    for (int i = 0; i < trust_map.size(); ++i)
      if (trust_map[i].first == 0 && trust_map[i].second == n - 1)
        return i + 1;
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
// * |0 <= trust.length <= 10⁴|
// * |trust[i].length == 2|
// * All the pairs of |trust| are unique.
// * |aᵢ != bᵢ|
// * |1 <= aᵢ, bᵢ <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2, trust = [[1,2]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(997, FindTheTownJudge, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 2;
  vector<vector<int>> trust    = {
      {1, 2}
  };
  int expect = 2;
  int actual = solution->findJudge(n, trust);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, trust = [[1,3],[2,3]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(997, FindTheTownJudge, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> trust    = {
      {1, 3},
      {2, 3}
  };
  int expect = 3;
  int actual = solution->findJudge(n, trust);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3, trust = [[1,3],[2,3],[3,1]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(997, FindTheTownJudge, example_3) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> trust    = {
      {1, 3},
      {2, 3},
      {3, 1}
  };
  int expect = -1;
  int actual = solution->findJudge(n, trust);
  LCD_EXPECT_EQ(expect, actual);
}
