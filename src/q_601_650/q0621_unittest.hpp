
#ifndef Q621_UNITTEST_H__
#define Q621_UNITTEST_H__
#include <gtest/gtest.h>

#include <leetcode/anyorder.hpp>

#include "q0621.hpp"
using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 621.
 *      Task Scheduler
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a characters array ‘tasks’ , representing the tasks a CPU needs
 *   to do, where each letter represents a different task. Tasks could be
 *   done in any order. Each task is done in one unit of time. For each
 *   unit of time, the CPU could complete either one task or just be
 *   However, there is a non-negative integer ‘n’ that represents the
 *   cooldown period betweentwo “same tasks” (the same letter in the
 *   array), that is that there must be at least ‘n’ units of time between
 *   any two same
 *   Return “the least number of units of times that the CPU will take to
 *   finish all the given tasks” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ task.length ≤ 10⁴’
 *   • ‘tasks[i]’ is upper-case English letter.
 *   • The integer ‘n’ is in the range ‘[0, 100]’ .
 *
 */

TEST(q621, sample_input01) {
  l621::Solution solver;
  vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
  int n = 2;
  int exp = 8;
  EXPECT_EQ(solver.leastInterval(tasks, n), exp);
}

TEST(q621, sample_input02) {
  l621::Solution solver;
  vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
  int n = 0;
  int exp = 6;
  EXPECT_EQ(solver.leastInterval(tasks, n), exp);
}

TEST(q621, sample_input03) {
  l621::Solution solver;
  vector<char> tasks = {'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  int n = 2;
  int exp = 16;
  EXPECT_EQ(solver.leastInterval(tasks, n), exp);
}

#endif