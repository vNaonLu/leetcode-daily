// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Element
//
// https://leetcode.com/problems/remove-element/
//
// Question ID: 27
// Difficult  : Easy
// Solve Date : 2021/11/20 14:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |27. Remove Element|:
//
// Given an integer array |nums| and an integer |val|, remove all occurrences of
// |val| in |nums| in-place. The relative order of the elements may be changed.
// Since it is impossible to change the length of the array in some languages,
// you must instead have the result be placed in the first part of the array
// |nums|. More formally, if there are |k| elements after removing the
// duplicates, then the first |k| elements of |nums| should hold the final
// result. It does not matter what you leave beyond the first |k| elements.
// Return |k| after placing the final result in the first |k| slots of |nums|.
// Do not allocate extra space for another array. You must do this by modifying
// the input array [in-place] with O(1) extra memory. Custom Judge: The judge
// will test your solution with the following code: int[] nums = [...]; // Input
// array int val = ...; // Value to remove int[] expectedNums = [...]; // The
// expected answer with correct length.
//                             // It is sorted with no values equaling val.
// int k = removeElement(nums, val); // Calls your implementation
// assert k == expectedNums.length;
// sort(nums, 0, k); // Sort the first k elements of nums
// for (int i = 0; i < actualLength; i++) {
//     assert nums[i] == expectedNums[i];
// }
// If all assertions pass, then your solution will be accepted.
//  
//

LEETCODE_BEGIN_RESOLVING(27, RemoveElement, Solution);

class Solution {
public:
  int removeElement(vector<int> &nums, int val) {
    int last = nums.size() - 1;
    for (int i = 0; i <= last; ++i) {
      if (nums[i] == val) {
        while (i <= last && nums[last] == val)
          --last;
        if (last < i)
          break;
        swap(nums[i], nums[last]);
      }
    }
    return max(last + 1, 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= nums.length <= 100|
// * |0 <= nums[i] <= 50|
// * |0 <= val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,2,3], val = 3
// Output: 2, nums = [2,2,_,_]
//
// Your function should return k = 2, with the first two elements of nums
// being 2. It does not matter what you leave beyond the returned k (hence they
// are underscores).

LEETCODE_SOLUTION_UNITTEST(27, RemoveElement, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 2, 3};
  int         val      = 3;
  int         expect   = 2;
  int         actual   = solution->removeElement(nums, val);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,2,2,3,0,4,2], val = 2
// Output: 5, nums = [0,1,4,0,3,_,_,_]
//
// Your function should return k = 5, with the first five elements of nums
// containing 0, 0, 1, 3, and 4. Note that the five elements can be returned in
// any order. It does not matter what you leave beyond the returned k (hence
// they are underscores).

LEETCODE_SOLUTION_UNITTEST(27, RemoveElement, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 2, 2, 3, 0, 4, 2};
  int         val      = 2;
  int         expect   = 5;
  int         actual   = solution->removeElement(nums, val);
  LCD_EXPECT_EQ(expect, actual);
}
