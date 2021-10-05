
#ifndef LEETCODE_Q1545_H__
#define LEETCODE_Q1545_H__
#include <iostream>

namespace l1545 {
using namespace std;

/**
  * This file is generated by leetcode_add.py
  *
  * 1545.
  *       Find Kth Bit in Nth Binary String
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   Given two positive integers ‘n’ and ‘k’ ,the binary string ‘Sₙ’ is
  *   formed as.
  *   
  *   - ‘S₁= "0"’.
  *   
  *   - ‘S⎽(<span style="font-size: 10.8333px;">i</span>)=S⎽(<span
  *   style="font-size: 10.8333px;">i-1</span>)+ "1" +
  *   reverse(invert(S⎽(<span style="font-size: 10.8333px;">i-1</span>)))’
  *   for ‘i > 1’.
  *   
  *   Where ‘+’ denotes the concatenation operation, ‘reverse(x)’ returns
  *   the reversed string <font face="monospace">x,</font>and ‘invert(x)’
  *   inverts all the bits in <font face="monospace">x</font> (0 changes to
  *   1 and 1 changes to 0).
  *   
  *   For example, the first 4 strings in the above sequence.
  *   
  *   - ‘S⎽(1)= "0"’.
  *   
  *   - ‘S⎽(2)= "0 “1” 1"’.
  *   
  *   - ‘S⎽(3)= "011 “1” 001"’.
  *   
  *   - ‘S₄ = "0111001 “1” 0110001"’.
  *   
  *   Return “the” ‘kᵗʰ’ “bit”  “in”  ‘Sₙ’ . It is guaranteed that ‘k’ is
  *   valid for the given ‘n’.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘1 ≤ n ≤ 20’
  *   • ‘1 ≤ k ≤ 2ⁿ - 1’
  *
*/

class Solution {
 public:
  char findKthBit(int n, int k) {
    if (n == 1) return '0';
    int half = 1 << (n - 1);
    if (k == half) {
      return '1';
    } else if (k < half) {
      return findKthBit(n - 1, k);
    } else {
      return findKthBit(n - 1, (half << 1) - k) == '0' ? '1' : '0';
    }
  }
};
}  // namespace l1545

#endif