#include <gtest/gtest.h>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1346.
 *       Check If N and Its Double Exist
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an array ‘arr’ of integers, check if there exists two integers
 *   ‘N’ and ‘M’ such that ‘N’ is the double of ‘M’ ( i.e. ‘N = 2 × M’
 *   More formally check if there existstwo indices ‘i’ and ‘j’ such that
 *       -  ‘i ≠ j’
 *       -  ‘0 ≤ i, j < arr.length’
 *       -  ‘arr[i] = 2 × arr[j]’ 
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘2 ≤ arr.length ≤ 500’
 *   • ‘-10^3 ≤ arr[i] ≤ 10^3’
 *
 */

struct q1346 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    bool checkIfExist(vector<int> &arr) {
      unordered_set<int> memos;
      for (auto &x : arr) {
        if (memos.count(x * 2)) {

          return true;
        } else if (!(x & 1) && memos.count(x / 2)) {
          
          return true;
        }
        memos.emplace(x);
      }

      return false;
    }
  };

  class Solution *solution;
};

TEST_F(q1346, sample_input01) {
  solution = new Solution();
  vector<int> arr = {10, 2, 5, 3};
  bool exp = true;
  bool act = solution->checkIfExist(arr);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1346, sample_input02) {
  solution = new Solution();
  vector<int> arr = {7, 1, 14, 11};
  bool exp = true;
  bool act = solution->checkIfExist(arr);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1346, sample_input03) {
  solution = new Solution();
  vector<int> arr = {3, 1, 7, 11};
  bool exp = false;
  bool act = solution->checkIfExist(arr);
  EXPECT_EQ(act, exp);
  delete solution;
}