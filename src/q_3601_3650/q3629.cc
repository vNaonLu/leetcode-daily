// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Jumps to Reach End via Prime Teleportation
//
// https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/
//
// Question ID: 3629
// Difficult  : Medium
// Solve Date : 2026/05/08 19:15

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3629. Minimum Jumps to Reach End via Prime Teleportation|:
//
// You are given an integer array |nums| of length |n|.
// You start at index 0, and your goal is to reach index |n - 1|.
// From any index |i|, you may perform one of the following operations:
//
//  • Adjacent Step: Jump to index |i + 1| or |i - 1|, if the index is within
//  bounds.
//
//  • Prime Teleportation: If |nums[i]| is a prime number |p|, you may instantly
//  jump to any index |j != i| such that |nums[j] % p == 0|.
// Return the minimum number of jumps required to reach index |n - 1|.
//
//

LEETCODE_BEGIN_RESOLVING(3629, MinimumJumpsToReachEndViaPrimeTeleportation,
                         Solution);

class Solution {
public:
  int minJumps(vector<int> &nums) {
    int n  = nums.size();
    int mx = *max_element(nums.begin(), nums.end());

    vector<bool> prime(mx + 1, true);
    prime[0] = false;
    prime[1] = false;
    for (long long i = 2; i <= mx; i++) {
      if (prime[i]) {
        for (long long j = i * i; j <= mx; j += i) {
          prime[j] = false;
        }
      }
    }

    vector<vector<int>> pos(mx + 1);
    for (int i = 0; i < n; i++) {
      pos[nums[i]].push_back(i);
    }

    queue<pair<int, int>> q;
    q.push({0, 0});
    vector<int> vis(n);
    vis[0] = 1;
    while (!q.empty()) {
      auto [i, t] = q.front();
      q.pop();

      if (i == n - 1)
        return t;

      if (i > 0 && !vis[i - 1]) {
        q.push({i - 1, t + 1});
        vis[i - 1] = 1;
      }
      if (i < n - 1 && !vis[i + 1]) {
        q.push({i + 1, t + 1});
        vis[i + 1] = 1;
      }

      if (prime[nums[i]]) {
        int p = nums[i];
        for (int m = p; m <= mx; m += p) {
          for (int j : pos[m]) {
            if (!vis[j]) {
              q.push({j, t + 1});
              vis[j] = 1;
            }
          }
          pos[m].clear();
        }
        prime[p] = false;
      }
    }
    return n - 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,4,6]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3629, MinimumJumpsToReachEndViaPrimeTeleportation,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 4, 6};
  int         expect   = 2;
  int         actual   = solution->minJumps(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,4,7,9]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3629, MinimumJumpsToReachEndViaPrimeTeleportation,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 4, 7, 9};
  int         expect   = 2;
  int         actual   = solution->minJumps(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [4,6,5,8]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3629, MinimumJumpsToReachEndViaPrimeTeleportation,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 6, 5, 8};
  int         expect   = 3;
  int         actual   = solution->minJumps(nums);
  LCD_EXPECT_EQ(expect, actual);
}
