/*
 * @lc app=leetcode.cn id=520 lang=cpp
 *
 * [520] 检测大写字母
 */

// @lc code=start
class Solution {
public:
    bool isUppercase(char ch) {
        return ch <= 'Z' && ch >= 'A';
    }
    bool detectCapitalUse(string word) {
        int len = word.length();
        if (len == 1) return true;
        int partten = 0;
        if (!isUppercase(word[0]) || !isUppercase(word[1])) {
            partten = 1;
        }
        if (partten) {
            for (int i = 1; i < len; i++) {
                if (isUppercase(word[i])) {
                    return false;
                }
            }
        } else {
            for (int i = 1; i < len; i++) {
                if (!isUppercase(word[i])) {
                    return false;
                }
            }
        }
        return true;
    }
};
// @lc code=end

