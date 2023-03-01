// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Frequency Stack
//
// https://leetcode.com/problems/maximum-frequency-stack/
//
// Question ID: 895
// Difficult  : Hard
// Solve Date : 2022/03/19 13:40

#include <iosfwd>
#include <map>
#include <stack>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |895. Maximum Frequency Stack|:
//
// Design a stack-like data structure to push elements to the stack and pop the
// most frequent element from the stack. Implement the |FreqStack| class:
//
//  • |FreqStack()| constructs an empty frequency stack.
//
//  • |void push(int val)| pushes an integer |val| onto the top of the stack.
//
//  • |int pop()| removes and returns the most frequent element in the stack.
//
//
//    • If there is a tie for the most frequent element, the element closest to
//    the stack's top is removed and returned.
//
//
//  
//

LEETCODE_BEGIN_RESOLVING(895, MaximumFrequencyStack, FreqStack);

class FreqStack {
private:
  unordered_map<int, int>        freq;
  unordered_map<int, stack<int>> group;
  int                            maxfreq;

public:
  FreqStack() { maxfreq = 0; }

  void push(int val) {
    int count = ++freq[val];
    maxfreq   = max(count, maxfreq);

    group[count].push(val);
  }

  int pop() {
    auto &stk = group[maxfreq];
    auto  res = stk.top();
    stk.pop();
    --freq[res];

    if (stk.empty()) {
      --maxfreq;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(FreqStack);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= val <= 10⁹|
// * At most |2 * 10⁴| calls will be made to |push| and |pop|.
// * It is guaranteed that there will be at least one element in the stack
// before calling |pop|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["FreqStack", "push", "push", "push", "push", "push", "push", "pop",
//  "pop", "pop", "pop"]
// [[], [5], [7], [5], [7], [4], [5], [], [], [], []]
// Output: [null, null, null, null, null, null, null, 5, 7, 5, 4]
//
// FreqStack freqStack = new FreqStack();
// freqStack.push(5); // The stack is [5]
// freqStack.push(7); // The stack is [5,7]
// freqStack.push(5); // The stack is [5,7,5]
// freqStack.push(7); // The stack is [5,7,5,7]
// freqStack.push(4); // The stack is [5,7,5,7,4]
// freqStack.push(5); // The stack is [5,7,5,7,4,5]
// freqStack.pop(); // return 5, as 5 is the most frequent. The stack becomes
// [5,7,5,7,4]. freqStack.pop(); // return 7, as 5 and 7 is the most frequent,
// but 7 is closest to the top. The stack becomes [5,7,5,4]. freqStack.pop(); //
// return 5, as 5 is the most frequent. The stack becomes [5,7,4].
// freqStack.pop(); // return 4, as 4, 5 and 7 is the most frequent, but 4 is
// closest to the top. The stack becomes [5,7].

LEETCODE_SOLUTION_UNITTEST(895, MaximumFrequencyStack, example_1) {
  auto freq_stack = MakeFreqStack();
  int  s1_val     = 5;
  freq_stack->push(s1_val);
  int s2_val = 7;
  freq_stack->push(s2_val);
  int s3_val = 5;
  freq_stack->push(s3_val);
  int s4_val = 7;
  freq_stack->push(s4_val);
  int s5_val = 4;
  freq_stack->push(s5_val);
  int s6_val = 5;
  freq_stack->push(s6_val);
  int s7_expect = 5;
  int s7_actual = freq_stack->pop();
  LCD_EXPECT_EQ(s7_expect, s7_actual);
  int s8_expect = 7;
  int s8_actual = freq_stack->pop();
  LCD_EXPECT_EQ(s8_expect, s8_actual);
  int s9_expect = 5;
  int s9_actual = freq_stack->pop();
  LCD_EXPECT_EQ(s9_expect, s9_actual);
  int s10_expect = 4;
  int s10_actual = freq_stack->pop();
  LCD_EXPECT_EQ(s10_expect, s10_actual);
}
