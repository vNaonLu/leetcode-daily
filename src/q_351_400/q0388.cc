// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Absolute File Path
//
// https://leetcode.com/problems/longest-absolute-file-path/
//
// Question ID: 388
// Difficult  : Medium
// Solve Date : 2022/03/05 10:14

#include <iosfwd>
#include <numeric>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |388. Longest Absolute File Path|:
//
// Suppose we have a file system that stores both files and directories. An
// example of one system is represented in the following picture:
// ![img](https://assets.leetcode.com/uploads/2020/08/28/mdir.jpg)
// Here, we have |dir| as the only directory in the root. |dir| contains two
// subdirectories, |subdir1| and |subdir2|. |subdir1| contains a file
// |file1.ext| and subdirectory |subsubdir1|. |subdir2| contains a subdirectory
// |subsubdir2|, which contains a file |file2.ext|. In text form, it looks like
// this (with ⟶ representing the tab character): dir ⟶ subdir1 ⟶ ⟶ file1.ext ⟶ ⟶
// subsubdir1 ⟶ subdir2 ⟶ ⟶ subsubdir2 ⟶ ⟶ ⟶ file2.ext If we were to write this
// representation in code, it will look like this:
// |"dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"|.
// Note that the |'\n'| and |'\t'| are the new-line and tab characters. Every
// file and directory has a unique absolute path in the file system, which is
// the order of directories that must be opened to reach the file/directory
// itself, all concatenated by |'/'s|. Using the above example, the absolute
// path to |file2.ext| is |"dir/subdir2/subsubdir2/file2.ext"|. Each directory
// name consists of letters, digits, and/or spaces. Each file name is of the
// form |name.extension|, where |name| and |extension| consist of letters,
// digits, and/or spaces. Given a string |input| representing the file system in
// the explained format, return the length of the longest absolute path to a
// file in the abstracted file system. If there is no file in the system, return
// |0|. Note that the testcases are generated such that the file system is valid
// and no file or directory name has length 0.  
//

LEETCODE_BEGIN_RESOLVING(388, LongestAbsoluteFilePath, Solution);

class Solution {
public:
  int lengthLongestPath(string input) {
    int         res = 0, ptr = 0, cur = 0, indent = 0;
    bool        is_file = false;
    vector<int> pathes(1001, 0);
    for (auto it = input.begin(); it != input.end(); ++it) {
      switch (*it) {
      case '\n':
        break;
      case '\t':
        ++indent;
        break;
      case '.':
        is_file = true;
        [[fallthrough]];
      default:
        ++cur;
      }
      if (*it == '\n' || it + 1 == input.end()) {
        if (ptr == indent) {
          /// next depth
          pathes[ptr++] = cur;
          if (is_file) {
            res = max(res, accumulate(pathes.begin(), pathes.begin() + ptr, 0) +
                               indent);
          }
          cur = indent = 0;
          is_file      = false;
        } else {
          /// indent is not possible bigger than ptr
          ptr           = indent;
          pathes[ptr++] = cur;
          if (is_file) {
            res = max(res, accumulate(pathes.begin(), pathes.begin() + ptr, 0) +
                               indent);
          }
          cur = indent = 0;
          is_file      = false;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= input.length <= 10⁴|
// * |input| may contain lowercase or uppercase English letters, a new line
// character |'\n'|, a tab character |'\t'|, a dot |'.'|, a space |' '|, and
// digits.
// * All file and directory names have positive length.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
// Output: 20
//
// We have only one file, and the absolute path is "dir/subdir2/file.ext" of
// length 20.

LEETCODE_SOLUTION_UNITTEST(388, LongestAbsoluteFilePath, example_1) {
  auto   solution = MakeSolution();
  string input    = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext";
  int    expect   = 20;
  int    actual   = solution->lengthLongestPath(input);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: input =
//  "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
// Output: 32
//
// We have two files:
// "dir/subdir1/file1.ext" of length 21
// "dir/subdir2/subsubdir2/file2.ext" of length 32.
// We return 32 since it is the longest absolute path to a file.

LEETCODE_SOLUTION_UNITTEST(388, LongestAbsoluteFilePath, example_2) {
  auto   solution = MakeSolution();
  string input =
      "dir\n\tsubdir1\n\t\tfile1."
      "ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
  int expect = 32;
  int actual = solution->lengthLongestPath(input);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: input = "a"
// Output: 0
//
// We do not have any files, just a single directory named "a".

LEETCODE_SOLUTION_UNITTEST(388, LongestAbsoluteFilePath, example_3) {
  auto   solution = MakeSolution();
  string input    = "a";
  int    expect   = 0;
  int    actual   = solution->lengthLongestPath(input);
  LCD_EXPECT_EQ(expect, actual);
}
