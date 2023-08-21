// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Students Doing Homework at a Given Time
//
// https://leetcode.com/problems/number-of-students-doing-homework-at-a-given-time/
//
// Question ID: 1450
// Difficult  : Easy
// Solve Date : 2023/08/17 22:28

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1450. Number of Students Doing Homework at a Given Time|:
//
// Given two integer arrays |startTime| and |endTime| and given an integer
// |queryTime|. The |ith| student started doing their homework at the time
// |startTime[i]| and finished it at time |endTime[i]|. Return the number of
// students doing their homework at time |queryTime|. More formally, return the
// number of students where |queryTime| lays in the interval |[startTime[i],
// endTime[i]]| inclusive.
//
//

LEETCODE_BEGIN_RESOLVING(1450, NumberOfStudentsDoingHomeworkAtAGivenTime,
                         Solution);

class Solution {
public:
  int busyStudent(vector<int> &startTime, vector<int> &endTime, int queryTime) {
    int res = 0;
    for (int i = 0; i < startTime.size(); ++i) {
      if (queryTime >= startTime[i] && queryTime <= endTime[i]) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |startTime.length == endTime.length|
// * |1 <= startTime.length <= 100|
// * |1 <= startTime[i] <= endTime[i] <= 1000|
// * |1 <= queryTime <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: startTime = [1,2,3], endTime = [3,2,7], queryTime = 4
// Output: 1
//
// We have 3 students where:
// The first student started doing homework at time 1 and finished at time 3 and
// wasn't doing anything at time 4. The second student started doing homework at
// time 2 and finished at time 2 and also wasn't doing anything at time 4. The
// third student started doing homework at time 3 and finished at time 7 and was
// the only student doing homework at time 4.

LEETCODE_SOLUTION_UNITTEST(1450, NumberOfStudentsDoingHomeworkAtAGivenTime,
                           example_1) {
  auto        solution  = MakeSolution();
  vector<int> startTime = {1, 2, 3};
  vector<int> endTime   = {3, 2, 7};
  int         queryTime = 4;
  int         expect    = 1;
  int         actual    = solution->busyStudent(startTime, endTime, queryTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: startTime = [4], endTime = [4], queryTime = 4
// Output: 1
//
// The only student was doing their homework at the queryTime.

LEETCODE_SOLUTION_UNITTEST(1450, NumberOfStudentsDoingHomeworkAtAGivenTime,
                           example_2) {
  auto        solution  = MakeSolution();
  vector<int> startTime = {4};
  vector<int> endTime   = {4};
  int         queryTime = 4;
  int         expect    = 1;
  int         actual    = solution->busyStudent(startTime, endTime, queryTime);
  LCD_EXPECT_EQ(expect, actual);
}
