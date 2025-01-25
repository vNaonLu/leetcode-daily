// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Make Lexicographically Smallest Array by Swapping Elements
//
// https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/
//
// Question ID: 2948
// Difficult  : Medium
// Solve Date : 2025/01/25 09:13

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2948. Make Lexicographically Smallest Array by Swapping
// Elements|:
//
// You are given a 0-indexed array of positive integers |nums| and a positive
// integer |limit|. In one operation, you can choose any two indices |i| and |j|
// and swap |nums[i]| and |nums[j]| if ||nums[i] - nums[j]| <= limit|. Return
// the lexicographically smallest array that can be obtained by performing the
// operation any number of times. An array |a| is lexicographically smaller than
// an array |b| if in the first position where |a| and |b| differ, array |a| has
// an element that is less than the corresponding element in |b|. For example,
// the array |[2,10,3]| is lexicographically smaller than the array |[10,2,3]|
// because they differ at index |0| and |2 < 10|.
//
//

LEETCODE_BEGIN_RESOLVING(2948,
                         MakeLexicographicallySmallestArrayBySwappingElements,
                         Solution);

class Solution {
public:
  vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit) {
    vector<pair<int, int>> b;
    int                    n = nums.size();
    for (int i = 0; i < n; ++i) {
      b.emplace_back(nums[i], i);
    }
    sort(b.begin(), b.end(),
         [](auto &a, auto &b) { return a.first < b.first; });

    vector<vector<pair<int, int>>> c = {{b[0]}};

    for (int i = 1; i < n; ++i) {
      if (b[i].first - b[i - 1].first <= limit) {
        c.back().emplace_back(b[i]);
      } else {
        c.push_back({b[i]});
      }
    }

    for (auto const &t : c) {
      vector<int> ind;
      for (auto const &p : t) {
        ind.emplace_back(p.second);
      }
      sort(ind.begin(), ind.end());

      for (int i = 0; i < ind.size(); ++i) {
        nums[ind[i]] = t[i].first;
      }
    }
    return nums;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= limit <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,5,3,9,8], limit = 2
// Output: [1,3,5,8,9]
//

LEETCODE_SOLUTION_UNITTEST(2948,
                           MakeLexicographicallySmallestArrayBySwappingElements,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 3, 9, 8};
  int         limit    = 2;
  vector<int> expect   = {1, 3, 5, 8, 9};
  vector<int> actual   = solution->lexicographicallySmallestArray(nums, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,7,6,18,2,1], limit = 3
// Output: [1,6,7,18,1,2]
//

LEETCODE_SOLUTION_UNITTEST(2948,
                           MakeLexicographicallySmallestArrayBySwappingElements,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 7, 6, 18, 2, 1};
  int         limit    = 3;
  vector<int> expect   = {1, 6, 7, 18, 1, 2};
  vector<int> actual   = solution->lexicographicallySmallestArray(nums, limit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,7,28,19,10], limit = 3
// Output: [1,7,28,19,10]
//

LEETCODE_SOLUTION_UNITTEST(2948,
                           MakeLexicographicallySmallestArrayBySwappingElements,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 7, 28, 19, 10};
  int         limit    = 3;
  vector<int> expect   = {1, 7, 28, 19, 10};
  vector<int> actual   = solution->lexicographicallySmallestArray(nums, limit);
  LCD_EXPECT_EQ(expect, actual);
}
