// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design an Ordered Stream
//
// https://leetcode.com/problems/design-an-ordered-stream/
//
// Question ID: 1656
// Difficult  : Easy
// Solve Date : 2022/12/26 14:39

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1656. Design an Ordered Stream|:
//
// There is a stream of |n| |(idKey, value)| pairs arriving in an arbitrary
// order, where |idKey| is an integer between |1| and |n| and |value| is a
// string. No two pairs have the same |id|. Design a stream that returns the
// values in increasing order of their IDs by returning a chunk (list) of values
// after each insertion. The concatenation of all the chunks should result in a
// list of the sorted values. Implement the |OrderedStream| class:
//
//  • |OrderedStream(int n)| Constructs the stream to take |n| values.
//
//  • |String[] insert(int idKey, String value)| Inserts the pair |(idKey,
//  value)| into the stream, then returns the largest possible chunk of
//  currently inserted values that appear next in the order.
//

LEETCODE_BEGIN_RESOLVING(1656, DesignAnOrderedStream, OrderedStream);

class OrderedStream {
private:
  int            idx_;
  vector<string> data_;

public:
  OrderedStream(int n) {
    idx_ = 0;
    data_.clear();
    data_.resize(n + 1, "");
  }

  vector<string> insert(int idKey, string value) {
    auto res         = vector<string>();
    data_[idKey - 1] = value;

    while (!data_[idx_].empty()) {
      res.emplace_back(data_[idx_++]);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(OrderedStream);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
// * |1 <= id <= n|
// * |value.length == 5|
// * |value|consists only of lowercase letters.
// * Each call to |insert|will have a unique |id.|
// * Exactly |n| calls will be made to |insert|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["OrderedStream", "insert", "insert", "insert", "insert", "insert"]
// [[5], [3, "ccccc"], [1, "aaaaa"], [2, "bbbbb"], [5, "eeeee"], [4, "ddddd"]]
// Output: [null, [], ["aaaaa"], ["bbbbb", "ccccc"], [], ["ddddd", "eeeee"]]
//
// // Note that the values ordered by ID is ["aaaaa", "bbbbb", "ccccc", "ddddd",
// "eeeee"]. OrderedStream os = new OrderedStream(5); os.insert(3, "ccccc"); //
// Inserts (3, "ccccc"), returns []. os.insert(1, "aaaaa"); // Inserts (1,
// "aaaaa"), returns ["aaaaa"]. os.insert(2, "bbbbb"); // Inserts (2, "bbbbb"),
// returns ["bbbbb", "ccccc"]. os.insert(5, "eeeee"); // Inserts (5, "eeeee"),
// returns []. os.insert(4, "ddddd"); // Inserts (4, "ddddd"), returns ["ddddd",
// "eeeee"].
// // Concatentating all the chunks returned:
// // [] + ["aaaaa"] + ["bbbbb", "ccccc"] + [] + ["ddddd", "eeeee"] = ["aaaaa",
// "bbbbb", "ccccc", "ddddd", "eeeee"]
// // The resulting order is the same as the order above.

LEETCODE_SOLUTION_UNITTEST(1656, DesignAnOrderedStream, example_1) {
  int            s0_n           = 5;
  auto           ordered_stream = MakeOrderedStream(s0_n);
  int            s1_idKey       = 3;
  string         s1_value       = "ccccc";
  vector<string> s1_expect      = {};
  vector<string> s1_actual      = ordered_stream->insert(s1_idKey, s1_value);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int            s2_idKey  = 1;
  string         s2_value  = "aaaaa";
  vector<string> s2_expect = {"aaaaa"};
  vector<string> s2_actual = ordered_stream->insert(s2_idKey, s2_value);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int            s3_idKey  = 2;
  string         s3_value  = "bbbbb";
  vector<string> s3_expect = {"bbbbb", "ccccc"};
  vector<string> s3_actual = ordered_stream->insert(s3_idKey, s3_value);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int            s4_idKey  = 5;
  string         s4_value  = "eeeee";
  vector<string> s4_expect = {};
  vector<string> s4_actual = ordered_stream->insert(s4_idKey, s4_value);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int            s5_idKey  = 4;
  string         s5_value  = "ddddd";
  vector<string> s5_expect = {"ddddd", "eeeee"};
  vector<string> s5_actual = ordered_stream->insert(s5_idKey, s5_value);
  LCD_EXPECT_EQ(s5_expect, s5_actual);
}
