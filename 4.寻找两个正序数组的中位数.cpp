/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 */

// @lc code=start
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 寻找中位数
        // 先计算中位数的位置，即两个数组合并后的中心位置
        int size1 = nums1.size(), size2 = nums2.size(), size = size1 + size2, mid = size >> 1;
        // 如果总长度为奇数，则mid = size / 2，3/2 = 1，只需要找到合并数组位置为 1 = mid 的数
        // 如果总长度为偶数，则mid = size / 2，4/2 = 2，需要找到合并数组位置为 1 = mid - 1 和 2 = mid 的两个数
        int pos1 = 0, pos2 = 0, pos = 0, mid1 = 0, mid2 = 0;
        while (pos <= mid) {
            mid1 = mid2;
            if (pos1 < size1 && (pos2 >= size2 || nums1[pos1] < nums2[pos2])) {
                mid2 = nums1[pos1++];
            } else {
                mid2 = nums2[pos2++];
            }
            pos++;
        }
        //     判断奇偶数  奇数       偶数
        return size % 2 ? mid2 : 1.0 * (mid1 + mid2) / 2;
    }
};
// @lc code=end
