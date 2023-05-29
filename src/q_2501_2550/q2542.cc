// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Subsequence Score
//
// https://leetcode.com/problems/maximum-subsequence-score/
//
// Question ID: 2542
// Difficult  : Medium
// Solve Date : 2023/05/24 20:01

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2542. Maximum Subsequence Score|:
//
// You are given two 0-indexed integer arrays |nums1| and |nums2| of equal
// length |n| and a positive integer |k|. You must choose a subsequence of
// indices from |nums1| of length |k|. For chosen indices |i₀|, |i₁|, ..., |i_{k
// - 1}|, your score is defined as:
//
//  • The sum of the selected elements from |nums1| multiplied with the minimum
//  of the selected elements from |nums2|.
//
//  • It can defined simply as: |(nums1[i₀] + nums1[i₁] +...+ nums1[i_{k - 1}])
//  * min(nums2[i₀] , nums2[i₁], ... ,nums2[i_{k - 1}])|.
// Return the maximum possible score.
// A subsequence of indices of an array is a set that can be derived from the
// set |{0, 1, ..., n-1}| by deleting some or no elements.
//
//

LEETCODE_BEGIN_RESOLVING(2542, MaximumSubsequenceScore, Solution);

class Solution {
public:
  long long maxScore(vector<int> &nums1, vector<int> &nums2, int k) {
    vector<pair<int, int>> v;
    for (int i = 0; i < nums1.size(); ++i) {
      v.emplace_back(nums2[i], nums1[i]);
    }
    sort(v.rbegin(), v.rend());
    int64_t                                        res = 0;
    int64_t                                        cur = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < k - 1; ++i) {
      cur += v[i].second;
      pq.emplace(v[i].second);
    }
    for (int i = k - 1; i < nums1.size(); ++i) {
      cur += v[i].second;
      pq.emplace(v[i].second);
      res = max(res, cur * v[i].first);
      cur -= pq.top();
      pq.pop();
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums1.length == nums2.length|
// * |1 <= n <= 10⁵|
// * |0 <= nums1[i], nums2[j] <= 10⁵|
// * |1 <= k <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
// Output: 12
//
// The four possible subsequence scores are:
// - We choose the indices 0, 1, and 2 with score = (1+3+3) * min(2,1,3) = 7.
// - We choose the indices 0, 1, and 3 with score = (1+3+2) * min(2,1,4) = 6.
// - We choose the indices 0, 2, and 3 with score = (1+3+2) * min(2,3,4) = 12.
// - We choose the indices 1, 2, and 3 with score = (3+3+2) * min(1,3,4) = 8.
// Therefore, we return the max score, which is 12.

LEETCODE_SOLUTION_UNITTEST(2542, MaximumSubsequenceScore, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 3, 3, 2};
  vector<int> nums2    = {2, 1, 3, 4};
  int         k        = 3;
  long long   expect   = 12;
  long long   actual   = solution->maxScore(nums1, nums2, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [4,2,3,1,1], nums2 = [7,5,10,9,6], k = 1
// Output: 30
//
// Choosing index 2 is optimal: nums1[2] * nums2[2] = 3 * 10 = 30 is the maximum
// possible score.

LEETCODE_SOLUTION_UNITTEST(2542, MaximumSubsequenceScore, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {4, 2, 3, 1, 1};
  vector<int> nums2    = {7, 5, 10, 9, 6};
  int         k        = 1;
  long long   expect   = 30;
  long long   actual   = solution->maxScore(nums1, nums2, k);
  LCD_EXPECT_EQ(expect, actual);
}
