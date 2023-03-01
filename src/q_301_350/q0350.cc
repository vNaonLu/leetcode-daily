// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Intersection of Two Arrays II
//
// https://leetcode.com/problems/intersection-of-two-arrays-ii/
//
// Question ID: 350
// Difficult  : Easy
// Solve Date : 2021/09/07 08:00

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |350. Intersection of Two Arrays II|:
//
// Given two integer arrays |nums1| and |nums2|, return an array of their
// intersection. Each element in the result must appear as many times as it
// shows in both arrays and you may return the result in any order.  
//

LEETCODE_BEGIN_RESOLVING(350, IntersectionofTwoArraysII, Solution);

class Solution {
public:
  vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    vector<int> res;
    res.reserve(min(nums1.size(), nums2.size()));
    while (!nums1.empty() && !nums2.empty()) {
      if (nums1.back() == nums2.back()) {
        res.push_back(nums1.back());
        nums1.pop_back();
        nums2.pop_back();
      } else if (nums1.back() > nums2.back()) {
        nums1.pop_back();
      } else {
        nums2.pop_back();
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 1000|
// * |0 <= nums1[i], nums2[i] <= 1000|
// * What if the given array is already sorted? How would you optimize your
// algorithm?
// * What if |nums1|'s size is small compared to |nums2|'s size? Which algorithm
// is better?
// * What if elements of |nums2| are stored on disk, and the memory is limited
// such that you cannot load all elements into the memory at once?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2,2]
//

LEETCODE_SOLUTION_UNITTEST(350, IntersectionofTwoArraysII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2, 2, 1};
  vector<int> nums2    = {2, 2};
  vector<int> expect   = {2, 2};
  vector<int> actual   = solution->intersect(nums1, nums2);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
// Output: [4,9]
//
// [9,4] is also accepted.

LEETCODE_SOLUTION_UNITTEST(350, IntersectionofTwoArraysII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {4, 9, 5};
  vector<int> nums2    = {9, 4, 9, 8, 4};
  vector<int> expect   = {4, 9};
  vector<int> actual   = solution->intersect(nums1, nums2);
  EXPECT_ANYORDER_EQ(expect, actual);
}
