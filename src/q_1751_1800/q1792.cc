// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Average Pass Ratio
//
// https://leetcode.com/problems/maximum-average-pass-ratio/
//
// Question ID: 1792
// Difficult  : Medium
// Solve Date : 2024/12/15 14:36

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1792. Maximum Average Pass Ratio|:
//
// There is a school that has classes of students and each class will be having
// a final exam. You are given a 2D integer array |classes|, where |classes[i] =
// [passᵢ, totalᵢ]|. You know beforehand that in the |iᵗʰ| class, there are
// |totalᵢ| total students, but only |passᵢ| number of students will pass the
// exam. You are also given an integer |extraStudents|. There are another
// |extraStudents| brilliant students that are guaranteed to pass the exam of
// any class they are assigned to. You want to assign each of the
// |extraStudents| students to a class in a way that maximizes the average pass
// ratio across all the classes. The pass ratio of a class is equal to the
// number of students of the class that will pass the exam divided by the total
// number of students of the class. The average pass ratio is the sum of pass
// ratios of all the classes divided by the number of the classes. Return the
// maximum possible average pass ratio after assigning the |extraStudents|
// students. Answers within |10⁻⁵| of the actual answer will be accepted.
//
//

LEETCODE_BEGIN_RESOLVING(1792, MaximumAveragePassRatio, Solution);

class Solution {
public:
  double maxAverageRatio(vector<vector<int>> &classes, int extraStudents) {
    auto calculateGain = [](int passes, int totalStudents) {
      return (double)(passes + 1) / (totalStudents + 1) -
             (double)passes / totalStudents;
    };

    // Max heap to store (-gain, passes, totalStudents)
    priority_queue<pair<double, pair<int, int>>> maxHeap;
    for (const auto &singleClass : classes) {
      maxHeap.push({
          calculateGain(singleClass[0], singleClass[1]),
          {singleClass[0], singleClass[1]}
      });
    }

    // Distribute extra students
    while (extraStudents--) {
      auto [currentGain, classInfo] = maxHeap.top();
      maxHeap.pop();
      int passes        = classInfo.first;
      int totalStudents = classInfo.second;
      maxHeap.push({
          calculateGain(passes + 1, totalStudents + 1),
          {passes + 1, totalStudents + 1}
      });
    }

    // Calculate the final average pass ratio
    double totalPassRatio = 0;
    while (!maxHeap.empty()) {
      auto [_, classInfo] = maxHeap.top();
      maxHeap.pop();
      totalPassRatio += (double)classInfo.first / classInfo.second;
    }

    return totalPassRatio / classes.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= classes.length <= 10⁵|
// * |classes[i].length == 2|
// * |1 <= passᵢ <= totalᵢ <= 10⁵|
// * |1 <= extraStudents <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
// Output: 0.78333
//

LEETCODE_SOLUTION_UNITTEST(1792, MaximumAveragePassRatio, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> classes  = {
      {1, 2},
      {3, 5},
      {2, 2}
  };
  int    extraStudents = 2;
  double expect        = 0.78333;
  double actual        = solution->maxAverageRatio(classes, extraStudents);
  EXPECT_NEAR(expect, actual, 1e-5);
}

// [Example #2]
//  Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
// Output: 0.53485
//

LEETCODE_SOLUTION_UNITTEST(1792, MaximumAveragePassRatio, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> classes  = {
      {2,  4},
      {3,  9},
      {4,  5},
      {2, 10}
  };
  int    extraStudents = 4;
  double expect        = 0.53485;
  double actual        = solution->maxAverageRatio(classes, extraStudents);
  EXPECT_NEAR(expect, actual, 1e-5);
}
