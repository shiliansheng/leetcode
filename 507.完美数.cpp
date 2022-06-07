/*
 * @lc app=leetcode.cn id=507 lang=cpp
 *
 * [507] 完美数
 */

// @lc code=start
class Solution {
public:
    bool checkPerfectNumber(int num) {
        int scope = num >> 1, sum = 0;
        for (int i = 1; i <= scope; i++) {
            if (num % i == 0) {
                sum += i;
            }
            if (sum > num) {
                return false;
            }
        }
        if (sum == num) {
            return true;
        }
        return false;

    }
};
// @lc code=end

