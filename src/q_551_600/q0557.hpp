
#ifndef LEETCODE_Q557_H__
#define LEETCODE_Q557_H__

#include <iostream>
#include <string>

namespace l557 {
using namespace std;
class Solution {
 public:
  string reverseWords(string s) {
    int l = 0;
    for (int i = 1; i <= s.size(); ++i) {
      if ((i == s.size() || s[i] == ' ')) {
        reverse(s, l, i - 1);
        l = i;
      } else if (s[l] == ' ') {
        l = i;
      }
    }
    return s;
  }

 private:
  void reverse(string &s, int l, int r) {
    char c = ' ';
    while (l < r) {
      c = s[l];
      s[l++] = s[r];
      s[r--] = c;
    }
  }
};
}  // namespace l557

#endif