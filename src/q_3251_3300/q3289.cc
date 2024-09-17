// Copyright 2024 Naon Lu
//
// This file describes the solution of
// The Two Sneaky Numbers of Digitville
//
// https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville/
//
// Question ID: 3289
// Difficult  : Easy
// Solve Date : 2024/09/17 21:10

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3289. The Two Sneaky Numbers of Digitville|:
//
// In the town of Digitville, there was a list of numbers called |nums|
// containing integers from |0| to |n - 1|. Each number was supposed to appear
// exactly once in the list, however, two mischievous numbers sneaked in an
// additional time, making the list longer than usual. As the town detective,
// your task is to find these two sneaky numbers. Return an array of size two
// containing the two numbers (in any order), so peace can return to Digitville.
//
//

LEETCODE_BEGIN_RESOLVING(3289, TheTwoSneakyNumbersOfDigitville, Solution);

class Solution {
public:
  vector<int> getSneakyNumbers(vector<int> &nums) {
    vector<int>   res;
    map<int, int> memo;
    for (auto x : nums) {
      ++memo[x];
    }
    for (auto [x, c] : memo) {
      if (c == 2) {
        res.emplace_back(x);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

// [Example #1]
//  Input: nums = [0,1,1,0]
// Output: [0,1]
//

LEETCODE_SOLUTION_UNITTEST(3289, TheTwoSneakyNumbersOfDigitville, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 1, 0};
  vector<int> expect   = {0, 1};
  vector<int> actual   = solution->getSneakyNumbers(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,3,2,1,3,2]
// Output: [2,3]
//

LEETCODE_SOLUTION_UNITTEST(3289, TheTwoSneakyNumbersOfDigitville, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 3, 2, 1, 3, 2};
  vector<int> expect   = {2, 3};
  vector<int> actual   = solution->getSneakyNumbers(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [7,1,5,4,3,4,6,0,9,5,8,2]
// Output: [4,5]
//

LEETCODE_SOLUTION_UNITTEST(3289, TheTwoSneakyNumbersOfDigitville, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 1, 5, 4, 3, 4, 6, 0, 9, 5, 8, 2};
  vector<int> expect   = {4, 5};
  vector<int> actual   = solution->getSneakyNumbers(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}
