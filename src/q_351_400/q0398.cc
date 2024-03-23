// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Random Pick Index
//
// https://leetcode.com/problems/random-pick-index/
//
// Question ID: 398
// Difficult  : Medium
// Solve Date : 2024/03/23 08:16

#include <algorithm>
#include <iosfwd>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |398. Random Pick Index|:
//
// Given an integer array |nums| with possible duplicates, randomly output the
// index of a given |target| number. You can assume that the given target number
// must exist in the array. Implement the |Solution| class:
//
//  • |Solution(int[] nums)| Initializes the object with the array |nums|.
//
//  • |int pick(int target)| Picks a random index |i| from |nums| where |nums[i]
//  == target|. If there are multiple valid i's, then each index should have an
//  equal probability of returning.
//
//

LEETCODE_BEGIN_RESOLVING(398, RandomPickIndex, Solution);

class Solution {
public:
  Solution(vector<int> &nums) {
    for (int i = 0; i < nums.size(); ++i) {
      idx_[nums[i]].emplace_back(i);
    }
  }

  int pick(int target) {
    int                        n = idx_[target].size();
    random_device              rd;
    mt19937                    rng(rd());
    uniform_int_distribution<> d(0, n - 1);
    return idx_[target][d(rng)];
  }

private:
  unordered_map<int, vector<int>> idx_;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁴|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
// * |target| is an integer from |nums|.
// * At most |10⁴| calls will be made to |pick|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Solution", "pick", "pick", "pick"]
// [[[1, 2, 3, 3, 3]], [3], [1], [3]]
// Output: [null, 4, 0, 2]
//

LEETCODE_SOLUTION_UNITTEST(398, RandomPickIndex, example_1) {
  vector<int>        s0_nums   = {1, 2, 3, 3, 3};
  auto               solution  = MakeSolution(s0_nums);
  int                s1_target = 3;
  unordered_set<int> s1_expect;
  s1_expect.emplace(2);
  s1_expect.emplace(3);
  s1_expect.emplace(4);
  int s1_actual = solution->pick(s1_target);
  EXPECT_TRUE(s1_expect.count(s1_actual));
  int s2_target = 1;
  int s2_expect = 0;
  int s2_actual = solution->pick(s2_target);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_target = 3;
  int s3_actual = solution->pick(s3_target);
  EXPECT_TRUE(s1_expect.count(s3_actual));
}
