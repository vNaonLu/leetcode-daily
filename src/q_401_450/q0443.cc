// Copyright 2023 Naon Lu
//
// This file describes the solution of
// String Compression
//
// https://leetcode.com/problems/string-compression/
//
// Question ID: 443
// Difficult  : Medium
// Solve Date : 2023/03/02 20:03

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |443. String Compression|:
//
// Given an array of characters |chars|, compress it using the following
// algorithm: Begin with an empty string |s|. For each group of consecutive
// repeating characters in |chars|:
//
//  • If the group's length is |1|, append the character to |s|.
//
//  • Otherwise, append the character followed by the group's length.
// The compressed string |s| should not be returned separately, but instead, be
// stored in the input character array |chars|. Note that group lengths that are
// |10| or longer will be split into multiple characters in |chars|. After you
// are done modifying the input array, return the new length of the array. You
// must write an algorithm that uses only constant extra space.
//

LEETCODE_BEGIN_RESOLVING(443, StringCompression, Solution);

class Solution {
public:
  int compress(vector<char> &chars) {
    int i = 0;
    int j = 0;
    while (i < chars.size()) {
      int freq = 1;
      while (i < chars.size() - 1 && chars[i] == chars[i + 1]) {
        ++freq;
        ++i;
      }
      chars[j++] = chars[i++];
      if (freq > 1) {
        for (auto c : to_string(freq)) {
          chars[j++] = c;
        }
      }
    }
    return j;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= chars.length <= 2000|
// * |chars[i]| is a lowercase English letter, uppercase English letter, digit,
// or symbol.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: chars = ["a","a","b","b","c","c","c"]
// Output: Return 6, and the first 6 characters of the input array should be:
// ["a","2","b","2","c","3"]
//
// The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".

LEETCODE_SOLUTION_UNITTEST(443, StringCompression, example_1) {
  auto         solution     = MakeSolution();
  vector<char> chars        = {'a', 'a', 'b', 'b', 'c', 'c', 'c'};
  int          expect       = 6;
  vector<char> expect_chars = {'a', '2', 'b', '2', 'c', '3', 'c'};
  int          actual       = solution->compress(chars);
  LCD_EXPECT_EQ(expect, actual);
  LCD_EXPECT_EQ(expect_chars, chars);
}

// [Example #2]
//  Input: chars = ["a"]
// Output: Return 1, and the first character of the input array should be: ["a"]
//
// The only group is "a", which remains uncompressed since it's a single
// character.

LEETCODE_SOLUTION_UNITTEST(443, StringCompression, example_2) {
  auto         solution     = MakeSolution();
  vector<char> chars        = {'a'};
  int          expect       = 1;
  vector<char> expect_chars = {'a'};
  int          actual       = solution->compress(chars);
  LCD_EXPECT_EQ(expect, actual);
  LCD_EXPECT_EQ(expect_chars, chars);
}

// [Example #3]
//  Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
// Output: Return 4, and the first 4 characters of the input array should be:
// ["a","b","1","2"].
//
// The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".

LEETCODE_SOLUTION_UNITTEST(443, StringCompression, example_3) {
  auto         solution     = MakeSolution();
  vector<char> chars        = {'a', 'b', 'b', 'b', 'b', 'b', 'b',
                               'b', 'b', 'b', 'b', 'b', 'b'};
  int          expect       = 4;
  vector<char> expect_chars = {'a', 'b', '1', '2', 'b', 'b', 'b',
                               'b', 'b', 'b', 'b', 'b', 'b'};
  int          actual       = solution->compress(chars);
  LCD_EXPECT_EQ(expect, actual);
  LCD_EXPECT_EQ(expect_chars, chars);
}
