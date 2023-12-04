// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Array Concatenation Value
//
// https://leetcode.com/problems/find-the-array-concatenation-value/
//
// Question ID: 2562
// Difficult  : Easy
// Solve Date : 2023/12/01 21:40

#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2562. Find the Array Concatenation Value|:
//
// You are given a 0-indexed integer array |nums|.
// The concatenation of two numbers is the number formed by concatenating their
// numerals.
//
//  • For example, the concatenation of |15|, |49| is |1549|.
// The concatenation value of |nums| is initially equal to |0|. Perform this
// operation until |nums| becomes empty:
//
//  • If there exists more than one number in |nums|, pick the first element and
//  last element in |nums| respectively and add the value of their concatenation
//  to the concatenation value of |nums|, then delete the first and last element
//  from |nums|.
//
//  • If one element exists, add its value to the concatenation value of |nums|,
//  then delete it.
// Return the concatenation value of the |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(2562, FindTheArrayConcatenationValue, Solution);

class Solution {
public:
  long long findTheArrayConcVal(vector<int> &nums) {
    int64_t res = 0;
    int     i   = 0;
    int     j   = nums.size() - 1;
    while (i < j) {
      int64_t x   = nums[i++];
      int64_t y   = nums[j--];
      int64_t sum = x * pow(10, int(log10(y)) + 1) + y;
      res += sum;
    }
    res += i == j ? nums[i] : 0;
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [7,52,2,4]
// Output: 596
//
// Before performing any operation, nums is [7,52,2,4] and concatenation value
// is 0.
//  - In the first operation:
// We pick the first element, 7, and the last element, 4.
// Their concatenation is 74, and we add it to the concatenation value, so it
// becomes equal to 74. Then we delete them from nums, so nums becomes equal to
// [52,2].
//  - In the second operation:
// We pick the first element, 52, and the last element, 2.
// Their concatenation is 522, and we add it to the concatenation value, so it
// becomes equal to 596. Then we delete them from the nums, so nums becomes
// empty. Since the concatenation value is 596 so the answer is 596.

LEETCODE_SOLUTION_UNITTEST(2562, FindTheArrayConcatenationValue, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 52, 2, 4};
  long long   expect   = 596;
  long long   actual   = solution->findTheArrayConcVal(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,14,13,8,12]
// Output: 673
//
// Before performing any operation, nums is [5,14,13,8,12] and concatenation
// value is 0.
//  - In the first operation:
// We pick the first element, 5, and the last element, 12.
// Their concatenation is 512, and we add it to the concatenation value, so it
// becomes equal to 512. Then we delete them from the nums, so nums becomes
// equal to [14,13,8].
//  - In the second operation:
// We pick the first element, 14, and the last element, 8.
// Their concatenation is 148, and we add it to the concatenation value, so it
// becomes equal to 660. Then we delete them from the nums, so nums becomes
// equal to [13].
//  - In the third operation:
// nums has only one element, so we pick 13 and add it to the concatenation
// value, so it becomes equal to 673. Then we delete it from nums, so nums
// become empty. Since the concatenation value is 673 so the answer is 673.

LEETCODE_SOLUTION_UNITTEST(2562, FindTheArrayConcatenationValue, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 14, 13, 8, 12};
  long long   expect   = 673;
  long long   actual   = solution->findTheArrayConcVal(nums);
  LCD_EXPECT_EQ(expect, actual);
}
