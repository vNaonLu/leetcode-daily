// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Genetic Mutation
//
// https://leetcode.com/problems/minimum-genetic-mutation/
//
// Question ID: 433
// Difficult  : Medium
// Solve Date : 2022/03/21 16:31

#include <array>
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

// Description of |433. Minimum Genetic Mutation|:
//
// A gene string can be represented by an 8-character long string, with choices
// from |'A'|, |'C'|, |'G'|, and |'T'|. Suppose we need to investigate a
// mutation from a gene string |startGene| to a gene string |endGene| where one
// mutation is defined as one single character changed in the gene string.
//
//  • For example, |"AACCGGTT" --> "AACCGGTA"| is one mutation.
// There is also a gene bank |bank| that records all the valid gene mutations. A
// gene must be in |bank| to make it a valid gene string. Given the two gene
// strings |startGene| and |endGene| and the gene bank |bank|, return the
// minimum number of mutations needed to mutate from |startGene| to |endGene|.
// If there is no such a mutation, return |-1|. Note that the starting point is
// assumed to be valid, so it might not be included in the bank.  
//

LEETCODE_BEGIN_RESOLVING(433, MinimumGeneticMutation, Solution);

class Solution {
private:
  inline constexpr static array<char, 4> dict = {'A', 'T', 'C', 'G'};

public:
  int minMutation(string start, string end, vector<string> &bank) {
    unordered_set<string> bank_gene(bank.begin(), bank.end());
    unordered_set<string> changed;

    int           res = 0;
    queue<string> path;
    path.emplace(start);
    changed.emplace(start);

    while (!path.empty()) {
      auto temp = move(path);

      while (!temp.empty()) {
        auto s = move(temp.front());
        temp.pop();

        if (s == end)
          return res;

        for (int i = 0; i < 8; ++i) {
          auto origin = s[i];
          for (const auto &c : dict) {
            s[i] = c;
            if (bank_gene.count(s) && changed.emplace(s).second) {
              path.emplace(s);
            }
          }
          s[i] = origin;
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
// * |0 <= bank.length <= 10|
// * |startGene.length == endGene.length == bank[i].length == 8|
// * |startGene|, |endGene|, and |bank[i]| consist of only the characters |['A',
// 'C', 'G', 'T']|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(433, MinimumGeneticMutation, example_1) {
  auto           solution  = MakeSolution();
  string         startGene = "AACCGGTT";
  string         endGene   = "AACCGGTA";
  vector<string> bank      = {"AACCGGTA"};
  int            expect    = 1;
  int            actual    = solution->minMutation(startGene, endGene, bank);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: startGene = "AACCGGTT", endGene = "AAACGGTA", bank =
//  ["AACCGGTA","AACCGCTA","AAACGGTA"]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(433, MinimumGeneticMutation, example_2) {
  auto           solution  = MakeSolution();
  string         startGene = "AACCGGTT";
  string         endGene   = "AAACGGTA";
  vector<string> bank      = {"AACCGGTA", "AACCGCTA", "AAACGGTA"};
  int            expect    = 2;
  int            actual    = solution->minMutation(startGene, endGene, bank);
  LCD_EXPECT_EQ(expect, actual);
}
