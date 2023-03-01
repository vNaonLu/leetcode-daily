// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Intersection of Two Arrays
//
// https://leetcode.com/problems/intersection-of-two-arrays/
//
// Question ID: 349
// Difficult  : Easy
// Solve Date : 2022/08/29 17:47

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |349. Intersection of Two Arrays|:
//
// Given two integer arrays |nums1| and |nums2|, return an array of their
// intersection. Each element in the result must be unique and you may return
// the result in any order.
//

LEETCODE_BEGIN_RESOLVING(349, IntersectionOfTwoArrays, Solution);

class Solution {
public:
  vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
    auto nums1_map = unordered_set<int>(nums1.begin(), nums1.end());
    auto res       = unordered_set<int>();
    for (auto x : nums2) {
      if (nums1_map.count(x)) {
        res.emplace(x);
      }
    }
    return vector<int>{res.begin(), res.end()};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 1000|
// * |0 <= nums1[i], nums2[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2]
//

LEETCODE_SOLUTION_UNITTEST(349, IntersectionOfTwoArrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2, 2, 1};
  vector<int> nums2    = {2, 2};
  vector<int> expect   = {2};
  vector<int> actual   = solution->intersection(nums1, nums2);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
// Output: [9,4]
//
// [4,9] is also accepted.

LEETCODE_SOLUTION_UNITTEST(349, IntersectionOfTwoArrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {4, 9, 5};
  vector<int> nums2    = {9, 4, 9, 8, 4};
  vector<int> expect   = {9, 4};
  vector<int> actual   = solution->intersection(nums1, nums2);
  EXPECT_ANYORDER_EQ(expect, actual);
}
