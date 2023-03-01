// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Restore IP Addresses
//
// https://leetcode.com/problems/restore-ip-addresses/
//
// Question ID: 93
// Difficult  : Medium
// Solve Date : 2021/10/05 01:53

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |93. Restore IP Addresses|:
//
// A valid IP address consists of exactly four integers separated by single
// dots. Each integer is between |0| and |255| (inclusive) and cannot have
// leading zeros.
//
//  • For example, |"0.1.2.201"| and |"192.168.1.1"| are valid IP addresses, but
//  |"0.011.255.245"|, |"192.168.1.312"| and |"192.168@1.1"| are invalid IP
//  addresses.
// Given a string |s| containing only digits, return all possible valid IP
// addresses that can be formed by inserting dots into |s|. You are not allowed
// to reorder or remove any digits in |s|. You may return the valid IP addresses
// in any order.  
//

LEETCODE_BEGIN_RESOLVING(93, RestoreIPAddresses, Solution);

class Solution {
private:
  bool valid_ip(const string &s) {
    int num = 0;
    for (const auto &c : s)
      num = num * 10 + (c - '0');
    if (num != 0 && s[0] == '0')
      return false;
    if (num == 0 && s.size() > 1)
      return false;
    return num >= 0 && num <= 255;
  }
  void helper(const string &s, string ip, vector<string> &r, int ip_cnt = 0,
              int beg = 0) {
    if (ip_cnt == 4 && beg == s.size()) {
      r.push_back(ip);
    } else if (ip_cnt < 4) {
      for (int i = 1; i < 4 && beg + i <= s.size(); ++i) {
        string current = s.substr(beg, i);
        if (valid_ip(current)) {
          if (ip_cnt == 0) {
            helper(s, current, r, ip_cnt + 1, beg + i);
          } else {
            helper(s, ip + "." + current, r, ip_cnt + 1, beg + i);
          }
        }
      }
    }
  }

public:
  vector<string> restoreIpAddresses(string s) {
    vector<string> res;
    if (s.size() > 12)
      return res;
    helper(s, "", res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 20|
// * |s| consists of digits only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "25525511135"
// Output: ["255.255.11.135","255.255.111.35"]
//

LEETCODE_SOLUTION_UNITTEST(93, RestoreIPAddresses, example_1) {
  auto           solution = MakeSolution();
  string         s        = "25525511135";
  vector<string> expect   = {"255.255.11.135", "255.255.111.35"};
  vector<string> actual   = solution->restoreIpAddresses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "0000"
// Output: ["0.0.0.0"]
//

LEETCODE_SOLUTION_UNITTEST(93, RestoreIPAddresses, example_2) {
  auto           solution = MakeSolution();
  string         s        = "0000";
  vector<string> expect   = {"0.0.0.0"};
  vector<string> actual   = solution->restoreIpAddresses(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "101023"
// Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
//

LEETCODE_SOLUTION_UNITTEST(93, RestoreIPAddresses, example_3) {
  auto           solution = MakeSolution();
  string         s        = "101023";
  vector<string> expect   = {"1.0.10.23", "1.0.102.3", "10.1.0.23", "10.10.2.3",
                             "101.0.2.3"};
  vector<string> actual   = solution->restoreIpAddresses(s);
  LCD_EXPECT_EQ(expect, actual);
}
