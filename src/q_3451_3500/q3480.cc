// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximize Subarrays After Removing One Conflicting Pair
//
// https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/
//
// Question ID: 3480
// Difficult  : Hard
// Solve Date : 2025/07/26 14:26

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3480. Maximize Subarrays After Removing One Conflicting
// Pair|:
//
// You are given an integer |n| which represents an array |nums| containing the
// numbers from 1 to |n| in order. Additionally, you are given a 2D array
// |conflictingPairs|, where |conflictingPairs[i] = [a, b]| indicates that |a|
// and |b| form a conflicting pair. Remove exactly one element from
// |conflictingPairs|. Afterward, count the number of non-empty subarrays of
// |nums| which do not contain both |a| and |b| for any remaining conflicting
// pair |[a, b]|. Return the maximum number of subarrays possible after removing
// exactly one conflicting pair.
//
//

LEETCODE_BEGIN_RESOLVING(3480, MaximizeSubarraysAfterRemovingOneConflictingPair,
                         Solution);

class Solution {
public:
  long long maxSubarrays(int n, vector<vector<int>> &conflictingPairs) {
    vector<vector<int>> right(n + 1);
    for (const auto &pair : conflictingPairs) {
      right[max(pair[0], pair[1])].push_back(min(pair[0], pair[1]));
    }

    long long         ans  = 0;
    vector<long long> left = {0, 0};
    vector<long long> bonus(n + 1, 0);

    for (int r = 1; r <= n; ++r) {
      for (int l_val : right[r]) {
        if (l_val > left[0]) {
          left = {static_cast<long long>(l_val), left[0]};
        } else if (l_val > left[1]) {
          left = {left[0], static_cast<long long>(l_val)};
        }
      }

      ans += r - left[0];

      if (left[0] > 0) {
        bonus[left[0]] += left[0] - left[1];
      }
    }

    long long max_bonus = 0;
    for (long long b : bonus) {
      max_bonus = max(max_bonus, b);
    }

    return ans + max_bonus;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |1 <= conflictingPairs.length <= 2 * n|
// * |conflictingPairs[i].length == 2|
// * |1 <= conflictingPairs[i][j] <= n|
// * |conflictingPairs[i][0] != conflictingPairs[i][1]|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, conflictingPairs = [[2,3],[1,4]]
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(3480,
                           MaximizeSubarraysAfterRemovingOneConflictingPair,
                           example_1) {
  auto                solution         = MakeSolution();
  int                 n                = 4;
  vector<vector<int>> conflictingPairs = {
      {2, 3},
      {1, 4}
  };
  long long expect = 9;
  long long actual = solution->maxSubarrays(n, conflictingPairs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, conflictingPairs = [[1,2],[2,5],[3,5]]
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(3480,
                           MaximizeSubarraysAfterRemovingOneConflictingPair,
                           example_2) {
  auto                solution         = MakeSolution();
  int                 n                = 5;
  vector<vector<int>> conflictingPairs = {
      {1, 2},
      {2, 5},
      {3, 5}
  };
  long long expect = 12;
  long long actual = solution->maxSubarrays(n, conflictingPairs);
  LCD_EXPECT_EQ(expect, actual);
}
