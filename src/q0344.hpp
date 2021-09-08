
#ifndef LEETCODE_Q344_H__
#define LEETCODE_Q344_H__

#include <iostream>
#include <vector>

namespace l344{
using namespace std;
class Solution {
 public:
  void reverseString(vector<char>& s) {
    int l = 0, r = s.size() - 1;
    char tmp = ' ';
    while (l <= r) {
      tmp = s[r];
      s[r--] = s[l];
      s[l++] = tmp;
    }
  }
};
}

#endif