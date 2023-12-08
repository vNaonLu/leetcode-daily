// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Maximum Divisibility Score
//
// https://leetcode.com/problems/find-the-maximum-divisibility-score/
//
// Question ID: 2644
// Difficult  : Easy
// Solve Date : 2023/12/08 20:18

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2644. Find the Maximum Divisibility Score|:
//
// You are given two 0-indexed integer arrays |nums| and |divisors|.
// The divisibility score of |divisors[i]| is the number of indices |j| such
// that |nums[j]| is divisible by |divisors[i]|. Return the integer
// |divisors[i]| with the maximum divisibility score. If there is more than one
// integer with the maximum score, return the minimum of them.
//
//

LEETCODE_BEGIN_RESOLVING(2644, FindTheMaximumDivisibilityScore, Solution);

class Solution {
public:
  int maxDivScore(vector<int> &nums, vector<int> &divisors) {
    set<int> memo;
    int      res = 1e9;
    int      sc  = 0;
    for (auto x : divisors) {
      if (memo.emplace(x).second) {
        int local = score(nums, x);
        if (local > sc || (local == sc && x < res)) {
          sc  = local;
          res = x;
        }
      }
    }
    return res;
  }

private:
  int score(vector<int> const &v, int x) {
    int res = 0;
    for (auto c : v) {
      if (c % x == 0) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length, divisors.length <= 1000|
// * |1 <= nums[i], divisors[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,7,9,3,9], divisors = [5,2,3]
// Output: 3
//
// The divisibility score for every element in divisors is:
// The divisibility score of divisors[0] is 0 since no number in nums is
// divisible by 5. The divisibility score of divisors[1] is 1 since nums[0] is
// divisible by 2. The divisibility score of divisors[2] is 3 since nums[2],
// nums[3], and nums[4] are divisible by 3. Since divisors[2] has the maximum
// divisibility score, we return it.

LEETCODE_SOLUTION_UNITTEST(2644, FindTheMaximumDivisibilityScore, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 7, 9, 3, 9};
  vector<int> divisors = {5, 2, 3};
  int         expect   = 3;
  int         actual   = solution->maxDivScore(nums, divisors);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [20,14,21,10], divisors = [5,7,5]
// Output: 5
//
// The divisibility score for every element in divisors is:
// The divisibility score of divisors[0] is 2 since nums[0] and nums[3] are
// divisible by 5. The divisibility score of divisors[1] is 2 since nums[1] and
// nums[2] are divisible by 7. The divisibility score of divisors[2] is 2 since
// nums[0] and nums[3] are divisible by 5. Since divisors[0], divisors[1], and
// divisors[2] all have the maximum divisibility score, we return the minimum of
// them (i.e., divisors[2]).

LEETCODE_SOLUTION_UNITTEST(2644, FindTheMaximumDivisibilityScore, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {20, 14, 21, 10};
  vector<int> divisors = {5, 7, 5};
  int         expect   = 5;
  int         actual   = solution->maxDivScore(nums, divisors);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [12], divisors = [10,16]
// Output: 10
//
// The divisibility score for every element in divisors is:
// The divisibility score of divisors[0] is 0 since no number in nums is
// divisible by 10. The divisibility score of divisors[1] is 0 since no number
// in nums is divisible by 16. Since divisors[0] and divisors[1] both have the
// maximum divisibility score, we return the minimum of them (i.e.,
// divisors[0]).

LEETCODE_SOLUTION_UNITTEST(2644, FindTheMaximumDivisibilityScore, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {12};
  vector<int> divisors = {10, 16};
  int         expect   = 10;
  int         actual   = solution->maxDivScore(nums, divisors);
  LCD_EXPECT_EQ(expect, actual);
}
