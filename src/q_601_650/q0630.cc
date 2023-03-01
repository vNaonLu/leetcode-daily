// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Course Schedule III
//
// https://leetcode.com/problems/course-schedule-iii/
//
// Question ID: 630
// Difficult  : Hard
// Solve Date : 2022/06/23 18:22

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |630. Course Schedule III|:
//
// There are |n| different online courses numbered from |1| to |n|. You are
// given an array |courses| where |courses[i] = [durationᵢ, lastDayᵢ]| indicate
// that the |iᵗʰ| course should be taken continuously for |durationᵢ| days and
// must be finished before or on |lastDayᵢ|. You will start on the |1ˢᵗ| day and
// you cannot take two or more courses simultaneously. Return the maximum number
// of courses that you can take.
//

LEETCODE_BEGIN_RESOLVING(630, CourseScheduleIII, Solution);

class Solution {
public:
  int scheduleCourse(vector<vector<int>> &courses) {
    if (courses.empty()) {
      return 0;
    }
    sort(courses.begin(), courses.end(),
         [](auto &x, auto &y) { return x[1] < y[1]; });
    priority_queue<int> pq;
    int                 total = 0;
    for (auto &x : courses) {
      total += x[0];
      pq.emplace(x[0]);
      if (total > x[1]) {
        total -= pq.top();
        pq.pop();
      }
    }

    return pq.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= courses.length <= 10⁴|
// * |1 <= durationᵢ, lastDayᵢ <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
// Output: 3
// Explanation:
// There are totally 4 courses, but you can take 3 courses at most:
// First, take the 1ˢᵗ course, it costs 100 days so you will finish it on the
// 100ᵗʰ day, and ready to take the next course on the 101ˢᵗ day. Second, take
// the 3ʳᵈ course, it costs 1000 days so you will finish it on the 1100ᵗʰ day,
// and ready to take the next course on the 1101ˢᵗ day. Third, take the 2ⁿᵈ
// course, it costs 200 days so you will finish it on the 1300ᵗʰ day. The 4ᵗʰ
// course cannot be taken now, since you will finish it on the 3300ᵗʰ day, which
// exceeds the closed date.
//

LEETCODE_SOLUTION_UNITTEST(630, CourseScheduleIII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> courses  = {
      { 100,  200},
      { 200, 1300},
      {1000, 1250},
      {2000, 3200}
  };
  int expect = 3;
  int actual = solution->scheduleCourse(courses);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: courses = [[1,2]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(630, CourseScheduleIII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> courses  = {
      {1, 2}
  };
  int expect = 1;
  int actual = solution->scheduleCourse(courses);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: courses = [[3,2],[4,3]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(630, CourseScheduleIII, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> courses  = {
      {3, 2},
      {4, 3}
  };
  int expect = 0;
  int actual = solution->scheduleCourse(courses);
  LCD_EXPECT_EQ(expect, actual);
}
