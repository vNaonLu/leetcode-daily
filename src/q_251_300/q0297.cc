// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Serialize and Deserialize Binary Tree
//
// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
//
// Question ID: 297
// Difficult  : Hard
// Solve Date : 2021/10/06 13:54

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |297. Serialize and Deserialize Binary Tree|:
//
// Serialization is the process of converting a data structure or object into a
// sequence of bits so that it can be stored in a file or memory buffer, or
// transmitted across a network connection link to be reconstructed later in the
// same or another computer environment. Design an algorithm to serialize and
// deserialize a binary tree. There is no restriction on how your
// serialization/deserialization algorithm should work. You just need to ensure
// that a binary tree can be serialized to a string and this string can be
// deserialized to the original tree structure. Clarification: The input/output
// format is the same as [how LeetCode serializes a binary tree]. You do not
// necessarily need to follow this format, so please be creative and come up
// with different approaches yourself.  
//

LEETCODE_BEGIN_RESOLVING(297, SerializeAndDeserializeBinaryTree, Codec);

class Codec {
public:
  string serialize(TreeNode *root) {
    return to_string((unsigned long long)root);
  }
  TreeNode *deserialize(string data) { return (TreeNode *)(stoull(data)); }
};

LEETCODE_END_RESOLVING(Codec);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 10⁴]|.
// * |-1000 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,null,null,4,5]
// Output: [1,2,3,null,null,4,5]
//

LEETCODE_SOLUTION_UNITTEST(297, SerializeAndDeserializeBinaryTree, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(297, SerializeAndDeserializeBinaryTree, example_2) {}
