// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Iterator for Combination
//
// https://leetcode.com/problems/iterator-for-combination/
//
// Question ID: 1286
// Difficult  : Medium
// Solve Date : 2021/11/14 13:18

#include <iosfwd>
#include <queue>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1286. Iterator for Combination|:
//
// Design the |CombinationIterator| class:
//
//  • |CombinationIterator(string characters, int combinationLength)|
//  Initializes the object with a string |characters| of sorted distinct
//  lowercase English letters and a number |combinationLength| as arguments.
//
//  • |next()| Returns the next combination of length |combinationLength| in
//  lexicographical order.
//
//  • |hasNext()| Returns |true| if and only if there exists a next combination.
//  
//

LEETCODE_BEGIN_RESOLVING(1286, IteratorForCombination, CombinationIterator);

class CombinationIterator {
private:
  queue<string> _combine;
  void          combine_helper(const string &s, int L, string &t, int beg = 0) {
    if (t.size() == L) {
      _combine.emplace(t);
    } else {
      for (int i = beg; i < s.size(); ++i) {
        t.push_back(s[i]);
        combine_helper(s, L, t, i + 1);
        t.pop_back();
      }
    }
  }

public:
  CombinationIterator(string characters, int combinationLength) {
    string tmp;
    combine_helper(characters, combinationLength, tmp);
  }
  string next() {
    auto res = _combine.front();
    _combine.pop();
    return res;
  }
  bool hasNext() { return !_combine.empty(); }
};

LEETCODE_END_RESOLVING(CombinationIterator);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= combinationLength <= characters.length <= 15|
// * All the characters of |characters| are unique.
// * At most |10⁴| calls will be made to |next| and |hasNext|.
// * It is guaranteed that all calls of the function |next| are valid.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["CombinationIterator", "next", "hasNext", "next", "hasNext", "next",
//  "hasNext"]
// [["abc", 2], [], [], [], [], [], []]
// Output: [null, "ab", true, "ac", true, "bc", false]
//
// CombinationIterator itr = new CombinationIterator("abc", 2);
// itr.next(); // return "ab"
// itr.hasNext(); // return True
// itr.next(); // return "ac"
// itr.hasNext(); // return True
// itr.next(); // return "bc"
// itr.hasNext(); // return False

LEETCODE_SOLUTION_UNITTEST(1286, IteratorForCombination, example_1) {
  string s0_characters        = "abc";
  int    s0_combinationLength = 2;
  auto   combination_iterator =
      MakeCombinationIterator(s0_characters, s0_combinationLength);
  string s1_expect = "ab";
  string s1_actual = combination_iterator->next();
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  bool s2_expect = true;
  bool s2_actual = combination_iterator->hasNext();
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  string s3_expect = "ac";
  string s3_actual = combination_iterator->next();
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  bool s4_expect = true;
  bool s4_actual = combination_iterator->hasNext();
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  string s5_expect = "bc";
  string s5_actual = combination_iterator->next();
  LCD_EXPECT_EQ(s5_expect, s5_actual);
  bool s6_expect = false;
  bool s6_actual = combination_iterator->hasNext();
  LCD_EXPECT_EQ(s6_expect, s6_actual);
}
