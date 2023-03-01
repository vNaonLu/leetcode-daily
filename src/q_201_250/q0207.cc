// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Course Schedule
//
// https://leetcode.com/problems/course-schedule/
//
// Question ID: 207
// Difficult  : Medium
// Solve Date : 2022/08/22 16:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |207. Course Schedule|:
//
// There are a total of |numCourses| courses you have to take, labeled from |0|
// to |numCourses - 1|. You are given an array |prerequisites| where
// |prerequisites[i] = [aᵢ, bᵢ]| indicates that you must take course |bᵢ| first
// if you want to take course |aᵢ|.
//
//  • For example, the pair |[0, 1]|, indicates that to take course |0| you have
//  to first take course |1|.
// Return |true| if you can finish all courses. Otherwise, return |false|.
//

LEETCODE_BEGIN_RESOLVING(207, CourseSchedule, Solution);

class Solution {
private:
  enum Status { kIncomplete, kProgress, kComplete };

  bool solve(vector<vector<int>> &v, int cur, vector<Status> &stat) {
    if (stat[cur] == kComplete) {
      return true;
    } else if (stat[cur] == kProgress) {
      return false;
    }

    stat[cur] = kProgress;
    for (auto &x : v[cur]) {
      if (!solve(v, x, stat)) {
        return false;
      }
    }
    stat[cur] = kComplete;

    return true;
  }

public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    auto req  = vector<vector<int>>(numCourses);
    auto stat = vector<Status>(numCourses, Status::kIncomplete);

    for (auto &v : prerequisites) {
      if (v[0] == v[1]) {
        return false;
      }

      req[v[0]].emplace_back(v[1]);
    }

    for (int i = 0; i < req.size(); ++i) {
      if (!solve(req, i, stat)) {
        return false;
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= numCourses <= 2000|
// * |0 <= prerequisites.length <= 5000|
// * |prerequisites[i].length == 2|
// * |0 <= aᵢ, bᵢ < numCourses|
// * All the pairs prerequisites[i] are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numCourses = 2, prerequisites = [[1,0]]
// Output: true
//
// There are a total of 2 courses to take.
// To take course 1 you should have finished course 0. So it is possible.

LEETCODE_SOLUTION_UNITTEST(207, CourseSchedule, example_1) {
  auto                solution      = MakeSolution();
  int                 numCourses    = 2;
  vector<vector<int>> prerequisites = {
      {1, 0}
  };
  bool expect = true;
  bool actual = solution->canFinish(numCourses, prerequisites);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
// Output: false
//
// There are a total of 2 courses to take.
// To take course 1 you should have finished course 0, and to take course 0 you
// should also have finished course 1. So it is impossible.

LEETCODE_SOLUTION_UNITTEST(207, CourseSchedule, example_2) {
  auto                solution      = MakeSolution();
  int                 numCourses    = 2;
  vector<vector<int>> prerequisites = {
      {1, 0},
      {0, 1}
  };
  bool expect = false;
  bool actual = solution->canFinish(numCourses, prerequisites);
  LCD_EXPECT_EQ(expect, actual);
}
