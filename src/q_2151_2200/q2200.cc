// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find All K-Distant Indices in an Array
//
// https://leetcode.com/problems/find-all-k-distant-indices-in-an-array/
//
// Question ID: 2200
// Difficult  : Easy
// Solve Date : 2022/03/13 14:53

#include <algorithm>
#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2200. Find All K-Distant Indices in an Array|:
//
// You are given a 0-indexed integer array |nums| and two integers |key| and
// |k|. A k-distant index is an index |i| of |nums| for which there exists at
// least one index |j| such that ||i - j| <= k| and |nums[j] == key|. Return a
// list of all k-distant indices sorted in increasing order.  
//

LEETCODE_BEGIN_RESOLVING(2200, FindAllKDistantIndicesInAnArray, Solution);

class Solution {
public:
  vector<int> findKDistantIndices(vector<int> &nums, int key, int k) {
    unordered_set<int> memos, res;

    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == key) {
        for (int j = max<int>(0, i - k); j < min<int>(nums.size(), i + k + 1);
             ++j) {
          res.insert(j);
        }
      }
    }

    vector<int> ans(res.begin(), res.end());
    sort(ans.begin(), ans.end());
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 1000|
// * |key| is an integer from the array |nums|.
// * |1 <= k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,4,9,1,3,9,5], key = 9, k = 1
// Output: [1,2,3,4,5,6]
//
// Here, |nums[2] == key| and |nums[5] == key.
// - For index 0, |0 - 2| > k and |0 - 5| > k, so there is no j| where ||0 - j|
// <= k| and |nums[j] == key. Thus, 0 is not a k-distant index.
// - For index 1, |1 - 2| <= k and nums[2] == key, so 1 is a k-distant index.
// - For index 2, |2 - 2| <= k and nums[2] == key, so 2 is a k-distant index.
// - For index 3, |3 - 2| <= k and nums[2] == key, so 3 is a k-distant index.
// - For index 4, |4 - 5| <= k and nums[5] == key, so 4 is a k-distant index.
// - For index 5, |5 - 5| <= k and nums[5] == key, so 5 is a k-distant index.
// - For index 6, |6 - 5| <= k and nums[5] == key, so 6 is a k-distant index.
// |Thus, we return [1,2,3,4,5,6] which is sorted in increasing order.

LEETCODE_SOLUTION_UNITTEST(2200, FindAllKDistantIndicesInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 9, 1, 3, 9, 5};
  int         key      = 9;
  int         k        = 1;
  vector<int> expect   = {1, 2, 3, 4, 5, 6};
  vector<int> actual   = solution->findKDistantIndices(nums, key, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,2,2,2], key = 2, k = 2
// Output: [0,1,2,3,4]
//
// For all indices i in nums, there exists some index j such that |i - j| <= k
// and nums[j] == key, so every index is a k-distant index. Hence, we return
// [0,1,2,3,4].

LEETCODE_SOLUTION_UNITTEST(2200, FindAllKDistantIndicesInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 2, 2, 2};
  int         key      = 2;
  int         k        = 2;
  vector<int> expect   = {0, 1, 2, 3, 4};
  vector<int> actual   = solution->findKDistantIndices(nums, key, k);
  LCD_EXPECT_EQ(expect, actual);
}
