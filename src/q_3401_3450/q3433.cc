// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Mentions Per User
//
// https://leetcode.com/problems/count-mentions-per-user/
//
// Question ID: 3433
// Difficult  : Medium
// Solve Date : 2025/12/12 19:27

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3433. Count Mentions Per User|:
//
// You are given an integer |numberOfUsers| representing the total number of
// users and an array |events| of size |n x 3|. Each |events[i]| can be either
// of the following two types:
//
//  1. Message Event: |["MESSAGE", "timestampᵢ", "mentions_stringᵢ"]|
//
//
//    • This event indicates that a set of users was mentioned in a message at
//    |timestampᵢ|.
//
//    • The |mentions_stringᵢ| string can contain one of the following tokens:
//
//
//      • |id<number>|: where |<number>| is an integer in range
//      |[0,numberOfUsers - 1]|. There can be multiple ids separated by a single
//      whitespace and may contain duplicates. This can mention even the offline
//      users.
//
//      • |ALL|: mentions all users.
//
//      • |HERE|: mentions all online users.
//
//
//
//
//
//  2. Offline Event: |["OFFLINE", "timestampᵢ", "idᵢ"]|
//
//
//    • This event indicates that the user |idᵢ| had become offline at
//    |timestampᵢ| for 60 time units. The user will automatically be online
//    again at time |timestampᵢ + 60|.
//
//
// Return an array |mentions| where |mentions[i]| represents the number of
// mentions the user with id |i| has across all |MESSAGE| events. All users are
// initially online, and if a user goes offline or comes back online, their
// status change is processed before handling any message event that occurs at
// the same timestamp. Note that a user can be mentioned multiple times in a
// single message event, and each mention should be counted separately.
//
//

LEETCODE_BEGIN_RESOLVING(3433, CountMentionsPerUser, Solution);

class Solution {
public:
  vector<int> countMentions(int numberOfUsers, vector<vector<string>> &events) {
    int n = numberOfUsers;
    sort(events.begin(), events.end(),
         [&](vector<string> &a, vector<string> &b) {
           if (a[1] != b[1])
             return stoi(a[1]) < stoi(b[1]);
           return a[0] == "OFFLINE";
         });
    vector<int> ans(n);
    vector<int> onTime(n, 0);
    for (auto &e : events) {
      int time = stoi(e[1]);
      if (e[0] == "MESSAGE") {
        if (e[2] == "ALL") {
          for (int i = 0; i < n; i++) {
            ans[i]++;
          }
        } else if (e[2] == "HERE") {
          for (int i = 0; i < n; i++) {
            if (time >= onTime[i])
              ans[i]++;
          }
        } else {
          string       s;
          stringstream ss(e[2]);
          while (ss >> s) {
            int idx = stoi(s.substr(2));
            ans[idx]++;
          }
        }
      } else {
        int idx     = stoi(e[2]);
        onTime[idx] = time + 60;
      }
    }
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= numberOfUsers <= 100|
// * |1 <= events.length <= 100|
// * |events[i].length == 3|
// * |events[i][0]| will be one of |MESSAGE| or |OFFLINE|.
// * |1 <= int(events[i][1]) <= 10⁵|
// * The number of |id<number>| mentions in any |"MESSAGE"| event is between |1|
// and |100|.
// * |0 <= <number> <= numberOfUsers - 1|
// * It is guaranteed that the user id referenced in the |OFFLINE| event is
// online at the time the event occurs.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numberOfUsers = 2, events = [["MESSAGE","10","id1
//  id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
// Output: [2,2]
//

LEETCODE_SOLUTION_UNITTEST(3433, CountMentionsPerUser, example_1) {
  auto                   solution      = MakeSolution();
  int                    numberOfUsers = 2;
  vector<vector<string>> events        = {
      {"MESSAGE", "10", "id1 id0"},
      {"OFFLINE", "11",       "0"},
      {"MESSAGE", "71",    "HERE"}
  };
  vector<int> expect = {2, 2};
  vector<int> actual = solution->countMentions(numberOfUsers, events);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: numberOfUsers = 2, events = [["MESSAGE","10","id1
//  id0"],["OFFLINE","11","0"],["MESSAGE","12","ALL"]]
// Output: [2,2]
//

LEETCODE_SOLUTION_UNITTEST(3433, CountMentionsPerUser, example_2) {
  auto                   solution      = MakeSolution();
  int                    numberOfUsers = 2;
  vector<vector<string>> events        = {
      {"MESSAGE", "10", "id1 id0"},
      {"OFFLINE", "11",       "0"},
      {"MESSAGE", "12",     "ALL"}
  };
  vector<int> expect = {2, 2};
  vector<int> actual = solution->countMentions(numberOfUsers, events);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: numberOfUsers = 2, events =
//  [["OFFLINE","10","0"],["MESSAGE","12","HERE"]]
// Output: [0,1]
//

LEETCODE_SOLUTION_UNITTEST(3433, CountMentionsPerUser, example_3) {
  auto                   solution      = MakeSolution();
  int                    numberOfUsers = 2;
  vector<vector<string>> events        = {
      {"OFFLINE", "10",    "0"},
      {"MESSAGE", "12", "HERE"}
  };
  vector<int> expect = {0, 1};
  vector<int> actual = solution->countMentions(numberOfUsers, events);
  LCD_EXPECT_EQ(expect, actual);
}
