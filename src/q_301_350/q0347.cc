// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Top K Frequent Elements
//
// https://leetcode.com/problems/top-k-frequent-elements/
//
// Question ID: 347
// Difficult  : Medium
// Solve Date : 2021/10/08 13:09

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |347. Top K Frequent Elements|:
//
// Given an integer array |nums| and an integer |k|, return the |k| most
// frequent elements. You may return the answer in any order.  
//

LEETCODE_BEGIN_RESOLVING(347, TopKFrequentElements, Solution);

class Solution {
public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> cnt;
    for (const auto &n : nums)
      ++cnt[n];
    set<pair<int, int>> ordered;
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
      ordered.insert(make_pair(it->second, it->first));
    }
    vector<int> res;
    for (auto it = ordered.rbegin(); it != ordered.rend(); ++it) {
      res.push_back((*it).second);
      if (res.size() == k)
        break;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁴ <= nums[i] <= 10⁴|
// * |k| is in the range |[1, the number of unique elements in the array]|.
// * It is guaranteed that the answer is unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,1,2,2,3], k = 2
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(347, TopKFrequentElements, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 2, 2, 3};
  int         k        = 2;
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->topKFrequent(nums, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1], k = 1
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(347, TopKFrequentElements, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         k        = 1;
  vector<int> expect   = {1};
  vector<int> actual   = solution->topKFrequent(nums, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}
