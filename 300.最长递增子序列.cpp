/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
 */

// @lc code=start
class Solution {
   public:
    int lengthOfLIS(vector<int>& nums) {
        int size = nums.size(), len = 1;
        vector<int> d(size + 1, 0);
        d[1] = nums[0];
        for (auto i = 0; i < size; ++i) {
            if (nums[i] <= d[len]) {  // 更新数组d，将nums[i]插入到相应的位置
                // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                int l = 1, r = len, pos = 0;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (nums[i] > d[mid]) {
                        pos = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            } else {
                d[++len] = nums[i];
            }
        }
        return len;
    }
    int lengthOfLIS_N2(vector<int>& nums) {
        // dp[i]是以当前为最大值的最大长度
        vector<int> dp(nums.size(), 1);
        int size = nums.size(), left = 0, right = 0, maxlen = 1;
        while (left <= right && right < size) {
            left = right;
            for (left = right - 1; left >= 0; left--) {
                if (nums[right] > nums[left]) {
                    dp[right] = max(dp[left] + 1, dp[right]);
                    maxlen = max(dp[right], maxlen);
                }
            }
            ++right;
        }
        return maxlen;
    }
};
// @lc code=end
