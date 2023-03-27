/*
 * @lc app=leetcode.cn id=485 lang=cpp
 *
 * [485] 最大连续 1 的个数
 */

// @lc code=start
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int max = 0, rec = 0;
        for (int i : nums) {
            rec = i ? rec + 1 : 0;
            max = rec > max ? rec : max;
        }
        return max;
    }
};
// @lc code=end

