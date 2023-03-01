// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum XOR of Two Numbers in an Array
//
// https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
//
// Question ID: 421
// Difficult  : Medium
// Solve Date : 2022/01/27 18:12

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |421. Maximum XOR of Two Numbers in an Array|:
//
// Given an integer array |nums|, return the maximum result of |nums[i] XOR
// nums[j]|, where |0 <= i <= j < n|.  
//

LEETCODE_BEGIN_RESOLVING(421, MaximumXOROfTwoNumbersInAnArray, Solution);

class Solution {
public:
  int findMaximumXOR(vector<int> &nums) {
    uint32_t           it  = 1 << 31;
    int                res = 0, mask = 0;
    unordered_set<int> mp;
    while (it != 0) {
      int tmp = res | it;
      mask |= it;
      for (const auto &n : nums) {
        int num = n & tmp;
        if (mp.count(tmp ^ num)) {
          res = tmp;
          break;
        }
        mp.insert(num);
      }
      mp.clear();
      it >>= 1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁵|
// * |0 <= nums[i] <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,10,5,25,2,8]
// Output: 28
//
// The maximum result is 5 XOR 25 = 28.

LEETCODE_SOLUTION_UNITTEST(421, MaximumXOROfTwoNumbersInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 10, 5, 25, 2, 8};
  int         expect   = 28;
  int         actual   = solution->findMaximumXOR(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
// Output: 127
//

LEETCODE_SOLUTION_UNITTEST(421, MaximumXOROfTwoNumbersInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};
  int         expect   = 127;
  int         actual   = solution->findMaximumXOR(nums);
  LCD_EXPECT_EQ(expect, actual);
}
