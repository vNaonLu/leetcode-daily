// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Prime Subtraction Operation
//
// https://leetcode.com/problems/prime-subtraction-operation/
//
// Question ID: 2601
// Difficult  : Medium
// Solve Date : 2024/11/11 20:17

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2601. Prime Subtraction Operation|:
//
// You are given a 0-indexed integer array |nums| of length |n|.
// You can perform the following operation as many times as you want:
//
//  • Pick an index |i| that you haven’t picked before, and pick a prime |p|
//  strictly less than |nums[i]|, then subtract |p| from |nums[i]|.
// Return true if you can make |nums| a strictly increasing array using the
// above operation and false otherwise. A strictly increasing array is an array
// whose each element is strictly greater than its preceding element.
//
//

LEETCODE_BEGIN_RESOLVING(2601, PrimeSubtractionOperation, Solution);

class Solution {
public:
  bool primeSubOperation(vector<int> &nums) {
    int  n     = nums.size();
    auto prime = sieve();
    for (int i = n - 2; i >= 0; --i) {
      if (nums[i] < nums[i + 1]) {
        continue;
      }

      int  diff = nums[i] - nums[i + 1];
      auto it   = upper_bound(prime.begin(), prime.end(), diff);
      if (it == prime.end() || *it >= nums[i]) {
        return false;
      }

      nums[i] -= *it;
    }
    return true;
  }

private:
  vector<int> sieve() {
    vector<int> prime;
    vector<int> isp(1002, 1);
    isp[0] = 0;
    for (int i = 2; i < 1002; ++i) {
      if (isp[i]) {
        prime.emplace_back(i);
        for (int j = i * i; j < 1002; j += i) {
          isp[j] = 0;
        }
      }
    }
    return prime;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 1000|
// * |nums.length == n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,9,6,10]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2601, PrimeSubtractionOperation, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 9, 6, 10};
  bool        expect   = true;
  bool        actual   = solution->primeSubOperation(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [6,8,11,12]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2601, PrimeSubtractionOperation, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 8, 11, 12};
  bool        expect   = true;
  bool        actual   = solution->primeSubOperation(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [5,8,3]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(2601, PrimeSubtractionOperation, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 8, 3};
  bool        expect   = false;
  bool        actual   = solution->primeSubOperation(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [998,2]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2601, PrimeSubtractionOperation, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {998, 2};
  bool        expect   = true;
  bool        actual   = solution->primeSubOperation(nums);
  LCD_EXPECT_EQ(expect, actual);
}
