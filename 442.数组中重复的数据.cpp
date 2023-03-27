/*
 * @lc app=leetcode.cn id=442 lang=cpp
 *
 * [442] 数组中重复的数据
 */

// @lc code=start
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums)
    {
        int size = nums.size();
        vector<int> res;
        for (int i = 0; i < size; i++) {
            while (nums[i] != i + 1 && nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
            if (nums[i] != i + 1)
                res.push_back(nums[i]);
        }
        return res;
    }
};
// @lc code=end

