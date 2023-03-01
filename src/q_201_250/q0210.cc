// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Course Schedule II
//
// https://leetcode.com/problems/course-schedule-ii/
//
// Question ID: 210
// Difficult  : Medium
// Solve Date : 2021/12/23 18:09

#include <iosfwd>
#include <list>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |210. Course Schedule II|:
//
// There are a total of |numCourses| courses you have to take, labeled from |0|
// to |numCourses - 1|. You are given an array |prerequisites| where
// |prerequisites[i] = [aᵢ, bᵢ]| indicates that you must take course |bᵢ| first
// if you want to take course |aᵢ|.
//
//  • For example, the pair |[0, 1]|, indicates that to take course |0| you have
//  to first take course |1|.
// Return the ordering of courses you should take to finish all courses. If
// there are many valid answers, return any of them. If it is impossible to
// finish all courses, return an empty array.  
//

LEETCODE_BEGIN_RESOLVING(210, CourseScheduleII, Solution);

class Solution {
private:
  bool loop(vector<vector<int>> &graph, vector<int> &list, vector<int> &res,
            int i) {
    list[i] = 1;
    for (const auto &p : graph[i]) {
      if (list[p] == 1)
        return true;
      if (list[p] == 0)
        if (loop(graph, list, res, p))
          return true;
    }
    list[i] = 2;
    res.push_back(i);
    return false;
  }

public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<int>         res, list(numCourses, 0);
    vector<vector<int>> graph(numCourses);
    for (const auto &pre : prerequisites)
      graph[pre[0]].push_back(pre[1]);
    for (int i = 0; i < numCourses; ++i)
      if (list[i] == 0)
        if (loop(graph, list, res, i))
          return vector<int>{};
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= numCourses <= 2000|
// * |0 <= prerequisites.length <= numCourses * (numCourses - 1)|
// * |prerequisites[i].length == 2|
// * |0 <= aᵢ, bᵢ < numCourses|
// * |aᵢ != bᵢ|
// * All the pairs |[aᵢ, bᵢ]| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numCourses = 2, prerequisites = [[1,0]]
// Output: [0,1]
//
// There are a total of 2 courses to take. To take course 1 you should have
// finished course 0. So the correct course order is [0,1].

LEETCODE_SOLUTION_UNITTEST(210, CourseScheduleII, example_1) {
  auto                solution      = MakeSolution();
  int                 numCourses    = 2;
  vector<vector<int>> prerequisites = {
      {1, 0}
  };
  vector<int> expect = {0, 1};
  vector<int> actual = solution->findOrder(numCourses, prerequisites);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
// Output: [0,2,1,3]
//
// There are a total of 4 courses to take. To take course 3 you should have
// finished both courses 1 and 2. Both courses 1 and 2 should be taken after you
// finished course 0. So one correct course order is [0,1,2,3]. Another correct
// ordering is [0,2,1,3].

LEETCODE_SOLUTION_UNITTEST(210, CourseScheduleII, example_2) {
  auto                solution      = MakeSolution();
  int                 numCourses    = 4;
  vector<vector<int>> prerequisites = {
      {1, 0},
      {2, 0},
      {3, 1},
      {3, 2}
  };
  vector<int> expect = {0, 2, 1, 3};
  vector<int> actual = solution->findOrder(numCourses, prerequisites);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: numCourses = 1, prerequisites = []
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(210, CourseScheduleII, example_3) {
  auto                solution      = MakeSolution();
  int                 numCourses    = 1;
  vector<vector<int>> prerequisites = {};
  vector<int>         expect        = {0};
  vector<int>         actual = solution->findOrder(numCourses, prerequisites);
  EXPECT_ANYORDER_EQ(expect, actual);
}
