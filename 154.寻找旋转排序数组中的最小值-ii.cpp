/*
 * @lc app=leetcode.cn id=154 lang=cpp
 *
 * [154] 寻找旋转排序数组中的最小值 II
 */

// @lc code=start
class Solution {
public:
    int findMin(vector<int>& nums) {
        int high = nums.size() - 1, low = 0, mid;
        while (low <= high) {
            mid = high + low >> 1;
            if (nums[mid] < nums[high]) { // mid 是 最小值 右侧元素，忽略二分查找区间的右侧部分
                high = mid;
            } else if (nums[mid] > nums[high]) { // mid 是 最小值 左侧元素，忽略二分查找区间的左半部分
                low = mid + 1;
            } else { // mid == high 说明 最小值 在 mid 和 high 之间，因为不能确定 最小值 在 mid 左面还是右面，保守抛弃high，向左移动一位
                --high;
            }
        }
        return nums[low];
    }
};
// @lc code=end

