/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */

// @lc code=start
class Solution {
   public:
    bool isPalindrome(string& s, int begin, int end) {
        while (begin <= end && s[begin] == s[end]) ++begin, --end;
        return s[begin] == s[end];
    }
    // 贪心算法，从回文子串最长长度开始遍历
    string longestPalindrome2(string s) {
        int size = s.size(), len = size, begin = 0;
        // 枚举回文串的长度，最长是s.size，最短是2，默认不考虑1，N次
        while (len > 1) {
            // 遍历回文子串的开始位置，最大开始位置为size - len，因为要保证回文子串的长度，N次
            for (int i = 0; i <= size - len; ++i) {
                if (isPalindrome(s, i, i + len - 1)) {  // N / 2次
                    return s.substr(i, len);
                }
            }
            --len;
        }
        return s.substr(0, 1);
    }
    // 动态规划
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
        }
        // 定义最长回文子串的开始位置和最大长度
        int begin = 0, maxlen = 1;
        // 回文子串可能的长度为2~n
        for (int len = 2; len <= n; ++len) {
            // 遍历回文子串可能开始的地方为：0 ~ n-len
            for (int i = 0; i <= n - len; ++i) {
                // 获取回文子串结束的位置
                int j = i + len - 1;
                // 如果两端相等，判断除去两端的子串，即i+1 ~ j-1
                if (s[i] == s[j]) {
                    // 如果去掉端点的子串至多只含有一个元素，即 j - 1 - (i + 1) + 1 < 2 即 j - i < 3
                    // 或者长度大于3，且除去端点子串为回文串
                    dp[i][j] = j - i < 3 || dp[i + 1][j - 1];
                }
                if (dp[i][j] && maxlen < len) {
                    maxlen = len;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxlen);
    }
};
// @lc code=end

