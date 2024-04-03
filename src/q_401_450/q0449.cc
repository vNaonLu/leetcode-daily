// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Serialize and Deserialize BST
//
// https://leetcode.com/problems/serialize-and-deserialize-bst/
//
// Question ID: 449
// Difficult  : Medium
// Solve Date : 2024/04/03 20:39

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |449. Serialize and Deserialize BST|:
//
// Serialization is converting a data structure or object into a sequence of
// bits so that it can be stored in a file or memory buffer, or transmitted
// across a network connection link to be reconstructed later in the same or
// another computer environment. Design an algorithm to serialize and
// deserialize a binary search tree. There is no restriction on how your
// serialization/deserialization algorithm should work. You need to ensure that
// a binary search tree can be serialized to a string, and this string can be
// deserialized to the original tree structure. The encoded string should be as
// compact as possible.
//
//

LEETCODE_BEGIN_RESOLVING(449, SerializeAndDeserializeBST, Codec);

class Codec {
public:
  string serialize(TreeNode *root) {
    string res;
    traverse(root, &res);
    return res;
  }

  TreeNode *deserialize(string data) {
    return deserializeHelper(data.begin(), data.end());
  }

private:
  void traverse(TreeNode *p, string *out) {
    if (p) {
      (*out) += to_string(p->val) + ";";
      traverse(p->left, out);
      traverse(p->right, out);
    } else {
      (*out) += ";";
    }
  }

  template <typename It>
  TreeNode *deserializeHelper(It beg, It end) {
    vector<TreeNode *> order;
    auto               it = beg;
    while (beg != end) {
      // the last is always ';'
      if (*it == ';') {
        if (beg != it) {
          order.emplace_back(new TreeNode(toNumber(beg, it)));
        } else {
          order.emplace_back(nullptr);
        }
        beg = ++it;
      } else {
        ++it;
      }
    }
    if (order.empty()) {
      return nullptr;
    }
    buildTree(order.begin(), order.end());
    return order.front();
  }

  template <typename It>
  It buildTree(It beg, It end) {
    if (beg == end) {
      return end;
    }
    if (!*beg) {
      return beg + 1;
    }

    auto right    = buildTree(beg + 1, end);
    auto nxt      = buildTree(right, end);
    (*beg)->left  = *(beg + 1);
    (*beg)->right = *right;
    return nxt;
  }

  template <typename It>
  int toNumber(It beg, It end) {
    int res = 0;
    while (beg != end) {
      res = res * 10 + (*beg++ - '0');
    }
    return res;
  }
};

// return ans;

LEETCODE_END_RESOLVING(Codec);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 10⁴]|.
// * |0 <= Node.val <= 10⁴|
// * The input tree is guaranteed to be a binary search tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [2,1,3]
// Output: [2,1,3]
//

LEETCODE_SOLUTION_UNITTEST(449, SerializeAndDeserializeBST, example_1) {
  auto      codec = MakeCodec();
  TreeNode *root  = TreeNode::FromVector({2, 1, 3});
  string    s     = codec->serialize(root);
  cout << s << endl;
  TreeNode *actual = codec->deserialize(s);
  LCD_EXPECT_EQ(root, actual);
  TreeNode::Release(root, actual);
}

// [Example #2]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(449, SerializeAndDeserializeBST, example_2) {
  auto      codec  = MakeCodec();
  TreeNode *root   = TreeNode::FromVector({});
  string    s      = codec->serialize(root);
  TreeNode *actual = codec->deserialize(s);
  LCD_EXPECT_EQ(root, actual);
  TreeNode::Release(root, actual);
}
