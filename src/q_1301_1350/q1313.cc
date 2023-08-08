// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Decompress Run-Length Encoded List
//
// https://leetcode.com/problems/decompress-run-length-encoded-list/
//
// Question ID: 1313
// Difficult  : Easy
// Solve Date : 2023/08/03 18:43

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1313. Decompress Run-Length Encoded List|:
//
// We are given a list |nums| of integers representing a list compressed with
// run-length encoding. Consider each adjacent pair of elements |[freq, val] =
// [nums[2*i], nums[2*i+1]]| (with |i >= 0|).  For each such pair, there are
// |freq| elements with value |val| concatenated in a sublist. Concatenate all
// the sublists from left to right to generate the decompressed list. Return the
// decompressed list.
//
//

LEETCODE_BEGIN_RESOLVING(1313, DecompressRunLengthEncodedList, Solution);

class Solution {
public:
  vector<int> decompressRLElist(vector<int> &nums) {
    vector<int> res;
    for (int i = 0; i < nums.size(); i += 2) {
      for (int j = 0; j < nums[i]; ++j) {
        res.emplace_back(nums[i + 1]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 100|
// * |nums.length % 2 == 0|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: [2,4,4,4]
//
// The first pair [1,2] means we have freq = 1 and val = 2 so we generate the
// array [2]. The second pair [3,4] means we have freq = 3 and val = 4 so we
// generate [4,4,4]. At the end the concatenation [2] + [4,4,4] is [2,4,4,4].

LEETCODE_SOLUTION_UNITTEST(1313, DecompressRunLengthEncodedList, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  vector<int> expect   = {2, 4, 4, 4};
  vector<int> actual   = solution->decompressRLElist(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,2,3]
// Output: [1,3,3]
//

LEETCODE_SOLUTION_UNITTEST(1313, DecompressRunLengthEncodedList, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 3};
  vector<int> expect   = {1, 3, 3};
  vector<int> actual   = solution->decompressRLElist(nums);
  LCD_EXPECT_EQ(expect, actual);
}
