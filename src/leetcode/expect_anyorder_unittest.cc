#include "leetcode/list_node.h"
#include "leetcode/testing/test_helper.h"
#include "leetcode/tree_node.h"
#include <cmath>
#include <vector>

using namespace lcd;
using namespace std;

template <typename T>
T GetPrecisionLoss(T a) {
  return std::nextafter(a, T{INFINITY});
}

TEST(ExpectAnyOrder, Depth0) {
  vector<int> expect_int{1, 2, 3, 4, 5};
  vector<int> actual_int{5, 4, 3, 2, 1};

  vector<float> expect_float{1.f, 2.f, 3.f, 4.f, 5.f};
  vector<float> actual_float{
      GetPrecisionLoss(5.f), GetPrecisionLoss(4.f), GetPrecisionLoss(3.f),
      GetPrecisionLoss(2.f), GetPrecisionLoss(1.f),
  };

  vector<double> expect_double{1., 2., 3., 4., 5.};
  vector<double> actual_double{
      GetPrecisionLoss(5.), GetPrecisionLoss(4.), GetPrecisionLoss(3.),
      GetPrecisionLoss(2.), GetPrecisionLoss(1.),
  };

  vector<ListNode *> expect_list{ListNode::FromVector({1, 2, 3}),
                                 ListNode::FromVector({4, 5, 6})};
  vector<ListNode *> actual_list{ListNode::FromVector({4, 5, 6}),
                                 ListNode::FromVector({1, 2, 3})};

  vector<TreeNode *> expect_tree{TreeNode::FromVector({1, 2, 3}),
                                 TreeNode::FromVector({4, 5, 6})};
  vector<TreeNode *> actual_tree{TreeNode::FromVector({4, 5, 6}),
                                 TreeNode::FromVector({1, 2, 3})};

  EXPECT_ANYORDER_EQ(expect_int, actual_int);
  EXPECT_ANYORDER_EQ(expect_float, actual_float);
  EXPECT_ANYORDER_EQ(expect_double, actual_double);
  EXPECT_ANYORDER_EQ(expect_list, actual_list);
  EXPECT_ANYORDER_EQ(expect_tree, actual_tree);

  ListNode::ReleaseRange(expect_list.begin(), expect_list.end());
  ListNode::ReleaseRange(actual_list.begin(), actual_list.end());
  TreeNode::ReleaseRange(expect_tree.begin(), expect_tree.end());
  TreeNode::ReleaseRange(actual_tree.begin(), actual_tree.end());
  EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
}

TEST(ExpectAnyOrder, Depth1) {
  vector<vector<int>> expect_int{
      {1, 2, 3, 4, 5},
      {6, 7, 8, 9, 0}
  };
  vector<vector<int>> actual_int{
      {5, 4, 3, 2, 1},
      {0, 9, 8, 7, 6}
  };
  vector<vector<float>> expect_float{
      {1.f, 2.f, 3.f, 4.f, 5.f},
      {6.f, 7.f, 8.f, 9.f, 0.f}
  };
  vector<vector<float>> actual_float{
      {GetPrecisionLoss(5.f), GetPrecisionLoss(4.f), GetPrecisionLoss(3.f),
       GetPrecisionLoss(2.f), GetPrecisionLoss(1.f)},
      {GetPrecisionLoss(0.f), GetPrecisionLoss(9.f), GetPrecisionLoss(8.f),
       GetPrecisionLoss(7.f), GetPrecisionLoss(6.f)}
  };

  EXPECT_ANYORDER_WITH_DEPTH_EQ(1, expect_int, actual_int);
  EXPECT_ANYORDER_WITH_DEPTH_EQ(1, expect_float, actual_float);
}

TEST(ExpectAnyOrder, Depth2) {
  vector<vector<vector<int>>> expect_int{
      {{1, 2, 3},    {4, 5, 6}},
      {{7, 8, 9}, {10, 11, 12}}
  };
  vector<vector<vector<int>>> actual_int{
      {   {6, 5, 4}, {3, 2, 1}},
      {{12, 11, 10}, {9, 8, 7}}
  };

  EXPECT_ANYORDER_WITH_DEPTH_EQ(2, expect_int, actual_int);
}
