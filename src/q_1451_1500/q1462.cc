// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Course Schedule IV
//
// https://leetcode.com/problems/course-schedule-iv/
//
// Question ID: 1462
// Difficult  : Medium
// Solve Date : 2022/03/04 18:34

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1462. Course Schedule IV|:
//
// There are a total of |numCourses| courses you have to take, labeled from |0|
// to |numCourses - 1|. You are given an array |prerequisites| where
// |prerequisites[i] = [aᵢ, bᵢ]| indicates that you must take course |aᵢ| first
// if you want to take course |bᵢ|.
//
//  • For example, the pair |[0, 1]| indicates that you have to take course |0|
//  before you can take course |1|.
// Prerequisites can also be indirect. If course |a| is a prerequisite of course
// |b|, and course |b| is a prerequisite of course |c|, then course |a| is a
// prerequisite of course |c|. You are also given an array |queries| where
// |queries[j] = [uⱼ, vⱼ]|. For the |jᵗʰ| query, you should answer whether
// course |uⱼ| is a prerequisite of course |vⱼ| or not. Return a boolean array
// |answer|, where |answer[j]| is the answer to the |jᵗʰ| query.  
//

LEETCODE_BEGIN_RESOLVING(1462, CourseScheduleIV, Solution);

class Solution {
private:
  unordered_map<int, unordered_set<int>> requisites;
  bool dfs(int src, int dst, vector<bool> &visit) {
    if (src == dst)
      return true;
    visit[src] = true;
    for (const auto &next : requisites[src]) {
      if (!visit[next] && dfs(next, dst, visit))
        return true;
    }
    return false;
  }

public:
  vector<bool> checkIfPrerequisite(int                  numCourses,
                                   vector<vector<int>> &prerequisites,
                                   vector<vector<int>> &queries) {
    vector<bool> res;
    res.reserve(queries.size());
    for (const auto &v : prerequisites) {
      requisites[v[1]].insert(v[0]);
    }
    for (const auto &v : queries) {
      vector<bool> visited(numCourses, false);
      res.emplace_back(dfs(v[1], v[0], visited));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= numCourses <= 100|
// * |0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)|
// * |prerequisites[i].length == 2|
// * |0 <= aᵢ, bᵢ <= n - 1|
// * |aᵢ != bᵢ|
// * All the pairs |[aᵢ, bᵢ]| are unique.
// * The prerequisites graph has no cycles.
// * |1 <= queries.length <= 10⁴|
// * |0 <= uᵢ, vᵢ <= n - 1|
// * |uᵢ != vᵢ|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
// Output: [false,true]
//
// The pair [1, 0] indicates that you have to take course 1 before you can take
// course 0. Course 0 is not a prerequisite of course 1, but the opposite is
// true.

LEETCODE_SOLUTION_UNITTEST(1462, CourseScheduleIV, example_1) {
  auto                solution      = MakeSolution();
  int                 numCourses    = 2;
  vector<vector<int>> prerequisites = {
      {1, 0}
  };
  vector<vector<int>> queries = {
      {0, 1},
      {1, 0}
  };
  vector<bool> expect = {false, true};
  vector<bool> actual =
      solution->checkIfPrerequisite(numCourses, prerequisites, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
// Output: [false,false]
//
// There are no prerequisites, and each course is independent.

LEETCODE_SOLUTION_UNITTEST(1462, CourseScheduleIV, example_2) {
  auto                solution      = MakeSolution();
  int                 numCourses    = 2;
  vector<vector<int>> prerequisites = {};
  vector<vector<int>> queries       = {
      {1, 0},
      {0, 1}
  };
  vector<bool> expect = {false, false};
  vector<bool> actual =
      solution->checkIfPrerequisite(numCourses, prerequisites, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries =
//  [[1,0],[1,2]]
// Output: [true,true]
//

LEETCODE_SOLUTION_UNITTEST(1462, CourseScheduleIV, example_3) {
  auto                solution      = MakeSolution();
  int                 numCourses    = 3;
  vector<vector<int>> prerequisites = {
      {1, 2},
      {1, 0},
      {2, 0}
  };
  vector<vector<int>> queries = {
      {1, 0},
      {1, 2}
  };
  vector<bool> expect = {true, true};
  vector<bool> actual =
      solution->checkIfPrerequisite(numCourses, prerequisites, queries);
  LCD_EXPECT_EQ(expect, actual);
}
