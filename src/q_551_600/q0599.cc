// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Index Sum of Two Lists
//
// https://leetcode.com/problems/minimum-index-sum-of-two-lists/
//
// Question ID: 599
// Difficult  : Easy
// Solve Date : 2023/06/01 18:54

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |599. Minimum Index Sum of Two Lists|:
//
// Given two arrays of strings |list1| and |list2|, find the common strings with
// the least index sum. A common string is a string that appeared in both
// |list1| and |list2|. A common string with the least index sum is a common
// string such that if it appeared at |list1[i]| and |list2[j]| then |i + j|
// should be the minimum value among all the other common strings. Return all
// the common strings with the least index sum. Return the answer in any order.
//
//

LEETCODE_BEGIN_RESOLVING(599, MinimumIndexSumOfTwoLists, Solution);

class Solution {
public:
  vector<string> findRestaurant(vector<string> &list1, vector<string> &list2) {
    unordered_map<string, int> memo;
    for (int i = 0; i < list1.size(); ++i) {
      memo[std::move(list1[i])] = i;
    }
    vector<string> res;
    int            curr_sum = list1.size() + list2.size();
    for (int i = 0; i < list2.size(); ++i) {
      auto &w  = list2[i];
      auto  it = memo.find(w);
      if (it != memo.end()) {
        auto sum = it->second + i;
        if (curr_sum > sum) {
          res.clear();
          curr_sum = sum;
        }
        if (curr_sum == sum) {
          res.emplace_back(w);
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= list1.length, list2.length <= 1000|
// * |1 <= list1[i].length, list2[i].length <= 30|
// * |list1[i]| and |list2[i]| consist of spaces |' '| and English letters.
// * All the strings of |list1| are unique.
// * All the strings of |list2| are unique.
// * There is at least a common string between |list1| and |list2|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 =
//  ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
// Output: ["Shogun"]
//
// The only common string is "Shogun".

LEETCODE_SOLUTION_UNITTEST(599, MinimumIndexSumOfTwoLists, example_1) {
  auto           solution = MakeSolution();
  vector<string> list1    = {"Shogun", "Tapioca Express", "Burger King", "KFC"};
  vector<string> list2    = {"Piatti", "The Grill at Torrey Pines",
                             "Hungry Hunter Steakhouse", "Shogun"};
  vector<string> expect   = {"Shogun"};
  vector<string> actual   = solution->findRestaurant(list1, list2);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 =
//  ["KFC","Shogun","Burger King"]
// Output: ["Shogun"]
//
// The common string with the least index sum is "Shogun" with index sum = (0 +
// 1) = 1.

LEETCODE_SOLUTION_UNITTEST(599, MinimumIndexSumOfTwoLists, example_2) {
  auto           solution = MakeSolution();
  vector<string> list1    = {"Shogun", "Tapioca Express", "Burger King", "KFC"};
  vector<string> list2    = {"KFC", "Shogun", "Burger King"};
  vector<string> expect   = {"Shogun"};
  vector<string> actual   = solution->findRestaurant(list1, list2);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: list1 = ["happy","sad","good"], list2 = ["sad","happy","good"]
// Output: ["sad","happy"]
//
// There are three common strings:
// "happy" with index sum = (0 + 1) = 1.
// "sad" with index sum = (1 + 0) = 1.
// "good" with index sum = (2 + 2) = 4.
// The strings with the least index sum are "sad" and "happy".

LEETCODE_SOLUTION_UNITTEST(599, MinimumIndexSumOfTwoLists, example_3) {
  auto           solution = MakeSolution();
  vector<string> list1    = {"happy", "sad", "good"};
  vector<string> list2    = {"sad", "happy", "good"};
  vector<string> expect   = {"sad", "happy"};
  vector<string> actual   = solution->findRestaurant(list1, list2);
  EXPECT_ANYORDER_EQ(expect, actual);
}
