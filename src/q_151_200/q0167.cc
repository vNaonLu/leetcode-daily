// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Two Sum II - Input Array Is Sorted
//
// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
//
// Question ID: 167
// Difficult  : Medium
// Solve Date : 2021/09/07 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |167. Two Sum II - Input Array Is Sorted|:
//
// Given a 1-indexed array of integers |numbers| that is already sorted in
// non-decreasing order, find two numbers such that they add up to a specific
// |target| number. Let these two numbers be |numbers[index₁]| and
// |numbers[index₂]| where |1 <= index₁ < index₂ <= numbers.length|. Return the
// indices of the two numbers, |index₁| and |index₂|, added by one as an integer
// array |[index₁, index₂]| of length 2. The tests are generated such that there
// is exactly one solution. You may not use the same element twice. Your
// solution must use only constant extra space.  
//

LEETCODE_BEGIN_RESOLVING(167, TwoSumIIInputArrayIsSorted, Solution);

class Solution {
public:
  vector<int> twoSum(vector<int> &numbers, int target) {
    int l = 0, r = numbers.size() - 1;
    while (l < r) {
      int cur = numbers[l] + numbers[r];
      if (cur > target) {
        --r;
      } else if (cur < target) {
        ++l;
      } else {
        return {l + 1, r + 1};
      }
    }
    return {-1, -1};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= numbers.length <= 3 * 10⁴|
// * |-1000 <= numbers[i] <= 1000|
// * |numbers| is sorted in non-decreasing order.
// * |-1000 <= target <= 1000|
// * The tests are generated such that there is exactly one solution.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numbers = [2,7,11,15], target = 9
// Output: [1,2]
//
// The sum of 2 and 7 is 9. Therefore, index₁ = 1, index₂ = 2. We return [1, 2].

LEETCODE_SOLUTION_UNITTEST(167, TwoSumIIInputArrayIsSorted, example_1) {
  auto        solution = MakeSolution();
  vector<int> numbers  = {2, 7, 11, 15};
  int         target   = 9;
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->twoSum(numbers, target);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: numbers = [2,3,4], target = 6
// Output: [1,3]
//
// The sum of 2 and 4 is 6. Therefore index₁ = 1, index₂ = 3. We return [1, 3].

LEETCODE_SOLUTION_UNITTEST(167, TwoSumIIInputArrayIsSorted, example_2) {
  auto        solution = MakeSolution();
  vector<int> numbers  = {2, 3, 4};
  int         target   = 6;
  vector<int> expect   = {1, 3};
  vector<int> actual   = solution->twoSum(numbers, target);
  EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: numbers = [-1,0], target = -1
// Output: [1,2]
//
// The sum of -1 and 0 is -1. Therefore index₁ = 1, index₂ = 2. We return [1,
// 2].

LEETCODE_SOLUTION_UNITTEST(167, TwoSumIIInputArrayIsSorted, example_3) {
  auto        solution = MakeSolution();
  vector<int> numbers  = {-1, 0};
  int         target   = -1;
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->twoSum(numbers, target);
  EXPECT_EQ(expect, actual);
}
