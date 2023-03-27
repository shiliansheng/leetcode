/*
 * @lc app=leetcode.cn id=1323 lang=cpp
 *
 * [1323] 6 和 9 组成的最大数字
 */

// @lc code=start
class Solution {
public:
    int maximum69Number (int num) {
        int res = num, rec = 0, iter = 1;
        while(num) {
            if (num % 10 == 6) rec = iter;
            iter *= 10;
            num /= 10;
        }
        res += 3 * rec;
        return res;
    }
};
// @lc code=end

