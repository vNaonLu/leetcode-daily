// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Delete Duplicate Folders in System
//
// https://leetcode.com/problems/delete-duplicate-folders-in-system/
//
// Question ID: 1948
// Difficult  : Hard
// Solve Date : 2025/07/20 12:57

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1948. Delete Duplicate Folders in System|:
//
// Due to a bug, there are many duplicate folders in a file system. You are
// given a 2D array |paths|, where |paths[i]| is an array representing an
// absolute path to the |iᵗʰ| folder in the file system.
//
//  • For example, |["one", "two", "three"]| represents the path
//  |"/one/two/three"|.
// Two folders (not necessarily on the same level) are identical if they contain
// the same non-empty set of identical subfolders and underlying subfolder
// structure. The folders do not need to be at the root level to be identical.
// If two or more folders are identical, then mark the folders as well as all
// their subfolders.
//
//  • For example, folders |"/a"| and |"/b"| in the file structure below are
//  identical. They (as well as their subfolders) should all be marked:
//
//
//    • |/a|
//
//    • |/a/x|
//
//    • |/a/x/y|
//
//    • |/a/z|
//
//    • |/b|
//
//    • |/b/x|
//
//    • |/b/x/y|
//
//    • |/b/z|
//
//
//
//  • However, if the file structure also included the path |"/b/w"|, then the
//  folders |"/a"| and |"/b"| would not be identical. Note that |"/a/x"| and
//  |"/b/x"| would still be considered identical even with the added folder.
// Once all the identical folders and their subfolders have been marked, the
// file system will delete all of them. The file system only runs the deletion
// once, so any folders that become identical after the initial deletion are not
// deleted. Return the 2D array |ans| containing the paths of the remaining
// folders after deleting all the marked folders. The paths may be returned in
// any order.
//
//

LEETCODE_BEGIN_RESOLVING(1948, DeleteDuplicateFoldersInSystem, Solution);

struct Node {
  string                        name;
  unordered_map<string, Node *> children;
  string                        signature;

  Node(string name) : name(name) {}
};

class Solution {
public:
  vector<vector<string>> deleteDuplicateFolder(vector<vector<string>> &paths) {
    Node *root = new Node("");
    for (const auto &path : paths) {
      Node *curr = root;
      for (const string &folder : path) {
        if (curr->children.find(folder) == curr->children.end()) {
          curr->children[folder] = new Node(folder);
        }
        curr = curr->children[folder];
      }
    }

    unordered_map<string, int> signatureCount;
    dfs(root, signatureCount);

    vector<vector<string>> result;
    vector<string>         currentPath;
    for (const auto &[name, child] : root->children) {
      dfs2(child, currentPath, result, signatureCount);
    }

    delete root;
    return result;
  }

private:
  void dfs(Node *node, unordered_map<string, int> &signatureCount) {
    if (node->children.empty()) {
      node->signature = "";
      return;
    }

    vector<string> childSignatures;
    for (const auto &[name, child] : node->children) {
      dfs(child, signatureCount);
      childSignatures.push_back(name + "(" + child->signature + ")");
    }
    sort(childSignatures.begin(), childSignatures.end());
    node->signature = "";
    for (const string &sig : childSignatures) {
      node->signature += sig;
    }
    signatureCount[node->signature]++;
  }

  void dfs2(Node *node, vector<string> &currentPath,
            vector<vector<string>>     &result,
            unordered_map<string, int> &signatureCount) {
    if (!node->children.empty() && signatureCount[node->signature] >= 2) {
      return;
    }
    currentPath.push_back(node->name);
    result.push_back(currentPath);
    for (const auto &[name, child] : node->children) {
      dfs2(child, currentPath, result, signatureCount);
    }
    currentPath.pop_back();
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= paths.length <= 2 * 10⁴|
// * |1 <= paths[i].length <= 500|
// * |1 <= paths[i][j].length <= 10|
// * |1 <= sum(paths[i][j].length) <= 2 * 10⁵|
// * |path[i][j]| consists of lowercase English letters.
// * No two paths lead to the same folder.
// * For any folder not at the root level, its parent folder will also be in the
// input.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
// Output: [["d"],["d","a"]]
//

LEETCODE_SOLUTION_UNITTEST(1948, DeleteDuplicateFoldersInSystem, example_1) {
  auto                   solution = MakeSolution();
  vector<vector<string>> paths    = {
      {"a"},
      {"c"},
      {"d"},
      {"a", "b"},
      {"c", "b"},
      {"d", "a"}
  };
  vector<vector<string>> expect = {
      {"d"},
      {"d", "a"}
  };
  vector<vector<string>> actual = solution->deleteDuplicateFolder(paths);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: paths =
//  [["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]]
// Output: [["c"],["c","b"],["a"],["a","b"]]
//

LEETCODE_SOLUTION_UNITTEST(1948, DeleteDuplicateFoldersInSystem, example_2) {
  auto                   solution = MakeSolution();
  vector<vector<string>> paths    = {
      {"a"},
      {"c"},
      {"a", "b"},
      {"c", "b"},
      {"a", "b", "x"},
      {"a", "b", "x", "y"},
      {"w"},
      {"w", "y"}
  };
  vector<vector<string>> expect = {
      {"c"},
      {"c", "b"},
      {"a"},
      {"a", "b"}
  };
  vector<vector<string>> actual = solution->deleteDuplicateFolder(paths);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: paths = [["a","b"],["c","d"],["c"],["a"]]
// Output: [["c"],["c","d"],["a"],["a","b"]]
//

LEETCODE_SOLUTION_UNITTEST(1948, DeleteDuplicateFoldersInSystem, example_3) {
  auto                   solution = MakeSolution();
  vector<vector<string>> paths    = {
      {"a", "b"},
      {"c", "d"},
      {"c"},
      {"a"}
  };
  vector<vector<string>> expect = {
      {"c"},
      {"c", "d"},
      {"a"},
      {"a", "b"}
  };
  vector<vector<string>> actual = solution->deleteDuplicateFolder(paths);
  LCD_EXPECT_EQ(expect, actual);
}
