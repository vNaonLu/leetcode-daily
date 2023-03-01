// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Student that Will Replace the Chalk
//
// https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/
//
// Question ID: 1894
// Difficult  : Medium
// Solve Date : 2022/07/15 21:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1894. Find the Student that Will Replace the Chalk|:
//
// There are |n| students in a class numbered from |0| to |n - 1|. The teacher
// will give each student a problem starting with the student number |0|, then
// the student number |1|, and so on until the teacher reaches the student
// number |n - 1|. After that, the teacher will restart the process, starting
// with the student number |0| again. You are given a 0-indexed integer array
// |chalk| and an integer |k|. There are initially |k| pieces of chalk. When the
// student number |i| is given a problem to solve, they will use |chalk[i]|
// pieces of chalk to solve that problem. However, if the current number of
// chalk pieces is strictly less than |chalk[i]|, then the student number |i|
// will be asked to replace the chalk. Return the index of the student that will
// replace the chalk.
//

LEETCODE_BEGIN_RESOLVING(1894, FindTheStudentThatWillReplaceTheChalk, Solution);

class Solution {
public:
  int chalkReplacer(vector<int> &chalk, int k) {
    vector<int64_t> accum(chalk.begin(), chalk.end());
    for (auto it = accum.begin() + 1; it != accum.end(); ++it) {
      *it += *(it - 1);
    }
    k %= accum.back();

    return upper_bound(accum.begin(), accum.end(), k) - accum.begin();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |chalk.length == n|
// * |1 <= n <= 10⁵|
// * |1 <= chalk[i] <= 10⁵|
// * |1 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: chalk = [5,1,5], k = 22
// Output: 0
//
// The students go in turns as follows:
// - Student number 0 uses 5 chalk, so k = 17.
// - Student number 1 uses 1 chalk, so k = 16.
// - Student number 2 uses 5 chalk, so k = 11.
// - Student number 0 uses 5 chalk, so k = 6.
// - Student number 1 uses 1 chalk, so k = 5.
// - Student number 2 uses 5 chalk, so k = 0.
// Student number 0 does not have enough chalk, so they will have to replace it.

LEETCODE_SOLUTION_UNITTEST(1894, FindTheStudentThatWillReplaceTheChalk,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> chalk    = {5, 1, 5};
  int         k        = 22;
  int         expect   = 0;
  int         actual   = solution->chalkReplacer(chalk, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: chalk = [3,4,1,2], k = 25
// Output: 1
//
// The students go in turns as follows:
// - Student number 0 uses 3 chalk so k = 22.
// - Student number 1 uses 4 chalk so k = 18.
// - Student number 2 uses 1 chalk so k = 17.
// - Student number 3 uses 2 chalk so k = 15.
// - Student number 0 uses 3 chalk so k = 12.
// - Student number 1 uses 4 chalk so k = 8.
// - Student number 2 uses 1 chalk so k = 7.
// - Student number 3 uses 2 chalk so k = 5.
// - Student number 0 uses 3 chalk so k = 2.
// Student number 1 does not have enough chalk, so they will have to replace it.

LEETCODE_SOLUTION_UNITTEST(1894, FindTheStudentThatWillReplaceTheChalk,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> chalk    = {3, 4, 1, 2};
  int         k        = 25;
  int         expect   = 1;
  int         actual   = solution->chalkReplacer(chalk, k);
  LCD_EXPECT_EQ(expect, actual);
}
