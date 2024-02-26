// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Pushes to Type Word I
//
// https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/
//
// Question ID: 3014
// Difficult  : Easy
// Solve Date : 2024/02/26 19:09

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3014. Minimum Number of Pushes to Type Word I|:
//
// You are given a string |word| containing distinct lowercase English letters.
// Telephone keypads have keys mapped with distinct collections of lowercase
// English letters, which can be used to form words by pushing them. For
// example, the key |2| is mapped with |["a","b","c"]|, we need to push the key
// one time to type |"a"|, two times to type |"b"|, and three times to type
// |"c"| . It is allowed to remap the keys numbered |2| to |9| to distinct
// collections of letters. The keys can be remapped to any amount of letters,
// but each letter must be mapped to exactly one key. You need to find the
// minimum number of times the keys will be pushed to type the string |word|.
// Return the minimum number of pushes needed to type |word| after remapping the
// keys. An example mapping of letters to keys on a telephone keypad is given
// below. Note that |1|, |*|, |#|, and |0| do not map to any letters.
// ![img](https://assets.leetcode.com/uploads/2023/12/26/keypaddesc.png)
//
//

LEETCODE_BEGIN_RESOLVING(3014, MinimumNumberOfPushesToTypeWordI, Solution);

class Solution {
public:
  int minimumPushes(string word) {
    int n = word.size();
    if (n <= 8) {
      return n;
    } else if (n <= 16) {
      return 8 + (n - 8) * 2;
    } else if (n <= 24) {
      return 8 + 16 + (n - 16) * 3;
    } else {
      return 8 + 16 + 24 + (n - 24) * 4;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 26|
// * |word| consists of lowercase English letters.
// * All letters in |word| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "abcde"
// Output: 5
//
// The remapped keypad given in the image provides the minimum cost.
// "a" -> one push on key 2
// "b" -> one push on key 3
// "c" -> one push on key 4
// "d" -> one push on key 5
// "e" -> one push on key 6
// Total cost is 1 + 1 + 1 + 1 + 1 = 5.
// It can be shown that no other mapping can provide a lower cost.

LEETCODE_SOLUTION_UNITTEST(3014, MinimumNumberOfPushesToTypeWordI, example_1) {
  auto   solution = MakeSolution();
  string word     = "abcde";
  int    expect   = 5;
  int    actual   = solution->minimumPushes(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "xycdefghij"
// Output: 12
//
// The remapped keypad given in the image provides the minimum cost.
// "x" -> one push on key 2
// "y" -> two pushes on key 2
// "c" -> one push on key 3
// "d" -> two pushes on key 3
// "e" -> one push on key 4
// "f" -> one push on key 5
// "g" -> one push on key 6
// "h" -> one push on key 7
// "i" -> one push on key 8
// "j" -> one push on key 9
// Total cost is 1 + 2 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1 = 12.
// It can be shown that no other mapping can provide a lower cost.

LEETCODE_SOLUTION_UNITTEST(3014, MinimumNumberOfPushesToTypeWordI, example_2) {
  auto   solution = MakeSolution();
  string word     = "xycdefghij";
  int    expect   = 12;
  int    actual   = solution->minimumPushes(word);
  LCD_EXPECT_EQ(expect, actual);
}
