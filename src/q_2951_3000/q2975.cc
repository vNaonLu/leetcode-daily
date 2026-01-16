// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Maximum Square Area by Removing Fences From a Field
//
// https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/
//
// Question ID: 2975
// Difficult  : Medium
// Solve Date : 2026/01/16 19:06

#include <algorithm>
#include <cmath>
#include <iosfwd>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2975. Maximum Square Area by Removing Fences From a Field|:
//
// There is a large |(m - 1) x (n - 1)| rectangular field with corners at |(1,
// 1)| and |(m, n)| containing some horizontal and vertical fences given in
// arrays |hFences| and |vFences| respectively. Horizontal fences are from the
// coordinates |(hFences[i], 1)| to |(hFences[i], n)| and vertical fences are
// from the coordinates |(1, vFences[i])| to |(m, vFences[i])|. Return the
// maximum area of a square field that can be formed by removing some fences
// (possibly none) or |-1| if it is impossible to make a square field. Since the
// answer may be large, return it modulo |10^{9 }+ 7|. Note: The field is
// surrounded by two horizontal fences from the coordinates |(1, 1)| to |(1, n)|
// and |(m, 1)| to |(m, n)| and two vertical fences from the coordinates |(1,
// 1)| to |(m, 1)| and |(1, n)| to |(m, n)|. These fences cannot be removed.
//
//

LEETCODE_BEGIN_RESOLVING(2975, MaximumSquareAreaByRemovingFencesFromAField,
                         Solution);

class Solution {
public:
  int maximizeSquareArea(int m, int n, vector<int> &hFences,
                         vector<int> &vFences) {
    hFences.push_back(1);
    hFences.push_back(m);
    vFences.push_back(1);
    vFences.push_back(n);

    unordered_set<int> stt;
    long long          ans = 0;

    for (int i = 0; i < hFences.size(); i++) {
      for (int j = i + 1; j < hFences.size(); j++) {
        stt.insert(abs(hFences[j] - hFences[i]));
      }
    }

    for (int i = 0; i < vFences.size(); i++) {
      for (int j = i + 1; j < vFences.size(); j++) {
        int val = abs(vFences[j] - vFences[i]);
        if (stt.count(val)) {
          ans = max(ans, (long long)val);
        }
      }
    }

    if (ans == 0) {
      return -1;
    }

    long long MOD = 1e9 + 7;
    return (ans * ans) % MOD;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= m, n <= 10⁹|
// * |1 <= hFences.length, vFences.length <= 600|
// * |1 < hFences[i] < m|
// * |1 < vFences[i] < n|
// * |hFences| and |vFences| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2975, MaximumSquareAreaByRemovingFencesFromAField,
                           example_1) {
  auto        solution = MakeSolution();
  int         m        = 4;
  int         n        = 3;
  vector<int> hFences  = {2, 3};
  vector<int> vFences  = {2};
  int         expect   = 4;
  int         actual   = solution->maximizeSquareArea(m, n, hFences, vFences);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: m = 6, n = 7, hFences = [2], vFences = [4]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2975, MaximumSquareAreaByRemovingFencesFromAField,
                           example_2) {
  auto        solution = MakeSolution();
  int         m        = 6;
  int         n        = 7;
  vector<int> hFences  = {2};
  vector<int> vFences  = {4};
  int         expect   = -1;
  int         actual   = solution->maximizeSquareArea(m, n, hFences, vFences);
  LCD_EXPECT_EQ(expect, actual);
}
