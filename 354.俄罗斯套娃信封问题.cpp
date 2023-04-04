/*
 * @lc app=leetcode.cn id=354 lang=cpp
 *
 * [354] 俄罗斯套娃信封问题
 */

// @lc code=start
class Solution {
   public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int size = envelopes.size();
        // width为第一排序关键字，增序排列
        // height为第二排序关键字，降序排列
        // 将问题转换为寻找height的最长递增子序列
        sort(envelopes.begin(), envelopes.end(), [](const auto& a, const auto& b) {
            return a[0] < b[0] || a[0] == b[0] && a[1] > b[1];
        });
        // 维护一个f[i]，f[i]为长度为i的 以height为关键字的 最长递增子序列的最小值末尾
        vector<int> f = {envelopes[0][1]};
        int num;
        for (auto& env : envelopes) {
            num = env[1];
            if (f.back() < num) {
                f.push_back(num);
            } else {
                auto pos = lower_bound(f.begin(), f.end(), num);
                *pos = num;
            }
        }
        return f.size();
    }
};
// @lc code=end
