#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 1306.
 *       Jump Game III
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an array of non-negative integers ‘arr’ , you are initially
 *   positioned at ‘start’ index of the array. When you are at index ‘i’ ,
 *   you can jumpto ‘i + arr[i]’ or ‘i - arr[i]’ , check if you can reach
 *   to “any” index with value
 *   Notice that you can not jump outside of the array at any time.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ arr.length ≤ 5 × 10⁴’
 *   • ‘0 ≤ arr[i] <arr.length’
 *   • ‘0 ≤ start < arr.length’
 *
 */

struct q1306 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    bool canReach(vector<int>& arr, int start) {
      queue<int> q;
      int n = arr.size();
      q.push(start);
      while (!q.empty()) {
        int f = q.front();
        q.pop();
        if (f - arr[f] >= 0) {
          if (arr[f - arr[f]] == 0) {
            return true;
          } else if (arr[f - arr[f]] > 0) {
            q.push(f - arr[f]);
          }
        }
        if (f + arr[f] < n) {
          if (arr[f + arr[f]] == 0) {
            return true;
          } else if (arr[f + arr[f]] > 0) {
            q.push(f + arr[f]);
          }
        }
        arr[f] = -1;
      }
      return false;
    }
  };

  class Solution *solution;
};

TEST_F(q1306, sample_input01) {
  solution = new Solution();
  vector<int> arr = {4, 2, 3, 0, 3, 1, 2};
  int start = 5;
  bool exp = true;
  EXPECT_EQ(solution->canReach(arr, start), exp);
  delete solution;
}

TEST_F(q1306, sample_input02) {
  solution = new Solution();
  vector<int> arr = {4, 2, 3, 0, 3, 1, 2};
  int start = 0;
  bool exp = true;
  EXPECT_EQ(solution->canReach(arr, start), exp);
  delete solution;
}

TEST_F(q1306, sample_input03) {
  solution = new Solution();
  vector<int> arr = {3, 0, 2, 1, 2};
  int start = 2;
  bool exp = false;
  EXPECT_EQ(solution->canReach(arr, start), exp);
  delete solution;
}