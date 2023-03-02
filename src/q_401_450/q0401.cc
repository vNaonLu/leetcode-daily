// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Watch
//
// https://leetcode.com/problems/binary-watch/
//
// Question ID: 401
// Difficult  : Easy
// Solve Date : 2022/08/15 18:05

#include <bitset>
#include <iosfwd>
#include <set>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |401. Binary Watch|:
//
// A binary watch has 4 LEDs on the top to represent the hours (0-11), and 6
// LEDs on the bottom to representthe minutes (0-59). Each LED represents a zero
// or one, with the least significant bit on the right.
//
//  • For example, the below binary watch reads |"4:51"|.
// ![img](https://assets.leetcode.com/uploads/2021/04/08/binarywatch.jpg)
// Given an integer |turnedOn| which represents the number of LEDs that are
// currently on (ignoring the PM), return all possible times the watch could
// represent. You may return the answer in any order. The hour must not contain
// a leading zero.
//
//  • For example, |"01:00"| is not valid. It should be |"1:00"|.
// The minute must be consist of two digits and may contain a leading zero.
//
//  • For example, |"10:2"| is not valid. It should be |"10:02"|.
//

LEETCODE_BEGIN_RESOLVING(401, BinaryWatch, Solution);

class Solution {
private:
  void bt(string &s, int start, int num, vector<string> &res) {
    int hour   = bitset<4>(s.substr(6, 4)).to_ulong();
    int minute = bitset<6>(s.substr(0, 6)).to_ulong();
    if (hour > 11 || minute > 59) {
      return;
    }

    if (num == 0) {
      res.emplace_back(to_string(hour) + ":" + (minute < 10 ? "0" : "") +
                       to_string(minute));
      return;
    }

    if (start == s.size()) {
      return;
    }

    for (int i = start; i < s.size(); ++i) {
      s[i] = '1';
      bt(s, i + 1, num - 1, res);
      s[i] = '0';
    }
  }

public:
  vector<string> readBinaryWatch(int turnedOn) {
    auto res = vector<string>();
    auto s   = string("0000000000");
    bt(s, 0, turnedOn, res);

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= turnedOn <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: turnedOn = 1
// Output:
// ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
//

LEETCODE_SOLUTION_UNITTEST(401, BinaryWatch, example_1) {
  auto           solution = MakeSolution();
  int            turnedOn = 1;
  vector<string> expect   = {"0:01", "0:02", "0:04", "0:08", "0:16",
                             "0:32", "1:00", "2:00", "4:00", "8:00"};
  vector<string> actual   = solution->readBinaryWatch(turnedOn);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: turnedOn = 9
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(401, BinaryWatch, example_2) {
  auto           solution = MakeSolution();
  int            turnedOn = 9;
  vector<string> expect   = {};
  vector<string> actual   = solution->readBinaryWatch(turnedOn);
  EXPECT_ANYORDER_EQ(expect, actual);
}
