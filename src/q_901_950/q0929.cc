// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Unique Email Addresses
//
// https://leetcode.com/problems/unique-email-addresses/
//
// Question ID: 929
// Difficult  : Easy
// Solve Date : 2021/09/27 16:02

#include <iosfwd>
#include <set>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |929. Unique Email Addresses|:
//
// Every valid email consists of a local name and a domain name, separated by
// the |'@'| sign. Besides lowercase letters, the email may contain one or more
// |'.'| or |'+'|.
//
//  • For example, in |"alice@leetcode.com"|, |"alice"| is the local name, and
//  |"leetcode.com"| is the domain name.
// If you add periods |'.'| between some characters in the local name part of an
// email address, mail sent there will be forwarded to the same address without
// dots in the local name. Note that this rule does not apply to domain names.
//
//  • For example, |"alice.z@leetcode.com"| and |"alicez@leetcode.com"| forward
//  to the same email address.
// If you add a plus |'+'| in the local name, everything after the first plus
// sign will be ignored. This allows certain emails to be filtered. Note that
// this rule does not apply to domain names.
//
//  • For example, |"m.y+name@email.com"| will be forwarded to |"my@email.com"|.
// It is possible to use both of these rules at the same time.
// Given an array of strings |emails| where we send one email to each
// |emails[i]|, return the number of different addresses that actually receive
// mails.  
//

LEETCODE_BEGIN_RESOLVING(929, UniqueEmailAddresses, Solution);

class Solution {
private:
  string helper(const string &e) {
    char local[100];
    char domain[100];
    sscanf(e.c_str(), "%[^@]@%s", local, domain);
    string local_name = "";
    for (int i = 0; i < strlen(local); ++i) {
      if (local[i] == '+') {
        break;
      } else if (local[i] != '.') {
        local_name.push_back(local[i]);
      }
    }
    return local_name + "@" + domain;
  }

public:
  int numUniqueEmails(vector<string> &emails) {
    int         res = 0;
    set<string> uniq;
    for (const auto &e : emails) {
      string verified = helper(e);
      if (!uniq.count(verified)) {
        uniq.insert(verified);
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= emails.length <= 100|
// * |1 <= emails[i].length <= 100|
// * |emails[i]| consist of lowercase English letters, |'+'|, |'.'| and |'@'|.
// * Each |emails[i]| contains exactly one |'@'| character.
// * All local and domain names are non-empty.
// * Local names do not start with a |'+'| character.
// * Domain names end with the |".com"| suffix.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: emails =
//  ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
// Output: 2
//
// "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive
// mails.

LEETCODE_SOLUTION_UNITTEST(929, UniqueEmailAddresses, example_1) {
  auto           solution = MakeSolution();
  vector<string> emails   = {"test.email+alex@leetcode.com",
                             "test.e.mail+bob.cathy@leetcode.com",
                             "testemail+david@lee.tcode.com"};
  int            expect   = 2;
  int            actual   = solution->numUniqueEmails(emails);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: emails = ["a@leetcode.com","b@leetcode.com","c@leetcode.com"]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(929, UniqueEmailAddresses, example_2) {
  auto           solution = MakeSolution();
  vector<string> emails   = {"a@leetcode.com", "b@leetcode.com",
                             "c@leetcode.com"};
  int            expect   = 3;
  int            actual   = solution->numUniqueEmails(emails);
  LCD_EXPECT_EQ(expect, actual);
}
