// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Right Interval
//
// https://leetcode.com/problems/find-right-interval/
//
// Question ID: 436
// Difficult  : Medium
// Solve Date : 2022/07/24 15:12

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |436. Find Right Interval|:
//
// You are given an array of |intervals|, where |intervals[i] = [startᵢ, endᵢ]|
// and each |startᵢ| is unique. The right interval for an interval |i| is an
// interval |j| such that |startⱼ >= endᵢ| and |startⱼ| is minimized. Note that
// |i| may equal |j|. Return an array of right interval indices for each
// interval |i|. If no right interval exists for interval |i|, then put |-1| at
// index |i|.
//

LEETCODE_BEGIN_RESOLVING(436, FindRightInterval, Solution);

class Solution {
public:
  vector<int> findRightInterval(vector<vector<int>> &intervals) {
    vector<int> res;
    res.reserve(intervals.size());
    map<int, int> memo; // end -> index

    for (int i = 0; i < intervals.size(); ++i) {
      memo[intervals[i][0]] = i;
    }

    for (auto &v : intervals) {
      auto find = memo.lower_bound(v[1]);
      if (find == memo.end()) {
        res.emplace_back(-1);
      } else {
        res.emplace_back(find->second);
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= intervals.length <= 2 * 10⁴|
// * |intervals[i].length == 2|
// * |-10⁶ <= startᵢ <= endᵢ <= 10⁶|
// * The start point of each interval is unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: intervals = [[1,2]]
// Output: [-1]
//
// There is only one interval in the collection, so it outputs -1.

LEETCODE_SOLUTION_UNITTEST(436, FindRightInterval, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 2}
  };
  vector<int> expect = {-1};
  vector<int> actual = solution->findRightInterval(intervals);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: intervals = [[3,4],[2,3],[1,2]]
// Output: [-1,0,1]
//
// There is no right interval for [3,4].
// The right interval for [2,3] is [3,4] since start₀ = 3 is the smallest start
// that is >= end₁ = 3. The right interval for [1,2] is [2,3] since start₁ = 2
// is the smallest start that is >= end₂ = 2.

LEETCODE_SOLUTION_UNITTEST(436, FindRightInterval, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {3, 4},
      {2, 3},
      {1, 2}
  };
  vector<int> expect = {-1, 0, 1};
  vector<int> actual = solution->findRightInterval(intervals);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: intervals = [[1,4],[2,3],[3,4]]
// Output: [-1,2,-1]
//
// There is no right interval for [1,4] and [3,4].
// The right interval for [2,3] is [3,4] since start₂ = 3 is the smallest start
// that is >= end₁ = 3.

LEETCODE_SOLUTION_UNITTEST(436, FindRightInterval, example_3) {
  auto                solution  = MakeSolution();
  vector<vector<int>> intervals = {
      {1, 4},
      {2, 3},
      {3, 4}
  };
  vector<int> expect = {-1, 2, -1};
  vector<int> actual = solution->findRightInterval(intervals);
  LCD_EXPECT_EQ(expect, actual);
}
