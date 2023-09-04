// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Students Unable to Eat Lunch
//
// https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/
//
// Question ID: 1700
// Difficult  : Easy
// Solve Date : 2023/09/05 08:51

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1700. Number of Students Unable to Eat Lunch|:
//
// The school cafeteria offers circular and square sandwiches at lunch break,
// referred to by numbers |0| and |1| respectively. All students stand in a
// queue. Each student either prefers square or circular sandwiches. The number
// of sandwiches in the cafeteria is equal to the number of students. The
// sandwiches are placed in a stack. At each step:
//
//  • If the student at the front of the queue prefers the sandwich on the top
//  of the stack, they will take it and leave the queue.
//
//  • Otherwise, they will leave it and go to the queue's end.
// This continues until none of the queue students want to take the top sandwich
// and are thus unable to eat. You are given two integer arrays |students| and
// |sandwiches| where |sandwiches[i]| is the type of the
// |i^{​​​​​​th}| sandwich in the stack ( |i = 0| is the top of the
// stack) and |students[j]| is the preference of the |j^{​​​​​​th}|
// student in the initial queue ( |j = 0| is the front of the queue). Return the
// number of students that are unable to eat.
//
//

LEETCODE_BEGIN_RESOLVING(1700, NumberOfStudentsUnableToEatLunch, Solution);

class Solution {
public:
  int countStudents(vector<int> &students, vector<int> &sandwiches) {
    int        count = 0;
    int        i     = 0;
    queue<int> q;
    for (auto x : students) {
      q.push(x);
    }
    while (count < q.size() && i < sandwiches.size()) {
      if (sandwiches[i] == q.front()) {
        q.pop();
        ++i;
        count = 0;
      } else {
        q.push(q.front());
        q.pop();
        ++count;
      }
    }
    return q.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= students.length, sandwiches.length <= 100|
// * |students.length == sandwiches.length|
// * |sandwiches[i]| is |0| or |1|.
// * |students[i]| is |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
// Output: 0
// Explanation:
// - Front student leaves the top sandwich and returns to the end of the line
// making students = [1,0,0,1].
// - Front student leaves the top sandwich and returns to the end of the line
// making students = [0,0,1,1].
// - Front student takes the top sandwich and leaves the line making students =
// [0,1,1] and sandwiches = [1,0,1].
// - Front student leaves the top sandwich and returns to the end of the line
// making students = [1,1,0].
// - Front student takes the top sandwich and leaves the line making students =
// [1,0] and sandwiches = [0,1].
// - Front student leaves the top sandwich and returns to the end of the line
// making students = [0,1].
// - Front student takes the top sandwich and leaves the line making students =
// [1] and sandwiches = [1].
// - Front student takes the top sandwich and leaves the line making students =
// [] and sandwiches = []. Hence all students are able to eat.
//

LEETCODE_SOLUTION_UNITTEST(1700, NumberOfStudentsUnableToEatLunch, example_1) {
  auto        solution   = MakeSolution();
  vector<int> students   = {1, 1, 0, 0};
  vector<int> sandwiches = {0, 1, 0, 1};
  int         expect     = 0;
  int         actual     = solution->countStudents(students, sandwiches);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1700, NumberOfStudentsUnableToEatLunch, example_2) {
  auto        solution   = MakeSolution();
  vector<int> students   = {1, 1, 1, 0, 0, 1};
  vector<int> sandwiches = {1, 0, 0, 0, 1, 1};
  int         expect     = 3;
  int         actual     = solution->countStudents(students, sandwiches);
  LCD_EXPECT_EQ(expect, actual);
}
