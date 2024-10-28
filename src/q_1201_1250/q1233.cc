// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Remove Sub-Folders from the Filesystem
//
// https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/
//
// Question ID: 1233
// Difficult  : Medium
// Solve Date : 2024/10/25 23:08

#include <algorithm>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1233. Remove Sub-Folders from the Filesystem|:
//
// Given a list of folders |folder|, return the folders after removing all
// sub-folders in those folders. You may return the answer in any order. If a
// |folder[i]| is located within another |folder[j]|, it is called a sub-folder
// of it. A sub-folder of |folder[j]| must start with |folder[j]|, followed by a
// |"/"|. For example, |"/a/b"| is a sub-folder of |"/a"|, but |"/b"| is not a
// sub-folder of |"/a/b/c"|. The format of a path is one or more concatenated
// strings of the form: |'/'| followed by one or more lowercase English letters.
//
//  • For example, |"/leetcode"| and |"/leetcode/problems"| are valid paths
//  while an empty string and |"/"| are not.
//
//

LEETCODE_BEGIN_RESOLVING(1233, RemoveSubFoldersFromTheFilesystem, Solution);

class Solution {
public:
  vector<string> removeSubfolders(vector<string> &folder) {
    vector<string> res;
    sort(folder.begin(), folder.end());
    unordered_map<string, int> mp;
    for (auto &s : folder) {
      int    n    = s.size();
      bool   flag = false;
      string tmp;

      for (int i = 0; i < n; ++i) {
        tmp.push_back(s[i]);
        if (i == n - 1 && mp[tmp]) {
          flag = 1;
          break;
        } else if (mp[tmp] && s[i + 1] == '/') {
          flag = 1;
          break;
        }
      }

      if (!flag) {
        ++mp[tmp];
        res.push_back(tmp);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= folder.length <= 4 * 10⁴|
// * |2 <= folder[i].length <= 100|
// * |folder[i]| contains only lowercase letters and |'/'|.
// * |folder[i]| always starts with the character |'/'|.
// * Each folder name is unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
// Output: ["/a","/c/d","/c/f"]
//

LEETCODE_SOLUTION_UNITTEST(1233, RemoveSubFoldersFromTheFilesystem, example_1) {
  auto           solution = MakeSolution();
  vector<string> folder   = {"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"};
  vector<string> expect   = {"/a", "/c/d", "/c/f"};
  vector<string> actual   = solution->removeSubfolders(folder);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: folder = ["/a","/a/b/c","/a/b/d"]
// Output: ["/a"]
//

LEETCODE_SOLUTION_UNITTEST(1233, RemoveSubFoldersFromTheFilesystem, example_2) {
  auto           solution = MakeSolution();
  vector<string> folder   = {"/a", "/a/b/c", "/a/b/d"};
  vector<string> expect   = {"/a"};
  vector<string> actual   = solution->removeSubfolders(folder);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
// Output: ["/a/b/c","/a/b/ca","/a/b/d"]
//

LEETCODE_SOLUTION_UNITTEST(1233, RemoveSubFoldersFromTheFilesystem, example_3) {
  auto           solution = MakeSolution();
  vector<string> folder   = {"/a/b/c", "/a/b/ca", "/a/b/d"};
  vector<string> expect   = {"/a/b/c", "/a/b/ca", "/a/b/d"};
  vector<string> actual   = solution->removeSubfolders(folder);
  EXPECT_ANYORDER_EQ(expect, actual);
}
