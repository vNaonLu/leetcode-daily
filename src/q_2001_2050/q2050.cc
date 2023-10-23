// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Parallel Courses III
//
// https://leetcode.com/problems/parallel-courses-iii/
//
// Question ID: 2050
// Difficult  : Hard
// Solve Date : 2023/10/18 19:39

#include <iosfwd>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2050. Parallel Courses III|:
//
// You are given an integer |n|, which indicates that there are |n| courses
// labeled from |1| to |n|. You are also given a 2D integer array |relations|
// where |relations[j] = [prevCourseⱼ, nextCourseⱼ]| denotes that course
// |prevCourseⱼ| has to be completed before course |nextCourseⱼ| (prerequisite
// relationship). Furthermore, you are given a 0-indexed integer array |time|
// where |time[i]| denotes how many months it takes to complete the |(i+1)ᵗʰ|
// course. You must find the minimum number of months needed to complete all the
// courses following these rules:
//
//  • You may start taking a course at any time if the prerequisites are met.
//
//  • Any number of courses can be taken at the same time.
// Return the minimum number of months needed to complete all the courses.
// Note: The test cases are generated such that it is possible to complete every
// course (i.e., the graph is a directed acyclic graph).
//
//

LEETCODE_BEGIN_RESOLVING(2050, ParallelCoursesIII, Solution);

class Solution {
public:
  int minimumTime(int n, vector<vector<int>> &relations, vector<int> &time) {
    unordered_map<int, vector<int>> graph;
    vector<int>                     degree(n + 1, 0);
    for (auto &r : relations) {
      graph[r[0]].emplace_back(r[1]);
      ++degree[r[1]];
    }
    vector<int> dist = time;
    queue<int>  q;
    dist.insert(dist.begin(), 0);
    for (int i = 1; i <= n; ++i) {
      if (degree[i] == 0) {
        q.emplace(i);
      }
    }
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (auto nxt : graph[x]) {
        dist[nxt] = max(dist[nxt], dist[x] + time[nxt - 1]);
        if (--degree[nxt] == 0) {
          q.emplace(nxt);
        }
      }
    }
    return *max_element(dist.begin(), dist.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 5 * 10⁴|
// * |0 <= relations.length <= min(n * (n - 1) / 2, 5 * 10⁴)|
// * |relations[j].length == 2|
// * |1 <= prevCourseⱼ, nextCourseⱼ <= n|
// * |prevCourseⱼ != nextCourseⱼ|
// * All the pairs |[prevCourseⱼ, nextCourseⱼ]| are unique.
// * |time.length == n|
// * |1 <= time[i] <= 10⁴|
// * The given graph is a directed acyclic graph.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
// Output: 8
//
// The figure above represents the given graph and the time required to complete
// each course. We start course 1 and course 2 simultaneously at month 0. Course
// 1 takes 3 months and course 2 takes 2 months to complete respectively. Thus,
// the earliest time we can start course 3 is at month 3, and the total time
// required is 3 + 5 = 8 months.

LEETCODE_SOLUTION_UNITTEST(2050, ParallelCoursesIII, example_1) {
  auto                solution  = MakeSolution();
  int                 n         = 3;
  vector<vector<int>> relations = {
      {1, 3},
      {2, 3}
  };
  vector<int> time   = {3, 2, 5};
  int         expect = 8;
  int         actual = solution->minimumTime(n, relations, time);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, relations = [[1,5],[2,5],[3,5],[3,4],[4,5]], time =
//  [1,2,3,4,5]
// Output: 12
//
// The figure above represents the given graph and the time required to complete
// each course. You can start courses 1, 2, and 3 at month 0. You can complete
// them after 1, 2, and 3 months respectively. Course 4 can be taken only after
// course 3 is completed, i.e., after 3 months. It is completed after 3 + 4 = 7
// months. Course 5 can be taken only after courses 1, 2, 3, and 4 have been
// completed, i.e., after max(1,2,3,7) = 7 months. Thus, the minimum time needed
// to complete all the courses is 7 + 5 = 12 months.

LEETCODE_SOLUTION_UNITTEST(2050, ParallelCoursesIII, example_2) {
  auto                solution  = MakeSolution();
  int                 n         = 5;
  vector<vector<int>> relations = {
      {1, 5},
      {2, 5},
      {3, 5},
      {3, 4},
      {4, 5}
  };
  vector<int> time   = {1, 2, 3, 4, 5};
  int         expect = 12;
  int         actual = solution->minimumTime(n, relations, time);
  LCD_EXPECT_EQ(expect, actual);
}
