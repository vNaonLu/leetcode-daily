#include "leetcode/tree_node.h"
#include "testing/test_helper.h"
#include <vector>

using namespace lcd;
using namespace std;

TEST(ExpectAnyOrder, Depth0) {
  vector<int> expect_int{1, 2, 3, 4, 5};
  vector<int> actual_int{5, 4, 3, 2, 1};

  EXPECT_ANYORDER_EQ(expect_int, actual_int);
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

  EXPECT_ANYORDER_WITH_DEPTH_EQ(1, expect_int, actual_int);
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
