/*
 * @lc app=leetcode.cn id=240 lang=cpp
 *
 * [240] 搜索二维矩阵 II
 */

// @lc code=start
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rown = matrix.size(), coln = matrix[0].size(), i = 0, j = 0;
        // 先从上往下找，再从左往右找
        while (i < rown && j < coln && i >= 0 && j >= 0) {
            if (matrix[i][j] == target) {
                return true;
            }
            if (matrix[i][j] < target) {
                if (i == rown - 1 || i < rown - 1 && matrix[i + 1][j] > target) {
                    j++;
                } else {
                    i++;
                }
            } else if (matrix[i][j] > target) {
                i--;
            }
        }
        return false;
    }
};
// @lc code=end

