// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Duplicates from Sorted Array
//
// https://leetcode.com/problems/remove-duplicates-from-sorted-array/
//
// Question ID: 26
// Difficult  : Easy
// Solve Date : 2021/11/20 14:14

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |26. Remove Duplicates from Sorted Array|:
//
// Given an integer array |nums| sorted in non-decreasing order, remove the
// duplicates in-place such that each unique element appears only once. The
// relative order of the elements should be kept the same. Since it is
// impossible to change the length of the array in some languages, you must
// instead have the result be placed in the first part of the array |nums|. More
// formally, if there are |k| elements after removing the duplicates, then the
// first |k| elements of |nums| should hold the final result. It does not matter
// what you leave beyond the first  |k| elements. Return |k| after placing the
// final result in the first |k| slots of |nums|. Do not allocate extra space
// for another array. You must do this by modifying the input array [in-place]
// with O(1) extra memory. Custom Judge: The judge will test your solution with
// the following code: int[] nums = [...]; // Input array int[] expectedNums =
// [...]; // The expected answer with correct length int k =
// removeDuplicates(nums); // Calls your implementation assert k ==
// expectedNums.length; for (int i = 0; i < k; i++) {
//     assert nums[i] == expectedNums[i];
// }
// If all assertions pass, then your solution will be accepted.
//  
//

LEETCODE_BEGIN_RESOLVING(26, RemoveDuplicatesFromSortedArray, Solution);

class Solution {
public:
  int removeDuplicates(vector<int> &nums) {
    if (nums.empty())
      return 0;
    int cur = 0;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] != nums[cur]) {
        swap(nums[++cur], nums[i]);
      }
    }
    return cur + 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 3 * 10⁴|
// * |-100 <= nums[i] <= 100|
// * |nums| is sorted in non-decreasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,2]
// Output: 2, nums = [1,2,_]
//
// Your function should return k = 2, with the first two elements of nums being
// 1 and 2 respectively. It does not matter what you leave beyond the returned k
// (hence they are underscores).

LEETCODE_SOLUTION_UNITTEST(26, RemoveDuplicatesFromSortedArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2};
  int         expect   = 2;
  int         actual   = solution->removeDuplicates(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,0,1,1,1,2,2,3,3,4]
// Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
//
// Your function should return k = 5, with the first five elements of nums being
// 0, 1, 2, 3, and 4 respectively. It does not matter what you leave beyond the
// returned k (hence they are underscores).

LEETCODE_SOLUTION_UNITTEST(26, RemoveDuplicatesFromSortedArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  int         expect   = 5;
  int         actual   = solution->removeDuplicates(nums);
  LCD_EXPECT_EQ(expect, actual);
}
