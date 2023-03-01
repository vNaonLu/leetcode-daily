// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Summary Ranges
//
// https://leetcode.com/problems/summary-ranges/
//
// Question ID: 228
// Difficult  : Easy
// Solve Date : 2022/02/28 15:43

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |228. Summary Ranges|:
//
// You are given a sorted unique integer array |nums|.
// A range |[a,b]| is the set of all integers from |a| to |b| (inclusive).
// Return the smallest sorted list of ranges that cover all the numbers in the
// array exactly. That is, each element of |nums| is covered by exactly one of
// the ranges, and there is no integer |x| such that |x| is in one of the ranges
// but not in |nums|. Each range |[a,b]| in the list should be output as:
//
//  • |"a->b"| if |a != b|
//
//  • |"a"| if |a == b|
//  
//

LEETCODE_BEGIN_RESOLVING(228, SummaryRanges, Solution);

class Solution {
public:
  vector<string> summaryRanges(vector<int> &nums) {
    if (nums.empty())
      return {};
    vector<string> res;
    int            from = nums.front(), to = nums.front();
    for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
      if (to != *it - 1) {
        if (from == to) {
          res.push_back(to_string(from));
        } else {
          res.push_back(to_string(from) + "->" + to_string(to));
        }
        from = to = *it;
      } else {
        to = *it;
      }
    }
    if (from == to) {
      res.push_back(to_string(from));
    } else {
      res.push_back(to_string(from) + "->" + to_string(to));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= nums.length <= 20|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
// * All the values of |nums| are unique.
// * |nums| is sorted in ascending order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,2,4,5,7]
// Output: ["0->2","4->5","7"]
//
// The ranges are:
// [0,2] --> "0->2"
// [4,5] --> "4->5"
// [7,7] --> "7"

LEETCODE_SOLUTION_UNITTEST(228, SummaryRanges, example_1) {
  auto           solution = MakeSolution();
  vector<int>    nums     = {0, 1, 2, 4, 5, 7};
  vector<string> expect   = {"0->2", "4->5", "7"};
  vector<string> actual   = solution->summaryRanges(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,2,3,4,6,8,9]
// Output: ["0","2->4","6","8->9"]
//
// The ranges are:
// [0,0] --> "0"
// [2,4] --> "2->4"
// [6,6] --> "6"
// [8,9] --> "8->9"

LEETCODE_SOLUTION_UNITTEST(228, SummaryRanges, example_2) {
  auto           solution = MakeSolution();
  vector<int>    nums     = {0, 2, 3, 4, 6, 8, 9};
  vector<string> expect   = {"0", "2->4", "6", "8->9"};
  vector<string> actual   = solution->summaryRanges(nums);
  LCD_EXPECT_EQ(expect, actual);
}
