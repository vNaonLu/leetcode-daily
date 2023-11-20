// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Amount of Time to Collect Garbage
//
// https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/
//
// Question ID: 2391
// Difficult  : Medium
// Solve Date : 2023/11/20 20:08

#include <iosfwd>
#include <numeric>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2391. Minimum Amount of Time to Collect Garbage|:
//
// You are given a 0-indexed array of strings |garbage| where |garbage[i]|
// represents the assortment of garbage at the |iᵗʰ| house. |garbage[i]|
// consists only of the characters |'M'|, |'P'| and |'G'| representing one unit
// of metal, paper and glass garbage respectively. Picking up one unit of any
// type of garbage takes |1| minute. You are also given a 0-indexed integer
// array |travel| where |travel[i]| is the number of minutes needed to go from
// house |i| to house |i + 1|. There are three garbage trucks in the city, each
// responsible for picking up one type of garbage. Each garbage truck starts at
// house |0| and must visit each house in order; however, they do not need to
// visit every house. Only one garbage truck may be used at any given moment.
// While one truck is driving or picking up garbage, the other two trucks cannot
// do anything. Return the minimum number of minutes needed to pick up all the
// garbage.
//
//

LEETCODE_BEGIN_RESOLVING(2391, MinimumAmountOfTimeToCollectGarbage, Solution);

class Solution {
public:
  int garbageCollection(vector<string> &garbage, vector<int> &travel) {
    int n  = garbage.size();
    int lp = -1;
    int lm = -1;
    int lg = -1;

    for (int i = n - 1; i >= 0; --i) {
      if (lm == -1 && garbage[i].find("M") != string::npos) {
        lm = i;
      }
      if (lp == -1 && garbage[i].find("P") != string::npos) {
        lp = i;
      }
      if (lg == -1 && garbage[i].find("G") != string::npos) {
        lg = i;
      }

      if (lm != -1 && lp != -1 && lg != -1) {
        break;
      }
    }

    int res = 0;
    for (auto &g : garbage) {
      res += g.size();
    }

    if (lm != -1) {
      res = accumulate(travel.begin(), travel.begin() + lm, res);
    }
    if (lp != -1) {
      res = accumulate(travel.begin(), travel.begin() + lp, res);
    }
    if (lg != -1) {
      res = accumulate(travel.begin(), travel.begin() + lg, res);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= garbage.length <= 10⁵|
// * |garbage[i]| consists of only the letters |'M'|, |'P'|, and |'G'|.
// * |1 <= garbage[i].length <= 10|
// * |travel.length == garbage.length - 1|
// * |1 <= travel[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
// Output: 21
//
// The paper garbage truck:
// 1. Travels from house 0 to house 1
// 2. Collects the paper garbage at house 1
// 3. Travels from house 1 to house 2
// 4. Collects the paper garbage at house 2
// Altogether, it takes 8 minutes to pick up all the paper garbage.
// The glass garbage truck:
// 1. Collects the glass garbage at house 0
// 2. Travels from house 0 to house 1
// 3. Travels from house 1 to house 2
// 4. Collects the glass garbage at house 2
// 5. Travels from house 2 to house 3
// 6. Collects the glass garbage at house 3
// Altogether, it takes 13 minutes to pick up all the glass garbage.
// Since there is no metal garbage, we do not need to consider the metal garbage
// truck. Therefore, it takes a total of 8 + 13 = 21 minutes to collect all the
// garbage.

LEETCODE_SOLUTION_UNITTEST(2391, MinimumAmountOfTimeToCollectGarbage,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> garbage  = {"G", "P", "GP", "GG"};
  vector<int>    travel   = {2, 4, 3};
  int            expect   = 21;
  int            actual   = solution->garbageCollection(garbage, travel);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: garbage = ["MMM","PGM","GP"], travel = [3,10]
// Output: 37
//
// The metal garbage truck takes 7 minutes to pick up all the metal garbage.
// The paper garbage truck takes 15 minutes to pick up all the paper garbage.
// The glass garbage truck takes 15 minutes to pick up all the glass garbage.
// It takes a total of 7 + 15 + 15 = 37 minutes to collect all the garbage.

LEETCODE_SOLUTION_UNITTEST(2391, MinimumAmountOfTimeToCollectGarbage,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> garbage  = {"MMM", "PGM", "GP"};
  vector<int>    travel   = {3, 10};
  int            expect   = 37;
  int            actual   = solution->garbageCollection(garbage, travel);
  LCD_EXPECT_EQ(expect, actual);
}
