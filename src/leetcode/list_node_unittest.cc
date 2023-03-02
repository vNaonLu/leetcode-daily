#include "leetcode/list_node.h"
#include "leetcode/testing/test_helper.h"

using namespace std;
using namespace lcd;

class ListNodeTest : public ::testing::Test {
protected:
  void SetUp() override {
    ListNode::ReleaseAll();
    LCD_ASSERT_EQ(ListNode::CheckRemainRefs(), 0);
  }

  void TearDown() override {
    ListNode::ReleaseAll();
    LCD_ASSERT_EQ(ListNode::CheckRemainRefs(), 0);
  }
};

TEST_F(ListNodeTest, Construct) {
  ListNode node1;
  ListNode node2(10);
  ListNode node3(20, &node1);

  LCD_EXPECT_EQ(node1.val, 0);
  LCD_EXPECT_EQ(node1.next, nullptr);

  LCD_EXPECT_EQ(node2.val, 10);
  LCD_EXPECT_EQ(node2.next, nullptr);

  LCD_EXPECT_EQ(node3.val, 20);
  LCD_EXPECT_EQ(node3.next, &node1);
}

TEST_F(ListNodeTest, GetChild) {
  ListNode node3;
  ListNode node2(10, &node3);
  ListNode node1(20, &node2);

  LCD_EXPECT_EQ(node1.GetChild(0), &node1);
  LCD_EXPECT_EQ(node1.GetChild(1), &node2);
  LCD_EXPECT_EQ(node1.GetChild(2), &node3);
  LCD_EXPECT_EQ(node1.GetChild(3), nullptr);
  LCD_EXPECT_EQ(node1.GetChild(4), nullptr);
}

TEST_F(ListNodeTest, GetChildLooped) {
  ListNode node3;
  ListNode node2(10, &node3);
  ListNode node1(20, &node2);
  node3.next = &node1;

  LCD_EXPECT_EQ(node1.GetChild(0), &node1);
  LCD_EXPECT_EQ(node1.GetChild(1), &node2);
  LCD_EXPECT_EQ(node1.GetChild(2), &node3);
  LCD_EXPECT_EQ(node1.GetChild(3), nullptr);
}

TEST_F(ListNodeTest, ReleaseManual) {
  auto *p = new ListNode();
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 1);
  delete p;
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
}

TEST_F(ListNodeTest, ReleaseChain) {
  auto *p = new ListNode(0, new ListNode(0, new ListNode()));
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 3);

  ListNode::Release(p);
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
}

TEST_F(ListNodeTest, ReleaseLooped) {
  auto *loop = new ListNode();
  auto *p = new ListNode(0, new ListNode(0, loop));
  loop->next = p;
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 3);

  ListNode::Release(p);
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
}

TEST_F(ListNodeTest, ReleaseMultiple) {
  auto *l1 = new ListNode();
  auto *l2 = new ListNode();
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 2);

  ListNode::Release(l1, l2);
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
}

TEST_F(ListNodeTest, ReleaseMultipleChain) {
  auto *l1 = new ListNode(0, new ListNode(0, new ListNode()));
  auto *l2 = new ListNode(0, new ListNode(0, new ListNode()));
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 6);

  ListNode::Release(l1, l2);
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
}

TEST_F(ListNodeTest, ReleaseWithModified) {
  auto *l1 = new ListNode(0, new ListNode(0, new ListNode()));
  auto *replace = new ListNode();
  replace->next = l1->next->next;
  auto *dangle = l1->next;
  l1->next = replace;

  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 4);

  ListNode::Release(l1);
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 1);
  ListNode::Release(dangle);
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
}

TEST_F(ListNodeTest, FromVector) {
  auto *node = ListNode::FromVector({1, 2, 3, 4, 5});
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 5);

  LCD_ASSERT_NE(node->GetChild(0), nullptr);
  LCD_EXPECT_EQ(1, node->GetChild(0)->val);

  LCD_ASSERT_NE(node->GetChild(1), nullptr);
  LCD_EXPECT_EQ(2, node->GetChild(1)->val);

  LCD_ASSERT_NE(node->GetChild(2), nullptr);
  LCD_EXPECT_EQ(3, node->GetChild(2)->val);

  LCD_ASSERT_NE(node->GetChild(3), nullptr);
  LCD_EXPECT_EQ(4, node->GetChild(3)->val);

  LCD_ASSERT_NE(node->GetChild(4), nullptr);
  LCD_EXPECT_EQ(5, node->GetChild(4)->val);

  LCD_EXPECT_EQ(node->GetChild(5), nullptr);
  ListNode::Release(node);
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
}

TEST_F(ListNodeTest, FromVectorLooped) {
  auto *node = ListNode::FromVector({1, 2, 3, 4, 5}, 0);
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 5);

  LCD_EXPECT_NE(nullptr, node->GetChild(0));
  LCD_EXPECT_EQ(1, node->GetChild(0)->val);

  LCD_EXPECT_NE(nullptr, node->GetChild(1));
  LCD_EXPECT_EQ(2, node->GetChild(1)->val);

  LCD_EXPECT_NE(nullptr, node->GetChild(2));
  LCD_EXPECT_EQ(3, node->GetChild(2)->val);

  LCD_EXPECT_NE(nullptr, node->GetChild(3));
  LCD_EXPECT_EQ(4, node->GetChild(3)->val);

  LCD_EXPECT_NE(nullptr, node->GetChild(4));
  LCD_EXPECT_EQ(5, node->GetChild(4)->val);

  LCD_EXPECT_EQ(nullptr, node->GetChild(5));
  LCD_EXPECT_EQ(node, node->GetChild(4)->next);
  ListNode::Release(node);
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
}

TEST_F(ListNodeTest, ExpectComparison) {
  auto *l1 = new ListNode(1, new ListNode(2, new ListNode(3)));
  auto *l2 = new ListNode(1, new ListNode(2, new ListNode(3)));
  auto *l3 = new ListNode(1, new ListNode(2, new ListNode(4)));
  auto *l4 = ListNode::FromVector({1, 2, 3});

  LCD_EXPECT_EQ(*l1, *l2);
  LCD_EXPECT_NE(*l2, *l3);
  LCD_EXPECT_NE(*l1, *l3);
  LCD_EXPECT_EQ(*l1, *l4);
  ListNode::Release(l1, l2, l3, l4);
}

TEST_F(ListNodeTest, ExpectComparisonLooped) {
  auto *l1_loop = new ListNode(3);
  auto *l2_loop = new ListNode(3);
  auto *l3_loop = new ListNode(4);
  auto *l1 = new ListNode(1, new ListNode(2, l1_loop));
  l1_loop->next = l1;
  auto *l2 = new ListNode(1, new ListNode(2, l2_loop));
  l2_loop->next = l2;
  auto *l3 = new ListNode(1, new ListNode(2, l3_loop));
  l3_loop->next = l3;
  auto *l4 = ListNode::FromVector({1, 2, 3}, 0);

  LCD_EXPECT_EQ(*l1, *l2);
  LCD_EXPECT_NE(*l1, *l3);
  LCD_EXPECT_EQ(*l1, *l4);
  LCD_EXPECT_NE(*l2, *l3);
  LCD_EXPECT_EQ(*l2, *l4);
  LCD_EXPECT_NE(*l3, *l4);
  ListNode::Release(l1, l2, l3, l4);
}

TEST_F(ListNodeTest, ExpectComparisonStaggerd) {
  auto *l1_loop = new ListNode(3);
  auto *l1 = new ListNode(1, new ListNode(2, l1_loop));
  l1_loop->next = l1;
  auto *l2 = new ListNode(1, new ListNode(2,  new ListNode(3,  new ListNode(1))));

  LCD_EXPECT_NE(*l1, *l2);
  ListNode::Release(l1, l2);
}

TEST_F(ListNodeTest, MacroExpectComparison) {
  auto *l1_loop = new ListNode(3);
  auto *l2_loop = new ListNode(3);
  auto *l3_loop = new ListNode(4);
  auto *l1 = new ListNode(1, new ListNode(2, l1_loop));
  l1_loop->next = l1;
  auto *l2 = new ListNode(1, new ListNode(2, l2_loop));
  l2_loop->next = l2;
  auto *l3 = new ListNode(1, new ListNode(2, l3_loop));
  l3_loop->next = l3;
  auto *l4 = ListNode::FromVector({1, 2, 3}, 0);
  ListNode *l5 = nullptr;

  LCD_EXPECT_EQ(l1, l2);
  LCD_EXPECT_NE(l1, l3);
  LCD_EXPECT_EQ(l1, l4);
  LCD_EXPECT_NE(l2, l3);
  LCD_EXPECT_EQ(l2, l4);
  LCD_EXPECT_NE(l3, l4);
  LCD_EXPECT_NE(l1, l5);
  LCD_EXPECT_NE(l2, l5);
  LCD_EXPECT_NE(l3, l5);
  ListNode::Release(l1, l2, l3, l4);
}

TEST_F(ListNodeTest, LiteralSerialization) {
  auto *node1 = ListNode::FromVector({1, 2, 3, 4, 5});
  auto *looped = ListNode::FromVector({1, 2, 3, 4, 5}, 2);
  std::ostringstream ss;

  ASSERT_TRUE(node1);
  ss << *node1;
  LCD_EXPECT_EQ(ss.str(), "{1, 2, 3, 4, 5}");

  ss.str("");
  ss.clear();

  ASSERT_TRUE(looped);
  ss << *looped;
  LCD_EXPECT_EQ(ss.str(), "{1, 2, 3, 4, 5, 3(Loop to index-2)}");

  ListNode::Release(node1);
}

TEST_F(ListNodeTest, ReleaseAll) {
  auto *l1_loop = new ListNode(3);
  auto *l2_loop = new ListNode(3);
  auto *l3_loop = new ListNode(4);
  auto *l1 = new ListNode(1, new ListNode(2, l1_loop));
  l1_loop->next = l1;
  auto *l2 = new ListNode(1, new ListNode(2, l2_loop));
  l2_loop->next = l2;
  auto *l3 = new ListNode(1, new ListNode(2, l3_loop));
  l3_loop->next = l3;
  [[maybe_unused]] auto *l4 = ListNode::FromVector({1, 2, 3}, 0);
  [[maybe_unused]] ListNode *l5 = nullptr;

  ListNode::ReleaseAll();
  LCD_EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
}
