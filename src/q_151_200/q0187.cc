// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Repeated DNA Sequences
//
// https://leetcode.com/problems/repeated-dna-sequences/
//
// Question ID: 187
// Difficult  : Medium
// Solve Date : 2021/09/27 13:52

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |187. Repeated DNA Sequences|:
//
// The DNA sequence is composed of a series of nucleotides abbreviated as |'A'|,
// |'C'|, |'G'|, and |'T'|.
//
//  • For example, |"ACGAATTCCG"| is a DNA sequence.
// When studying DNA, it is useful to identify repeated sequences within the
// DNA. Given a string |s| that represents a DNA sequence, return all the
// |10|-letter-long sequences (substrings) that occur more than once in a DNA
// molecule. You may return the answer in any order.  
//

LEETCODE_BEGIN_RESOLVING(187, RepeatedDNASequences, Solution);

class Solution {
public:
  vector<string> findRepeatedDnaSequences(string s) {
    unordered_map<string, int> keep;
    vector<string>             res;
    for (int i = 0; i < (int)s.size() - 10 + 1; ++i) {
      ++keep[s.substr(i, 10)];
    }
    for (auto it = keep.begin(); it != keep.end(); ++it) {
      if (it->second > 1)
        res.push_back(it->first);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s[i]| is either |'A'|, |'C'|, |'G'|, or |'T'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
// Output: ["AAAAACCCCC","CCCCCAAAAA"]
//

LEETCODE_SOLUTION_UNITTEST(187, RepeatedDNASequences, example_1) {
  auto           solution = MakeSolution();
  string         s        = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
  vector<string> expect   = {"AAAAACCCCC", "CCCCCAAAAA"};
  vector<string> actual   = solution->findRepeatedDnaSequences(s);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "AAAAAAAAAAAAA"
// Output: ["AAAAAAAAAA"]
//

LEETCODE_SOLUTION_UNITTEST(187, RepeatedDNASequences, example_2) {
  auto           solution = MakeSolution();
  string         s        = "AAAAAAAAAAAAA";
  vector<string> expect   = {"AAAAAAAAAA"};
  vector<string> actual   = solution->findRepeatedDnaSequences(s);
  EXPECT_ANYORDER_EQ(expect, actual);
}
