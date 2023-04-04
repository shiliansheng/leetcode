// 滑动窗口

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int lengthOfLongestSubstring(string s) {
    int left = 0;                     // 左指针
    int right = 0;                    // 右指针
    int maxLen = 0;                   // 最长子串长度
    unordered_map<char, int> window;  // 窗口中每个字符出现的次数

    while (right < s.size()) {  // 右指针在字符串范围内
        char c = s[right];      // 右指针指向的字符
        right++;                // 右指针向右移动

        // 更新窗口中每个字符出现的次数
        window[c]++;

        // 如果窗口中出现重复字符，左指针向右移动直到窗口中不再有重复字符
        while (window[c] > 1) {
            char d = s[left];  // 左指针指向的字符
            left++;            // 左指针向右移动
            // 更新窗口中每个字符出现的次数
            window[d]--;
        }

        // 更新最长子串长度
        maxLen = max(maxLen, right - left);
    }

    return maxLen;
}

string minWindow(string s, string t) {
    unordered_map<char, int> needs, window;  // 需要的字母及其出现次数，当前窗口中的字母及其出现次数
    for (char c : t)
        needs[c]++;
    int left = 0, right = 0;       // 滑动窗口的左右指针
    int start = 0, len = INT_MAX;  // 记录当前最小子串的起始位置，最小字串的长度
    int valid = 0;                 // 当前窗口中已经包含了t中字母的个数
    while (right < s.size()) {     // 当窗口的右边界没有超出s的边界时，继续移动右指针扩大窗口
        char c = s[right];         // 取出字符c
        right++;                   // 右指针右移一位
        if (needs.count(c)) {      // 如果c是t中的字符，更新window中c的计数
            window[c]++;
            if (window[c] == needs[c])  // 如果window中c的计数等于t中c的计数，说明window中已经包含了t中所有c的数量
                valid++;                // 更新valid的值
        }
        while (valid == needs.size()) {  // 如果window已经包含了t中所有的字符，开始移动左指针缩小窗口
            if (right - left < len) {    // 如果当前窗口比当前最小值小，更新最小值
                start = left;            // 记录当前最小子串的起始位置
                len = right - left;      // 记录当前最小子串的长度
            }
            char d = s[left];               // 取出左指针所指的字符d
            left++;                         // 左指针右移一位
            if (needs.count(d)) {           // 如果d是t中的字符，更新window中d的计数
                if (window[d] == needs[d])  // 如果window中d的计数等于t中d的计数，说明window中已经不再包含t中所有d的数量
                    valid--;                // 更新valid的值
                window[d]--;                // 更新window中d的计数
            }
        }
    }
    // 如果未找到符合条件的子串，返回空串
    return len == INT_MAX ? "" : s.substr(start, len);  // 返回符合条件的最小子串
}

string minWindow2(string s, string t) {
    unordered_map<char, int> needs, window;
    string res = "";
    int minsize = INT_MAX, size = s.size(), l = 0, r = 0, valid = 0, validsize = 0, begin = 0;
    for (auto& c : t) {
        needs[c]++;
    }
    validsize = needs.size();
    while (r < size) {
        while (r < size && valid != validsize) {
            if (needs.count(s[r])) {
                window[s[r]]++;
                if (window[s[r]] == needs[s[r]]) {
                    ++valid;
                }
            }
            ++r;
        }
        while (l < r && validsize == valid) {
            if (needs.count(s[l])) {
                window[s[l]]--;
                if (window[s[l]] < needs[s[l]]) {
                    if (minsize > r - l) {
                        begin = l;
                        minsize = r - l;
                    }
                    --valid;
                }
            }
            ++l;
        }
    }
    return minsize == INT_MAX ? "" : s.substr(begin, minsize);
}

int main() {
    // string s = "abcabcbb";
    // int len = lengthOfLongestSubstring(s);
    // cout << len << endl; // 输出3，即"abc"的长度
    // cout << minWindow2("ADOBECODEBANC", "ABC") << endl;
    cout << minWindow2("cabwefgewcwaefgcf", "cae") << endl;
    return 0;
}
