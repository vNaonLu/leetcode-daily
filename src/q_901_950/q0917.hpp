
#ifndef LEETCODE_Q917_H__
#define LEETCODE_Q917_H__
#include <iostream>
#include <string>

namespace l917 {
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 917. Reverse Only Letters
  *
  * Given a string s , reverse the string according
  * to the following rules:
  * - All the characters that are not English letters
  * remain in the same position.
  * - All the English letters (lowercase or
  * uppercase) should be reversed.
  * Return s after reversing it .
  *
  * Constraints:
  * -  1 <= s.length <= 100 
  * -  s consists of characters with ASCII values in the range [33, 122] .
  * -  s does not contain ';\"'; or ';\\'; .
  *
*/
class Solution {
 private:
  bool isValidLetter(const char &c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }

 public:
  string reverseOnlyLetters(string s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
      if (!isValidLetter(s[l])) {
        ++l;
        continue;
      }
      if (!isValidLetter(s[r])) {
        --r;
        continue;
      }

      char t = s[l];
      s[l++] = s[r];
      s[r--] = t;
    }

    return s;
  }
};
}  // namespace l917
#endif