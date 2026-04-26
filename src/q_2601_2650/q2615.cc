// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Sum of Distances
//
// https://leetcode.com/problems/sum-of-distances/
//
// Question ID: 2615
// Difficult  : Medium
// Solve Date : 2026/04/26 19:22

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2615. Sum of Distances|:
//
// You are given a 0-indexed integer array |nums|. There exists an array |arr|
// of length |nums.length|, where |arr[i]| is the sum of ||i - j|| over all |j|
// such that |nums[j] == nums[i]| and |j != i|. If there is no such |j|, set
// |arr[i]| to be |0|. Return the array |arr|.
//
//

LEETCODE_BEGIN_RESOLVING(2615, SumOfDistances, Solution);

class Solution {
public:
  vector<long long> distance(vector<int> &nums) {
    int                                   n = nums.size();
    vector<long long>                     res(n);
    unordered_map<long long, vector<int>> mp;

    for (int i = 0; i < n; i++) {
      mp[nums[i]].push_back(i);
    }

    for (auto &idx : mp) {
      auto &arr = idx.second;
      int   siz = arr.size();

      vector<long long> pref(siz, 0);
      pref[0] = arr[0];

      for (int i = 1; i < siz; i++) {
        pref[i] = pref[i - 1] + arr[i];
      }

      for (int i = 0; i < siz; i++) {
        long long left = 0, right = 0;

        if (i > 0) {
          left = (long long)i * arr[i] - pref[i - 1];
        }
        if (i < siz - 1) {
          right = (pref[siz - 1] - pref[i]) - (long long)(siz - i - 1) * arr[i];
        }
        res[arr[i]] = left + right;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,1,1,2]
// Output: [5,0,3,4,0]
//

LEETCODE_SOLUTION_UNITTEST(2615, SumOfDistances, example_1) {
  auto              solution = MakeSolution();
  vector<int>       nums     = {1, 3, 1, 1, 2};
  vector<long long> expect   = {5, 0, 3, 4, 0};
  vector<long long> actual   = solution->distance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,5,3]
// Output: [0,0,0]
//

LEETCODE_SOLUTION_UNITTEST(2615, SumOfDistances, example_2) {
  auto              solution = MakeSolution();
  vector<int>       nums     = {0, 5, 3};
  vector<long long> expect   = {0, 0, 0};
  vector<long long> actual   = solution->distance(nums);
  LCD_EXPECT_EQ(expect, actual);
}
