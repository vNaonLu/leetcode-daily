#include "leetcode/tree_node.h"
#include "testing/test_helper.h"
#include <sstream>

using namespace std;
using namespace lcd;

TEST(TreeNode, Construct) {
  TreeNode node1;
  TreeNode node2(10);
  TreeNode node3(20, &node1, &node2);
  TreeNode node4(30, nullptr, &node2);
  TreeNode node5(40, &node1, nullptr);

  EXPECT_EQ(node1.val, 0);
  EXPECT_EQ(node1.left, nullptr);
  EXPECT_EQ(node1.right, nullptr);

  EXPECT_EQ(node2.val, 10);
  EXPECT_EQ(node2.left, nullptr);
  EXPECT_EQ(node2.right, nullptr);

  EXPECT_EQ(node3.val, 20);
  EXPECT_EQ(node3.left, &node1);
  EXPECT_EQ(node3.right, &node2);

  EXPECT_EQ(node4.val, 30);
  EXPECT_EQ(node4.left, nullptr);
  EXPECT_EQ(node4.right, &node2);

  EXPECT_EQ(node5.val, 40);
  EXPECT_EQ(node5.left, &node1);
  EXPECT_EQ(node5.right, nullptr);
}

TEST(TreeNode, GetChild) {
  TreeNode node7;
  TreeNode node6;
  TreeNode node5(0, &node6, &node7);
  TreeNode node4;
  TreeNode node3;
  TreeNode node2(0, &node3, &node4);
  TreeNode node1(0, &node2, &node5);

  EXPECT_EQ(node1.GetChild(0), &node1);
  EXPECT_EQ(node1.GetChild(1), &node2);
  EXPECT_EQ(node1.GetChild(2), &node3);
  EXPECT_EQ(node1.GetChild(3), &node4);
  EXPECT_EQ(node1.GetChild(4), &node5);
  EXPECT_EQ(node1.GetChild(5), &node6);
  EXPECT_EQ(node1.GetChild(6), &node7);
  EXPECT_EQ(node1.GetChild(7), nullptr);
  EXPECT_EQ(node1.GetChild(8), nullptr);
}

TEST(TreeNode, ReleaseManual) {
  auto *node = new TreeNode();
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 1);
  delete node;
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST(TreeNode, ReleaseChain) {
  auto *node7 = new TreeNode();
  auto *node6 = new TreeNode();
  auto *node5 = new TreeNode(0, node6, node7);
  auto *node4 = new TreeNode();
  auto *node3 = new TreeNode;
  auto *node2 = new TreeNode(0, node3, node4);
  auto *node1 = new TreeNode(0, node2, node5);

  EXPECT_EQ(TreeNode::CheckRemainRefs(), 7);
  TreeNode::Release(node1);
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST(TreeNode, ReleaseMultiple) {
  auto *l1 = new TreeNode();
  auto *l2 = new TreeNode();
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 2);

  TreeNode::Release(l1, l2);
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST(TreeNode, ReleaseMultipleChain) {
  auto *l1 = new TreeNode(0, new TreeNode(0, new TreeNode(), nullptr), nullptr);
  auto *l2 = new TreeNode(0, nullptr, new TreeNode(0, nullptr, new TreeNode()));
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 6);

  TreeNode::Release(l1, l2);
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST(TreeNode, ReleaseWithModified) {
  auto *l1 = new TreeNode(0, new TreeNode(0, new TreeNode(), nullptr), nullptr);
  auto *replace = new TreeNode();
  replace->left = l1->left->left;
  auto *dangle  = l1->left;
  l1->left      = replace;

  EXPECT_EQ(TreeNode::CheckRemainRefs(), 4);

  TreeNode::Release(l1);
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 1);
  TreeNode::Release(dangle);
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST(TreeNode, FromVector) {
  auto *node = TreeNode::FromVector({1, 2, 3, null, 5, 6});
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 5);

  ASSERT_NE(nullptr, node->GetChild(0));
  EXPECT_EQ(1, node->GetChild(0)->val);

  ASSERT_NE(nullptr, node->GetChild(1));
  EXPECT_EQ(2, node->GetChild(1)->val);

  ASSERT_NE(nullptr, node->GetChild(2));
  EXPECT_EQ(5, node->GetChild(2)->val);

  ASSERT_NE(nullptr, node->GetChild(3));
  EXPECT_EQ(3, node->GetChild(3)->val);

  ASSERT_NE(nullptr, node->GetChild(4));
  EXPECT_EQ(6, node->GetChild(4)->val);

  EXPECT_EQ(nullptr, node->GetChild(5));
  TreeNode::Release(node);
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST(TreeNode, ExpectComparison) {
  auto *l1 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l2 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l3 =
      new TreeNode(1, new TreeNode(2, new TreeNode(4), nullptr), nullptr);
  auto *l4 = TreeNode::FromVector({1, 2, null, 3});

  EXPECT_EQ(*l1, *l2);
  EXPECT_NE(*l2, *l3);
  EXPECT_NE(*l1, *l3);
  EXPECT_EQ(*l1, *l4);
  TreeNode::Release(l1, l2, l3, l4);
}

TEST(TreeNode, MacroExpectComparison) {
  auto *l1 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l2 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l3 =
      new TreeNode(1, new TreeNode(2, new TreeNode(4), nullptr), nullptr);
  auto *l4 = TreeNode::FromVector({1, 2, null, 3});
  TreeNode *l5 = nullptr;

  EXPECT_TREENODE_EQ(l1, l2);
  EXPECT_TREENODE_NE(l2, l3);
  EXPECT_TREENODE_NE(l1, l3);
  EXPECT_TREENODE_EQ(l1, l4);
  EXPECT_TREENODE_NE(l1, l5);
  EXPECT_TREENODE_NE(l2, l5);
  EXPECT_TREENODE_NE(l3, l5);
  TreeNode::Release(l1, l2, l3, l4);
}

TEST(TreeNode, LiteralSerialization) {
  auto *node1 = TreeNode::FromVector({1, 2, null, 3, 4, null, 5});
  std::ostringstream ss;

  ASSERT_TRUE(node1);
  ss << *node1;

  EXPECT_EQ(ss.str(), "{1, 2, null, 3, 4, null, 5}");

  TreeNode::Release(node1);
}

TEST(TreeNode, ReleaseAll) {
  auto *l1 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l2 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l3 =
      new TreeNode(1, new TreeNode(2, new TreeNode(4), nullptr), nullptr);
  auto *l4 = TreeNode::FromVector({1, 2, null, 3});

  TreeNode::ReleaseAll();
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}
