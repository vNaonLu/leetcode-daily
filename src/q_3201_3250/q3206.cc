// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Alternating Groups I
//
// https://leetcode.com/problems/alternating-groups-i/
//
// Question ID: 3206
// Difficult  : Easy
// Solve Date : 2024/07/07 12:56

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3206. Alternating Groups I|:
//
//

LEETCODE_BEGIN_RESOLVING(3206, AlternatingGroupsI, Solution);

class Solution {
public:
  int numberOfAlternatingGroups(vector<int> &colors) {
    int n = colors.size();
    if (n < 3) {
      return 0;
    }

    int res = 0;
    for (int i = 0; i < n - 2; ++i) {
      if (colors[i] == colors[i + 2] && colors[i] != colors[i + 1]) {
        ++res;
      }
    }

    if (colors[0] == colors[n - 2] && colors[0] != colors[n - 1]) {
      ++res;
    }

    if (colors[0] != colors[1] && colors[1] == colors[n - 1]) {
      ++res;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= colors.length <= 100|
// * |0 <= colors[i] <= 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: colors = [1,1,1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3206, AlternatingGroupsI, example_1) {
  auto        solution = MakeSolution();
  vector<int> colors   = {1, 1, 1};
  int         expect   = 0;
  int         actual   = solution->numberOfAlternatingGroups(colors);
  LCD_EXPECT_EQ(expect, actual);
}
