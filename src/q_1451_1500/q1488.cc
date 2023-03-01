// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Avoid Flood in The City
//
// https://leetcode.com/problems/avoid-flood-in-the-city/
//
// Question ID: 1488
// Difficult  : Medium
// Solve Date : 2022/07/31 13:00

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1488. Avoid Flood in The City|:
//
// Your country has an infinite number of lakes. Initially, all the lakes are
// empty, but when it rains over the |nth| lake, the |nth| lake becomes full of
// water. If it rains over a lake that is full of water, there will be a flood.
// Your goal is to avoid floods in any lake. Given an integer array |rains|
// where:
//
//  • |rains[i] > 0| means there will be rains over the |rains[i]| lake.
//
//  • |rains[i] == 0| means there are no rains this day and you can choose one
//  lake this day and dry it.
// Return an array |ans| where:
//
//  • |ans.length == rains.length|
//
//  • |ans[i] == -1| if |rains[i] > 0|.
//
//  • |ans[i]| is the lake you choose to dry in the |ith| day if |rains[i] ==
//  0|.
// If there are multiple valid answers return any of them. If it is impossible
// to avoid flood return an empty array. Notice that if you chose to dry a full
// lake, it becomes empty, but if you chose to dry an empty lake, nothing
// changes.
//

LEETCODE_BEGIN_RESOLVING(1488, AvoidFloodInTheCity, Solution);

class Solution {
public:
  vector<int> avoidFlood(vector<int> &rains) {
    auto res     = vector<int>(rains.size(), -1);
    auto indices = unordered_map<int, int>();
    auto memo    = set<int>();

    for (int i = 0; i < rains.size(); ++i) {
      if (rains[i] == 0) {
        memo.insert(i);
      } else {
        auto prev = indices.find(rains[i]);
        if (prev == indices.end()) {
          indices[rains[i]] = i;
        } else {
          auto &prev = indices[rains[i]];
          auto  find = memo.upper_bound(prev);

          if (find == memo.end()) {
            return vector<int>{};
          } else {
            res[*find] = rains[i];
            prev       = i;
            memo.erase(find);
          }
        }
      }
    }

    for (int i = 0; i < res.size(); ++i) {
      if (rains[i] == 0 && res[i] == -1) {
        res[i] = 1;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= rains.length <= 10⁵|
// * |0 <= rains[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rains = [1,2,3,4]
// Output: [-1,-1,-1,-1]
//
// After the first day full lakes are [1]
// After the second day full lakes are [1,2]
// After the third day full lakes are [1,2,3]
// After the fourth day full lakes are [1,2,3,4]
// There's no day to dry any lake and there is no flood in any lake.

LEETCODE_SOLUTION_UNITTEST(1488, AvoidFloodInTheCity, example_1) {
  auto        solution = MakeSolution();
  vector<int> rains    = {1, 2, 3, 4};
  vector<int> expect   = {-1, -1, -1, -1};
  vector<int> actual   = solution->avoidFlood(rains);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rains = [1,2,0,0,2,1]
// Output: [-1,-1,2,1,-1,-1]
//
// After the first day full lakes are [1]
// After the second day full lakes are [1,2]
// After the third day, we dry lake 2. Full lakes are [1]
// After the fourth day, we dry lake 1. There is no full lakes.
// After the fifth day, full lakes are [2].
// After the sixth day, full lakes are [1,2].
// It is easy that this scenario is flood-free. [-1,-1,1,2,-1,-1] is another
// acceptable scenario.

LEETCODE_SOLUTION_UNITTEST(1488, AvoidFloodInTheCity, example_2) {
  auto        solution = MakeSolution();
  vector<int> rains    = {1, 2, 0, 0, 2, 1};
  vector<int> expect   = {-1, -1, 2, 1, -1, -1};
  vector<int> actual   = solution->avoidFlood(rains);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: rains = [1,2,0,1,2]
// Output: []
//
// After the second day, full lakes are [1,2]. We have to dry one lake in the
// third day. After that, it will rain over lakes [1,2]. It's easy to prove that
// no matter which lake you choose to dry in the 3rd day, the other one will
// flood.

LEETCODE_SOLUTION_UNITTEST(1488, AvoidFloodInTheCity, example_3) {
  auto        solution = MakeSolution();
  vector<int> rains    = {1, 2, 0, 1, 2};
  vector<int> expect   = {};
  vector<int> actual   = solution->avoidFlood(rains);
  LCD_EXPECT_EQ(expect, actual);
}
