// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Even Numbers After Queries
//
// https://leetcode.com/problems/sum-of-even-numbers-after-queries/
//
// Question ID: 985
// Difficult  : Medium
// Solve Date : 2022/09/21 22:10

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |985. Sum of Even Numbers After Queries|:
//
// You are given an integer array |nums| and an array |queries| where
// |queries[i] = [valᵢ, indexᵢ]|. For each query |i|, first, apply |nums[indexᵢ]
// = nums[indexᵢ] + valᵢ|, then print the sum of the even values of |nums|.
// Return an integer array |answer| where |answer[i]| is the answer to the |iᵗʰ|
// query.
//

LEETCODE_BEGIN_RESOLVING(985, SumOfEvenNumbersAfterQueries, Solution);

class Solution {
public:
  vector<int> sumEvenAfterQueries(vector<int>         &nums,
                                  vector<vector<int>> &queries) {
    auto res    = vector<int>(queries.size());
    res.front() = accumulate(nums.begin(), nums.end(), 0, [](auto x, auto y) {
      return x + ((y & 1) == 0 ? y : 0);
    });
    for (int i = 0; i < queries.size(); ++i) {
      auto &v   = queries[i];
      auto &tag = nums[v[1]];
      if (i != 0) {
        res[i] = res[i - 1];
      }
      if ((tag & 1) == 0) {
        res[i] -= tag;
      }

      tag += v[0];
      if ((tag & 1) == 0) {
        res[i] += tag;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁴ <= nums[i] <= 10⁴|
// * |1 <= queries.length <= 10⁴|
// * |-10⁴ <= valᵢ <= 10⁴|
// * |0 <= indexᵢ < nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
// Output: [8,6,2,4]
//
// At the beginning, the array is [1,2,3,4].
// After adding 1 to nums[0], the array is [2,2,3,4], and the sum of even values
// is 2 + 2 + 4 = 8. After adding -3 to nums[1], the array is [2,-1,3,4], and
// the sum of even values is 2 + 4 = 6. After adding -4 to nums[0], the array is
// [-2,-1,3,4], and the sum of even values is -2 + 4 = 2. After adding 2 to
// nums[3], the array is [-2,-1,3,6], and the sum of even values is -2 + 6 = 4.

LEETCODE_SOLUTION_UNITTEST(985, SumOfEvenNumbersAfterQueries, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 2, 3, 4};
  vector<vector<int>> queries  = {
      { 1, 0},
      {-3, 1},
      {-4, 0},
      { 2, 3}
  };
  vector<int> expect = {8, 6, 2, 4};
  vector<int> actual = solution->sumEvenAfterQueries(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1], queries = [[4,0]]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(985, SumOfEvenNumbersAfterQueries, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1};
  vector<vector<int>> queries  = {
      {4, 0}
  };
  vector<int> expect = {0};
  vector<int> actual = solution->sumEvenAfterQueries(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}
