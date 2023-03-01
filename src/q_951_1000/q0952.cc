// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Component Size by Common Factor
//
// https://leetcode.com/problems/largest-component-size-by-common-factor/
//
// Question ID: 952
// Difficult  : Hard
// Solve Date : 2021/11/23 18:31

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |952. Largest Component Size by Common Factor|:
//
// You are given an integer array of unique positive integers |nums|. Consider
// the following graph:
//
//  • There are |nums.length| nodes, labeled |nums[0]| to |nums[nums.length -
//  1]|,
//
//  • There is an undirected edge between |nums[i]| and |nums[j]| if |nums[i]|
//  and |nums[j]| share a common factor greater than |1|.
// Return the size of the largest connected component in the graph.
//  
//

LEETCODE_BEGIN_RESOLVING(952, LargestComponentSizeByCommonFactor, Solution);

class Solution {
private:
  vector<int> rank, parent;
  int         find(int x) {
    if (parent[x] == x)
      return x;
    return parent[x] = find(parent[x]);
  }
  void unionDsu(int x, int y) {
    int __x = find(x), __y = find(y);
    if (__x == __y)
      return;
    if (rank[__x] < rank[__y]) {
      parent[__x] = __y;
    } else if (rank[__y] < rank[__x]) {
      parent[__y] = __x;
    } else {
      parent[__y] = __x;
      rank[__x] += 1;
    }
  }

public:
  int largestComponentSize(vector<int> &nums) {
    int N = *max_element(nums.begin(), nums.end());
    parent.resize(N + 1);
    rank.resize(N + 1, 1);
    for (int i = 0; i <= N; ++i)
      parent[i] = i;
    for (const auto &x : nums) {
      for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
          unionDsu(x, i);
          unionDsu(x / i, i);
        }
      }
    }
    unordered_map<int, int> count;
    int                     res = 0;
    for (const auto &x : nums) {
      auto __x = find(x);
      ++count[__x];
    }
    for (const auto &p : count) {
      res = max(res, p.second);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁴|
// * |1 <= nums[i] <= 10⁵|
// * All the values of |nums| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,6,15,35]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(952, LargestComponentSizeByCommonFactor, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 6, 15, 35};
  int         expect   = 4;
  int         actual   = solution->largestComponentSize(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [20,50,9,63]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(952, LargestComponentSizeByCommonFactor, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {20, 50, 9, 63};
  int         expect   = 2;
  int         actual   = solution->largestComponentSize(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,3,6,7,4,12,21,39]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(952, LargestComponentSizeByCommonFactor, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 6, 7, 4, 12, 21, 39};
  int         expect   = 8;
  int         actual   = solution->largestComponentSize(nums);
  LCD_EXPECT_EQ(expect, actual);
}
