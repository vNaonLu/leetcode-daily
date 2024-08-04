// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Subdomain Visit Count
//
// https://leetcode.com/problems/subdomain-visit-count/
//
// Question ID: 811
// Difficult  : Medium
// Solve Date : 2024/08/04 14:34

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |811. Subdomain Visit Count|:
//
// A website domain |"discuss.leetcode.com"| consists of various subdomains. At
// the top level, we have |"com"|, at the next level, we have |"leetcode.com"|
// and at the lowest level, |"discuss.leetcode.com"|. When we visit a domain
// like |"discuss.leetcode.com"|, we will also visit the parent domains
// |"leetcode.com"| and |"com"| implicitly. A count-paired domain is a domain
// that has one of the two formats |"rep d1.d2.d3"| or |"rep d1.d2"| where |rep|
// is the number of visits to the domain and |d1.d2.d3| is the domain itself.
//
//  • For example, |"9001 discuss.leetcode.com"| is a count-paired domain that
//  indicates that |discuss.leetcode.com| was visited |9001| times.
// Given an array of count-paired domains |cpdomains|, return an array of the
// count-paired domains of each subdomain in the input. You may return the
// answer in any order.
//
//

LEETCODE_BEGIN_RESOLVING(811, SubdomainVisitCount, Solution);

class Solution {
public:
  vector<string> subdomainVisits(vector<string> &cpdomains) {
    unordered_map<string, int> visits;
    for (auto &s : cpdomains) {
      auto space = s.find_first_of(' ');
      int  cnt   = stoi(s.substr(0, space));
      auto sub   = subdomains(s.begin() + space + 1, s.end());
      for (auto &ss : sub) {
        visits[ss] += cnt;
      }
    }
    vector<string> res;
    for (auto &[sub, cnt] : visits) {
      res.emplace_back(to_string(cnt) + " " + sub);
    }
    return res;
  }

private:
  template <typename It>
  vector<string> subdomains(It beg, It end) {
    vector<string> res;
    res.emplace_back(beg, end);
    while (beg != end) {
      if (*beg++ == '.') {
        res.emplace_back(beg, end);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= cpdomain.length <= 100|
// * |1 <= cpdomain[i].length <= 100|
// * |cpdomain[i]| follows either the |"repᵢ d1ᵢ.d2ᵢ.d3ᵢ"| format or the |"repᵢ
// d1ᵢ.d2ᵢ"| format.
// * |repᵢ| is an integer in the range |[1, 10⁴]|.
// * |d1ᵢ|, |d2ᵢ|, and |d3ᵢ| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: cpdomains = ["9001 discuss.leetcode.com"]
// Output: ["9001 leetcode.com","9001 discuss.leetcode.com","9001 com"]
//

LEETCODE_SOLUTION_UNITTEST(811, SubdomainVisitCount, example_1) {
  auto           solution  = MakeSolution();
  vector<string> cpdomains = {"9001 discuss.leetcode.com"};
  vector<string> expect    = {"9001 leetcode.com", "9001 discuss.leetcode.com",
                              "9001 com"};
  vector<string> actual    = solution->subdomainVisits(cpdomains);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: cpdomains = ["900 google.mail.com", "50 yahoo.com", "1
//  intel.mail.com", "5 wiki.org"]
// Output: ["901 mail.com","50 yahoo.com","900 google.mail.com","5 wiki.org","5
// org","1 intel.mail.com","951 com"]
//

LEETCODE_SOLUTION_UNITTEST(811, SubdomainVisitCount, example_2) {
  auto           solution  = MakeSolution();
  vector<string> cpdomains = {"900 google.mail.com", "50 yahoo.com",
                              "1 intel.mail.com", "5 wiki.org"};
  vector<string> expect    = {
      "901 mail.com", "50 yahoo.com", "900 google.mail.com",
      "5 wiki.org",   "5 org",        "1 intel.mail.com",
      "951 com"};
  vector<string> actual = solution->subdomainVisits(cpdomains);
  EXPECT_ANYORDER_EQ(expect, actual);
}
