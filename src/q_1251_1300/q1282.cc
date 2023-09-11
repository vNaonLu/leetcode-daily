// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Group the People Given the Group Size They Belong To
//
// https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/
//
// Question ID: 1282
// Difficult  : Medium
// Solve Date : 2023/09/11 19:45

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1282. Group the People Given the Group Size They Belong To|:
//
// There are |n| people that are split into some unknown number of groups. Each
// person is labeled with a unique ID from |0| to |n - 1|. You are given an
// integer array |groupSizes|, where |groupSizes[i]| is the size of the group
// that person |i| is in. For example, if |groupSizes[1] = 3|, then person |1|
// must be in a group of size |3|. Return a list of groups such that each person
// |i| is in a group of size |groupSizes[i]|. Each person should appear in
// exactly one group, and every person must be in a group. If there are multiple
// answers, return any of them. It is guaranteed that there will be at least one
// valid solution for the given input.
//
//

LEETCODE_BEGIN_RESOLVING(1282, GroupThePeopleGivenTheGroupSizeTheyBelongTo,
                         Solution);

class Solution {
public:
  vector<vector<int>> groupThePeople(vector<int> &groupSizes) {
    vector<vector<int>>   res;
    map<int, vector<int>> group_mp;
    for (int i = 0; i < groupSizes.size(); ++i) {
      int d = groupSizes[i];
      group_mp[d].emplace_back(i);
      if (group_mp[d].size() == d) {
        res.emplace_back(std::move(group_mp[d]));
        group_mp[d].clear();
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |groupSizes.length == n|
// * |1 <= n <= 500|
// * |1 <= groupSizes[i] <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: groupSizes = [3,3,3,3,3,1,3]
// Output: [[5],[0,1,2],[3,4,6]]
//
// The first group is [5]. The size is 1, and groupSizes[5] = 1.
// The second group is [0,1,2]. The size is 3, and groupSizes[0] = groupSizes[1]
// = groupSizes[2] = 3. The third group is [3,4,6]. The size is 3, and
// groupSizes[3] = groupSizes[4] = groupSizes[6] = 3. Other possible solutions
// are [[2,1,6],[5],[0,4,3]] and [[5],[0,6,2],[4,3,1]].

LEETCODE_SOLUTION_UNITTEST(1282, GroupThePeopleGivenTheGroupSizeTheyBelongTo,
                           example_1) {
  auto                solution   = MakeSolution();
  vector<int>         groupSizes = {3, 3, 3, 3, 3, 1, 3};
  vector<vector<int>> expect     = {
      {5},
      {0, 1, 2},
      {3, 4, 6}
  };
  vector<vector<int>> actual = solution->groupThePeople(groupSizes);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: groupSizes = [2,1,3,3,3,2]
// Output: [[1],[0,5],[2,3,4]]
//

LEETCODE_SOLUTION_UNITTEST(1282, GroupThePeopleGivenTheGroupSizeTheyBelongTo,
                           example_2) {
  auto                solution   = MakeSolution();
  vector<int>         groupSizes = {2, 1, 3, 3, 3, 2};
  vector<vector<int>> expect     = {
      {1},
      {0, 5},
      {2, 3, 4}
  };
  vector<vector<int>> actual = solution->groupThePeople(groupSizes);
  EXPECT_ANYORDER_EQ(expect, actual);
}
