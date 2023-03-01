// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Duplicate File in System
//
// https://leetcode.com/problems/find-duplicate-file-in-system/
//
// Question ID: 609
// Difficult  : Medium
// Solve Date : 2022/09/19 17:46

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |609. Find Duplicate File in System|:
//
// Given a list |paths| of directory info, including the directory path, and all
// the files with contents in this directory, return all the duplicate files in
// the file system in terms of their paths. You may return the answer in any
// order. A group of duplicate files consists of at least two files that have
// the same content. A single directory info string in the input list has the
// following format:
//
//  • |"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ...
//  fn.txt(fn_content)"|
// It means there are |n| files |(f1.txt, f2.txt ... fn.txt)| with content
// |(f1_content, f2_content ... fn_content)| respectively in the directory "
// |root/d1/d2/.../dm"|. Note that |n >= 1| and |m >= 0|. If |m = 0|, it means
// the directory is just the root directory. The output is a list of groups of
// duplicate file paths. For each group, it contains all the file paths of the
// files that have the same content. A file path is a string that has the
// following format:
//
//  • |"directory_path/file_name.txt"|
//

LEETCODE_BEGIN_RESOLVING(609, FindDuplicateFileInSystem, Solution);

class Solution {
private:
  template <char sth, typename Iterator>
  Iterator find(Iterator beg, Iterator end) {
    while (beg != end) {
      if (*beg == sth) {
        return beg;
      }
      ++beg;
    }
    return end;
  }

  template <char sth, typename Iterator>
  Iterator findNot(Iterator beg, Iterator end) {
    while (beg != end) {
      if (*beg != sth) {
        return beg;
      }
      ++beg;
    }
    return end;
  }

  template <typename Iterator>
  vector<pair<string, string>> splitFileContent(Iterator beg, Iterator end) {
    auto res = vector<pair<string, string>>();
    auto it  = beg;
    while (it != end) {
      /// trim the space character
      beg = it = findNot<' '>(it, end);

      /// get the file name
      it        = find<'('>(it, end);
      auto file = string(beg, it);

      /// get the content
      beg          = ++it;
      it           = find<')'>(it, end);
      auto content = string(beg, it);

      /// ++it since the character ')' is useless for us now
      ++it;

      /// use move function to avoid the copy constructor
      res.emplace_back(move(file), move(content));
    }
    return res;
  }

public:
  vector<vector<string>> findDuplicate(vector<string> &paths) {
    auto memo = unordered_map<string, vector<string>>();
    auto res  = vector<vector<string>>();
    for (auto &s : paths) {
      auto it        = find<' '>(s.begin(), s.end());
      auto directory = string(s.begin(), it);

      for (auto [file, content] : splitFileContent(it, s.end())) {
        /// store the file_name into the hash map
        memo[content].emplace_back(directory + '/' + move(file));
      }
    }
    for (auto &[c, files] : memo) {
      if (files.size() > 1) {
        /// the
        res.emplace_back(move(files));
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= paths.length <= 2 * 10⁴|
// * |1 <= paths[i].length <= 3000|
// * |1 <= sum(paths[i].length) <= 5 * 10⁵|
// * |paths[i]| consist of English letters, digits, |'/'|, |'.'|, |'('|, |')'|,
// and |' '|.
// * You may assume no files or directories share the same name in the same
// directory.
// * You may assume each given directory info represents a unique directory. A
// single blank space separates the directory path and file info.
// * Imagine you are given a real file system, how will you search files? DFS or
// BFS?
// * If the file content is very large (GB level), how will you modify your
// solution?
// * If you can only read the file by 1kb each time, how will you modify your
// solution?
// * What is the time complexity of your modified solution? What is the most
// time-consuming part and memory-consuming part of it? How to optimize?
// * How to make sure the duplicated files you find are not false positive?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: paths =
//  ["root/a 1.txt(abcd) 2.txt(efgh)","root/c 3.txt(abcd)","root/c/d 4.txt(efgh)","root
//  4.txt(efgh)"]
// Output:
// [["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]
//

LEETCODE_SOLUTION_UNITTEST(609, FindDuplicateFileInSystem, example_1) {
  auto                   solution = MakeSolution();
  vector<string>         paths    = {"root/a 1.txt(abcd) 2.txt(efgh)",
                                     "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)",
                                     "root 4.txt(efgh)"};
  vector<vector<string>> expect   = {
      {"root/a/2.txt", "root/c/d/4.txt", "root/4.txt"},
      {"root/a/1.txt", "root/c/3.txt"}
  };
  vector<vector<string>> actual = solution->findDuplicate(paths);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: paths =
//  ["root/a 1.txt(abcd) 2.txt(efgh)","root/c 3.txt(abcd)","root/c/d 4.txt(efgh)"]
// Output: [["root/a/2.txt","root/c/d/4.txt"],["root/a/1.txt","root/c/3.txt"]]
//

LEETCODE_SOLUTION_UNITTEST(609, FindDuplicateFileInSystem, example_2) {
  auto                   solution = MakeSolution();
  vector<string>         paths    = {"root/a 1.txt(abcd) 2.txt(efgh)",
                                     "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)"};
  vector<vector<string>> expect   = {
      {"root/a/2.txt", "root/c/d/4.txt"},
      {"root/a/1.txt",   "root/c/3.txt"}
  };
  vector<vector<string>> actual = solution->findDuplicate(paths);
  EXPECT_ANYORDER_EQ(expect, actual);
}
