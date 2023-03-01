#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 929.
 *      Unique Email Addresses
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Every “valid email” consists of a “local name” and a “domain name” ,
 *   separated by the ‘'@'’ sign. Besides lowercase letters, the email may
 *   contain one or more ‘'.'’ or ‘'+'’
 *       - For example, in ‘'alice@leetcode.com'’ , ‘'alice'’ is the “local
 *   name” , and ‘'leetcode.com'’ is the “domain name”
 *   If you add periods ‘'.'’ between some characters in the “local name”
 *   part of an email address, mail sent there will be forwarded to the
 *   same address without dots in the local name. Note that this rule “does
 *   not apply” to “domain names”
 *       - For example, ‘'alice.z@leetcode.com'’ and
 *   ‘'alicez@leetcode.com'’ forward to the same email
 *   If you add a plus ‘'+'’ in the “local name” , everything after the
 *   first plus sign “will be ignored” . This allows certain emails to be
 *   filtered. Note that this rule “does not apply” to “domain names”
 *       - For example, ‘'m.y+name@email.com'’ will be forwarded to
 *   ‘'my@email.com'’
 *   It is possible to use both of these rules at the same
 *   Given an array of strings ‘emails’ where we send one email to each
 *   ‘emails[i]’ , return “the number of different addresses that actually
 *   receive mails” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ emails.length ≤ 100’
 *   • ‘1 ≤ emails[i].length ≤ 100’
 *   • ‘emails[i]’ consist of lowercase English letters, ‘'+'’ , ‘'.'’ and ‘'@'’ .
 *   • Each ‘emails[i]’ contains exactly one ‘'@'’ character.
 *   • All local and domain names are non-empty.
 *   • Local names do not start with a ‘'+'’ character.
 *
 */

struct q929 : public ::testing::Test {
  // Leetcode answer here
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
      int res = 0;
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

  class Solution *solution;
};

TEST_F(q929, sample_input01) {
  solution = new Solution();
  vector<string> emails = {"test.email+alex@leetcode.com", "test.e.mail+bob.cathy@leetcode.com", "testemail+david@lee.tcode.com"};
  int exp = 2;
  EXPECT_EQ(solution->numUniqueEmails(emails), exp);
  delete solution;
}

TEST_F(q929, sample_input02) {
  solution = new Solution();
  vector<string> emails = {"a@leetcode.com", "b@leetcode.com", "c@leetcode.com"};
  int exp = 3;
  EXPECT_EQ(solution->numUniqueEmails(emails), exp);
  delete solution;
}