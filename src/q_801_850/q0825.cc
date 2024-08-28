// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Friends Of Appropriate Ages
//
// https://leetcode.com/problems/friends-of-appropriate-ages/
//
// Question ID: 825
// Difficult  : Medium
// Solve Date : 2024/08/28 20:57

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |825. Friends Of Appropriate Ages|:
//
// There are |n| persons on a social media website. You are given an integer
// array |ages| where |ages[i]| is the age of the |iᵗʰ| person. A Person |x|
// will not send a friend request to a person |y| ( |x != y|) if any of the
// following conditions is true:
//
//  • |age[y] <= 0.5 * age[x] + 7|
//
//  • |age[y] > age[x]|
//
//  • |age[y] > 100 && age[x] < 100|
// Otherwise, |x| will send a friend request to |y|.
// Note that if |x| sends a request to |y|, |y| will not necessarily send a
// request to |x|. Also, a person will not send a friend request to themself.
// Return the total number of friend requests made.
//
//

LEETCODE_BEGIN_RESOLVING(825, FriendsOfAppropriateAges, Solution);

class Solution {
public:
  int numFriendRequests(vector<int> &ages) {
    unordered_map<int, int> cnt;
    for (auto x : ages) {
      ++cnt[x];
    }
    int res = 0;
    for (auto x : cnt) {
      for (auto y : cnt) {
        if (request(x.first, y.first)) {
          res += x.second * (y.second - (x.first == y.first ? 1 : 0));
        }
      }
    }
    return res;
  }

private:
  bool request(int x, int y) {
    return !(y <= 0.5 * x + 7 || y > x || (y > 100 & x < 100));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == ages.length|
// * |1 <= n <= 2 * 10⁴|
// * |1 <= ages[i] <= 120|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ages = [16,16]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(825, FriendsOfAppropriateAges, example_1) {
  auto        solution = MakeSolution();
  vector<int> ages     = {16, 16};
  int         expect   = 2;
  int         actual   = solution->numFriendRequests(ages);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ages = [16,17,18]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(825, FriendsOfAppropriateAges, example_2) {
  auto        solution = MakeSolution();
  vector<int> ages     = {16, 17, 18};
  int         expect   = 2;
  int         actual   = solution->numFriendRequests(ages);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: ages = [20,30,100,110,120]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(825, FriendsOfAppropriateAges, example_3) {
  auto        solution = MakeSolution();
  vector<int> ages     = {20, 30, 100, 110, 120};
  int         expect   = 3;
  int         actual   = solution->numFriendRequests(ages);
  LCD_EXPECT_EQ(expect, actual);
}
