// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Next Greater Element I
//
// https://leetcode.com/problems/next-greater-element-i/
//
// Question ID: 496
// Difficult  : Easy
// Solve Date : 2021/10/19 10:51

#include <iosfwd>
#include <map>
#include <stack>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |496. Next Greater Element I|:
//
// The next greater element of some element |x| in an array is the first greater
// element that is to the right of |x| in the same array. You are given two
// distinct 0-indexed integer arrays |nums1| and |nums2|, where |nums1| is a
// subset of |nums2|. For each |0 <= i < nums1.length|, find the index |j| such
// that |nums1[i] == nums2[j]| and determine the next greater element of
// |nums2[j]| in |nums2|. If there is no next greater element, then the answer
// for this query is |-1|. Return an array |ans| of length |nums1.length| such
// that |ans[i]| is the next greater element as described above.  
//

LEETCODE_BEGIN_RESOLVING(496, NextGreaterElementI, Solution);

class Solution {
public:
  vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2) {
    unordered_map<int, int> mp;
    stack<int>              mx;
    for (int i = nums2.size() - 1; i >= 0; --i) {
      while (!mx.empty() && mx.top() < nums2[i])
        mx.pop();
      if (mx.empty()) {
        mp[nums2[i]] = -1;
      } else {
        mp[nums2[i]] = mx.top();
      }
      mx.push(nums2[i]);
    }
    vector<int> res(nums1.size());
    for (int i = 0; i < nums1.size(); ++i)
      res[i] = mp[nums1[i]];
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length <= nums2.length <= 1000|
// * |0 <= nums1[i], nums2[i] <= 10⁴|
// * All integers in |nums1| and |nums2| are unique.
// * All the integers of |nums1| also appear in |nums2|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
// Output: [-1,3,-1]
//
// The next greater element for each value of nums1 is as follows:
// - 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so
// the answer is -1.
// - 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
// - 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so
// the answer is -1.

LEETCODE_SOLUTION_UNITTEST(496, NextGreaterElementI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {4, 1, 2};
  vector<int> nums2    = {1, 3, 4, 2};
  vector<int> expect   = {-1, 3, -1};
  vector<int> actual   = solution->nextGreaterElement(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [2,4], nums2 = [1,2,3,4]
// Output: [3,-1]
//
// The next greater element for each value of nums1 is as follows:
// - 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
// - 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so
// the answer is -1.

LEETCODE_SOLUTION_UNITTEST(496, NextGreaterElementI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {2, 4};
  vector<int> nums2    = {1, 2, 3, 4};
  vector<int> expect   = {3, -1};
  vector<int> actual   = solution->nextGreaterElement(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}
