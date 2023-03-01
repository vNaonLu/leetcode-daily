// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Open the Lock
//
// https://leetcode.com/problems/open-the-lock/
//
// Question ID: 752
// Difficult  : Medium
// Solve Date : 2022/02/11 21:58

#include <iosfwd>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |752. Open the Lock|:
//
// You have a lock in front of you with 4 circular wheels. Each wheel has 10
// slots: |'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'|. The wheels can
// rotate freely and wrap around: for example we can turn |'9'| to be |'0'|, or
// |'0'| to be |'9'|. Each move consists of turning one wheel one slot. The lock
// initially starts at |'0000'|, a string representing the state of the 4
// wheels. You are given a list of |deadends| dead ends, meaning if the lock
// displays any of these codes, the wheels of the lock will stop turning and you
// will be unable to open it. Given a |target| representing the value of the
// wheels that will unlock the lock, return the minimum total number of turns
// required to open the lock, or -1 if it is impossible.  
//

LEETCODE_BEGIN_RESOLVING(752, OpenTheLock, Solution);

class Solution {
private:
  unordered_set<int> dends;
  unordered_set<int> memos;
  inline int         encode(uint8_t (&n)[4]) noexcept {
    int *res = reinterpret_cast<int *>(n);
    return *res;
  }
  inline int encode(const string &s) noexcept {
    uint8_t temp[4];
    for (int i = 0; i < 4; ++i)
      temp[i] = s[i] - '0';
    return encode(temp);
  }
  inline void decode(int n, uint8_t (&out)[4]) noexcept {
    uint8_t *temp = reinterpret_cast<uint8_t *>(&n);
    memcpy(out, temp, 4);
  }
  inline bool check(int n) noexcept {
    return memos.find(n) == memos.end() && dends.find(n) == dends.end();
  }

public:
  int openLock(vector<string> &deadends, string target) {
    int        t   = encode(target);
    int        res = 0;
    queue<int> step;
    for (const auto &s : deadends) {
      int code = encode(s);
      if (code == 0)
        return -1;
      dends.insert(code);
    }
    step.push(0);
    memos.insert(0);
    while (true != step.empty()) {
      queue<int> curr;
      swap(curr, step);
      while (true != curr.empty()) {
        uint8_t lock[4];
        decode(curr.front(), lock);
        if (curr.front() == t)
          return res;
        curr.pop();
        /// turn once
        for (int i = 0; i < 4; ++i) {
          uint8_t old = lock[i];
          lock[i]     = old == 9 ? 0 : old + 1;
          int frward  = encode(lock);
          lock[i]     = old == 0 ? 9 : old - 1;
          int bkward  = encode(lock);
          lock[i]     = old;
          if (check(frward)) {
            memos.insert(frward);
            step.push(frward);
          }
          if (check(bkward)) {
            memos.insert(bkward);
            step.push(bkward);
          }
        }
      }
      ++res;
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= deadends.length <= 500|
// * |deadends[i].length == 4|
// * |target.length == 4|
// * target will not be in the list |deadends|.
// * |target| and |deadends[i]| consist of digits only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
// Output: 6
//
// A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" ->
// "1201" -> "1202" -> "0202". Note that a sequence like "0000" -> "0001" ->
// "0002" -> "0102" -> "0202" would be invalid, because the wheels of the lock
// become stuck after the display becomes the dead end "0102".

LEETCODE_SOLUTION_UNITTEST(752, OpenTheLock, example_1) {
  auto           solution = MakeSolution();
  vector<string> deadends = {"0201", "0101", "0102", "1212", "2002"};
  string         target   = "0202";
  int            expect   = 6;
  int            actual   = solution->openLock(deadends, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: deadends = ["8888"], target = "0009"
// Output: 1
//
// We can turn the last wheel in reverse to move from "0000" -> "0009".

LEETCODE_SOLUTION_UNITTEST(752, OpenTheLock, example_2) {
  auto           solution = MakeSolution();
  vector<string> deadends = {"8888"};
  string         target   = "0009";
  int            expect   = 1;
  int            actual   = solution->openLock(deadends, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"],
//  target = "8888"
// Output: -1
//
// We cannot reach the target without getting stuck.

LEETCODE_SOLUTION_UNITTEST(752, OpenTheLock, example_3) {
  auto           solution = MakeSolution();
  vector<string> deadends = {"8887", "8889", "8878", "8898",
                             "8788", "8988", "7888", "9888"};
  string         target   = "8888";
  int            expect   = -1;
  int            actual   = solution->openLock(deadends, target);
  LCD_EXPECT_EQ(expect, actual);
}
