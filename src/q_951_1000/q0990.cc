// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Satisfiability of Equality Equations
//
// https://leetcode.com/problems/satisfiability-of-equality-equations/
//
// Question ID: 990
// Difficult  : Medium
// Solve Date : 2022/09/26 17:37

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |990. Satisfiability of Equality Equations|:
//
// You are given an array of strings |equations| that represent relationships
// between variables where each string |equations[i]| is of length |4| and takes
// one of two different forms: |"xᵢ==yᵢ"| or |"xᵢ!=yᵢ"|.Here, |xᵢ| and |yᵢ| are
// lowercase letters (not necessarily different) that represent one-letter
// variable names. Return |true| if it is possible to assign integers to
// variable names so as to satisfy all the given equations, or |false|
// otherwise.
//

LEETCODE_BEGIN_RESOLVING(990, SatisfiabilityOfEqualityEquations, Solution);

class Solution {
private:
  int union_find(vector<int> &u, int x) {
    return u[x] == -1 || u[x] == x ? x : union_find(u, u[x]);
  }

public:
  bool equationsPossible(vector<string> &equations) {
    auto mp = vector<int>(127, -1);
    for (auto &s : equations) {
      if (s[1] == '=') {
        mp[union_find(mp, s[0])] = union_find(mp, s[3]);
      }
    }
    for (auto &s : equations) {
      if (s[1] == '!' && union_find(mp, s[0]) == union_find(mp, s[3])) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= equations.length <= 500|
// * |equations[i].length == 4|
// * |equations[i][0]| is a lowercase letter.
// * |equations[i][1]| is either |'='| or |'!'|.
// * |equations[i][2]| is |'='|.
// * |equations[i][3]| is a lowercase letter.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: equations = ["a==b","b!=a"]
// Output: false
//
// If we assign say, a = 1 and b = 1, then the first equation is satisfied, but
// not the second. There is no way to assign the variables to satisfy both
// equations.

LEETCODE_SOLUTION_UNITTEST(990, SatisfiabilityOfEqualityEquations, example_1) {
  auto           solution  = MakeSolution();
  vector<string> equations = {"a==b", "b!=a"};
  bool           expect    = false;
  bool           actual    = solution->equationsPossible(equations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: equations = ["b==a","a==b"]
// Output: true
//
// We could assign a = 1 and b = 1 to satisfy both equations.

LEETCODE_SOLUTION_UNITTEST(990, SatisfiabilityOfEqualityEquations, example_2) {
  auto           solution  = MakeSolution();
  vector<string> equations = {"b==a", "a==b"};
  bool           expect    = true;
  bool           actual    = solution->equationsPossible(equations);
  LCD_EXPECT_EQ(expect, actual);
}
