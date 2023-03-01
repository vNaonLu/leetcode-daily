// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Queue Reconstruction by Height
//
// https://leetcode.com/problems/queue-reconstruction-by-height/
//
// Question ID: 406
// Difficult  : Medium
// Solve Date : 2022/06/29 18:37

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |406. Queue Reconstruction by Height|:
//
// You are given an array of people, |people|, which are the attributes of some
// people in a queue (not necessarily in order). Each |people[i] = [hᵢ, kᵢ]|
// represents the |iᵗʰ| person of height |hᵢ| with exactly |kᵢ| other people in
// front who have a height greater than or equal to |hᵢ|. Reconstruct and return
// the queue that is represented by the input array |people|. The returned queue
// should be formatted as an array |queue|, where |queue[j] = [hⱼ, kⱼ]| is the
// attributes of the |jᵗʰ| person in the queue ( |queue[0]| is the person at the
// front of the queue).
//

LEETCODE_BEGIN_RESOLVING(406, QueueReconstructionByHeight, Solution);

class Solution {
public:
  vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
    sort(people.begin(), people.end(), [](auto &x, auto &y) {
      return x[0] == y[0] ? x[1] < y[1] : x[0] > y[0];
    });
    vector<vector<int>> res;

    for (auto &v : people) {
      res.insert(res.begin() + v[1], v);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= people.length <= 2000|
// * |0 <= hᵢ <= 10⁶|
// * |0 <= kᵢ < people.length|
// * It is guaranteed that the queue can be reconstructed.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
// Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
//
// Person 0 has height 5 with no other people taller or the same height in
// front. Person 1 has height 7 with no other people taller or the same height
// in front. Person 2 has height 5 with two persons taller or the same height in
// front, which is person 0 and 1. Person 3 has height 6 with one person taller
// or the same height in front, which is person 1. Person 4 has height 4 with
// four people taller or the same height in front, which are people 0, 1, 2,
// and 3. Person 5 has height 7 with one person taller or the same height in
// front, which is person 1. Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the
// reconstructed queue.

LEETCODE_SOLUTION_UNITTEST(406, QueueReconstructionByHeight, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> people   = {
      {7, 0},
      {4, 4},
      {7, 1},
      {5, 0},
      {6, 1},
      {5, 2}
  };
  vector<vector<int>> expect = {
      {5, 0},
      {7, 0},
      {5, 2},
      {6, 1},
      {4, 4},
      {7, 1}
  };
  vector<vector<int>> actual = solution->reconstructQueue(people);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
// Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
//

LEETCODE_SOLUTION_UNITTEST(406, QueueReconstructionByHeight, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> people   = {
      {6, 0},
      {5, 0},
      {4, 0},
      {3, 2},
      {2, 2},
      {1, 4}
  };
  vector<vector<int>> expect = {
      {4, 0},
      {5, 0},
      {2, 2},
      {3, 2},
      {1, 4},
      {6, 0}
  };
  vector<vector<int>> actual = solution->reconstructQueue(people);
  LCD_EXPECT_EQ(expect, actual);
}
