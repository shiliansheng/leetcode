/*
 * @lc app=leetcode.cn id=698 lang=cpp
 *
 * [698] 划分为k个相等的子集
 */

// @lc code=start
class Solution {
   public:
    bool backtrack(vector<int>& nums, vector<int>& buckets, int avg, int k, int end) {
        // 如果所有的元素都加入到桶中，则返回ture，如果出现有的元素加入不进桶中，则不会到end<0
        if (end < 0) return true;
        for (int i = 0; i < k; ++i) {
            // 如果加入end，当前桶溢出 或者 当前桶和前桶值相等，遍历下一个桶
            if (buckets[i] + nums[end] > avg || i && buckets[i] == buckets[i - 1]) {
                continue;
            }
            // 保证当前桶能装得下，遍历下一个元素
            buckets[i] += nums[end];
            if (backtrack(nums, buckets, avg, k, end - 1)) {
                return true;
            }
            // 如果当前桶失败，则还原桶的值
            buckets[i] -= nums[end];
        }
        return false;
    }
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int avg = accumulate(nums.begin(), nums.end(), 0), size = nums.size();
        // 如果总值不能保证平均分配到k个桶中，返回false
        if (avg % k != 0) return false;
        avg /= k;
        // 先sort
        sort(nums.begin(), nums.end());
        // 初始化k个桶，每个桶最终值为avg
        vector<int> buckets(k, 0);
        // 如果最大的数放不进桶，则满足不了条件
        return nums.back() <= avg && backtrack(nums, buckets, avg, k, size - 1);
    }
};
// @lc code=end
