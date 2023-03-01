#include "leetcode/tree_node.h"
#include "leetcode/testing/test_helper.h"
#include <memory>
#include <sstream>

using namespace std;
using namespace lcd;

class TreeNodeTest : public ::testing::Test {
protected:
  void SetUp() override {
    TreeNode::ReleaseAll();
    LCD_ASSERT_EQ(TreeNode::CheckRemainRefs(), 0);
  }

  void TearDown() override {
    TreeNode::ReleaseAll();
    LCD_ASSERT_EQ(TreeNode::CheckRemainRefs(), 0);
  }
};

TEST_F(TreeNodeTest, Construct) {
  TreeNode node1;
  TreeNode node2(10);
  TreeNode node3(20, &node1, &node2);
  TreeNode node4(30, nullptr, &node2);
  TreeNode node5(40, &node1, nullptr);

  LCD_EXPECT_EQ(node1.val, 0);
  LCD_EXPECT_EQ(node1.left, nullptr);
  LCD_EXPECT_EQ(node1.right, nullptr);

  LCD_EXPECT_EQ(node2.val, 10);
  LCD_EXPECT_EQ(node2.left, nullptr);
  LCD_EXPECT_EQ(node2.right, nullptr);

  LCD_EXPECT_EQ(node3.val, 20);
  LCD_EXPECT_EQ(node3.left, &node1);
  LCD_EXPECT_EQ(node3.right, &node2);

  LCD_EXPECT_EQ(node4.val, 30);
  LCD_EXPECT_EQ(node4.left, nullptr);
  LCD_EXPECT_EQ(node4.right, &node2);

  LCD_EXPECT_EQ(node5.val, 40);
  LCD_EXPECT_EQ(node5.left, &node1);
  LCD_EXPECT_EQ(node5.right, nullptr);
}

TEST_F(TreeNodeTest, GetChild) {
  TreeNode node7;
  TreeNode node6;
  TreeNode node5(0, &node6, &node7);
  TreeNode node4;
  TreeNode node3;
  TreeNode node2(0, &node3, &node4);
  TreeNode node1(0, &node2, &node5);

  LCD_EXPECT_EQ(node1.GetChild(0), &node1);
  LCD_EXPECT_EQ(node1.GetChild(1), &node2);
  LCD_EXPECT_EQ(node1.GetChild(2), &node3);
  LCD_EXPECT_EQ(node1.GetChild(3), &node4);
  LCD_EXPECT_EQ(node1.GetChild(4), &node5);
  LCD_EXPECT_EQ(node1.GetChild(5), &node6);
  LCD_EXPECT_EQ(node1.GetChild(6), &node7);
  LCD_EXPECT_EQ(node1.GetChild(7), nullptr);
  LCD_EXPECT_EQ(node1.GetChild(8), nullptr);
}

TEST_F(TreeNodeTest, ReleaseManual) {
  auto *node = new TreeNode();
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 1);
  delete node;
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST_F(TreeNodeTest, ReleaseChain) {
  auto *node7 = new TreeNode();
  auto *node6 = new TreeNode();
  auto *node5 = new TreeNode(0, node6, node7);
  auto *node4 = new TreeNode();
  auto *node3 = new TreeNode;
  auto *node2 = new TreeNode(0, node3, node4);
  auto *node1 = new TreeNode(0, node2, node5);

  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 7);
  TreeNode::Release(node1);
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST_F(TreeNodeTest, ReleaseMultiple) {
  auto *l1 = new TreeNode();
  auto *l2 = new TreeNode();
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 2);

  TreeNode::Release(l1, l2);
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST_F(TreeNodeTest, ReleaseMultipleChain) {
  auto *l1 = new TreeNode(0, new TreeNode(0, new TreeNode(), nullptr), nullptr);
  auto *l2 = new TreeNode(0, nullptr, new TreeNode(0, nullptr, new TreeNode()));
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 6);

  TreeNode::Release(l1, l2);
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST_F(TreeNodeTest, ReleaseWithModified) {
  auto *l1 = new TreeNode(0, new TreeNode(0, new TreeNode(), nullptr), nullptr);
  auto *replace = new TreeNode();
  replace->left = l1->left->left;
  auto *dangle  = l1->left;
  l1->left      = replace;
  dangle->left = nullptr;
  dangle->right = nullptr;

  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 4);

  TreeNode::Release(l1);
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 1);
  TreeNode::Release(dangle);
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST_F(TreeNodeTest, FromVector) {
  auto *node = TreeNode::FromVector({1, 2, 3, null, 5, 6});
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 5);

  LCD_ASSERT_NE(nullptr, node->GetChild(0));
  LCD_EXPECT_EQ(1, node->GetChild(0)->val);

  LCD_ASSERT_NE(nullptr, node->GetChild(1));
  LCD_EXPECT_EQ(2, node->GetChild(1)->val);

  LCD_ASSERT_NE(nullptr, node->GetChild(2));
  LCD_EXPECT_EQ(5, node->GetChild(2)->val);

  LCD_ASSERT_NE(nullptr, node->GetChild(3));
  LCD_EXPECT_EQ(3, node->GetChild(3)->val);

  LCD_ASSERT_NE(nullptr, node->GetChild(4));
  LCD_EXPECT_EQ(6, node->GetChild(4)->val);

  LCD_EXPECT_EQ(nullptr, node->GetChild(5));
  TreeNode::Release(node);
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST_F(TreeNodeTest, ExpectComparison) {
  auto *l1 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l2 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l3 =
      new TreeNode(1, new TreeNode(2, new TreeNode(4), nullptr), nullptr);
  auto *l4 = TreeNode::FromVector({1, 2, null, 3});

  LCD_EXPECT_EQ(*l1, *l2);
  LCD_EXPECT_NE(*l2, *l3);
  LCD_EXPECT_NE(*l1, *l3);
  LCD_EXPECT_EQ(*l1, *l4);
  TreeNode::Release(l1, l2, l3, l4);
}

TEST_F(TreeNodeTest, MacroExpectComparison) {
  auto *l1 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l2 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l3 =
      new TreeNode(1, new TreeNode(2, new TreeNode(4), nullptr), nullptr);
  auto *l4 = TreeNode::FromVector({1, 2, null, 3});
  TreeNode *l5 = nullptr;

  LCD_EXPECT_EQ(l1, l2);
  LCD_EXPECT_NE(l2, l3);
  LCD_EXPECT_NE(l1, l3);
  LCD_EXPECT_EQ(l1, l4);
  LCD_EXPECT_NE(l1, l5);
  LCD_EXPECT_NE(l2, l5);
  LCD_EXPECT_NE(l3, l5);
  TreeNode::Release(l1, l2, l3, l4);
}

TEST_F(TreeNodeTest, LiteralSerialization) {
  auto *node1 = TreeNode::FromVector({1, 2, null, 3, 4, null, 5});
  std::ostringstream ss;

  ASSERT_TRUE(node1);
  ss << *node1;

  LCD_EXPECT_EQ(ss.str(), "{1, 2, null, 3, 4, null, 5}");

  TreeNode::Release(node1);
}

TEST_F(TreeNodeTest, ReleaseAll) {
  auto *l1 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l2 =
      new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
  auto *l3 =
      new TreeNode(1, new TreeNode(2, new TreeNode(4), nullptr), nullptr);
  auto *l4 = TreeNode::FromVector({1, 2, null, 3});

  TreeNode::ReleaseAll();
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

namespace seg_fault {

class Solution {
private:
  void build_inorder(TreeNode *p, vector<TreeNode *> &inorder) {
    if (p == nullptr) {
      return;
    }

    build_inorder(p->left, inorder);
    inorder.emplace_back(p);
    build_inorder(p->right, inorder);
  }

  template <typename iterator>
  TreeNode *build_tree_from_inorder(iterator beg, iterator end) {
    if (beg == end) {
      return nullptr;
    }

    auto mid      = beg + (end - beg) / 2;
    (*mid)->left  = build_tree_from_inorder(beg, mid);
    (*mid)->right = build_tree_from_inorder(mid + 1, end);

    return *mid;
  }

public:
  TreeNode *balanceBST(TreeNode *root) {
    vector<TreeNode *> order;
    build_inorder(root, order);

    return build_tree_from_inorder(order.begin(), order.end());
  }
};
} // namespace seg_fault

TEST_F(TreeNodeTest, SegFault) {

  auto solution = std::make_unique<seg_fault::Solution>();
  // seg_fault::Solution solution ;

  TreeNode *root =
      TreeNode::FromVector({1, null, 2, null, 3, null, 4, null, null});
  TreeNode *expect = TreeNode::FromVector({3, 2, 4, 1});
  TreeNode *actual = solution->balanceBST(root);
  // TreeNode *actual = solution.balanceBST(root);

  TreeNode::Release(root, expect, actual);
  LCD_EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}
