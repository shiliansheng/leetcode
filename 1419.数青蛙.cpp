/*
 * @lc app=leetcode.cn id=1419 lang=cpp
 *
 * [1419] 数青蛙
 */

// @lc code=start
class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs)
    {
        unordered_map<char, int> chMid { { 'c', 0 }, { 'r', 1 }, { 'o', 2 }, { 'a', 3 }, { 'k', 4 } };
        // cnts 统计青蛙叫的各个部分的数量，必须满足前面的数量大于或等于后面的数量
        // cnt 统计当前正在叫的青蛙的数量
        // res 统计正在叫的青蛙的最大数量
        int cnts[5] = { 0 }, i = 0, cnt = 0, res = 0;
        for (auto ch : croakOfFrogs) {
            // 当出现c表示青蛙开始叫，增加当前青蛙在叫的个数
            cnt += chMid[ch] == 0;
            // 统计需要青蛙最多的数量
            if (ch == 'c')
                res = max(res, cnt);
            // 当青蛙叫完后，减少当前正在叫的青蛙个数
            cnt -= chMid[ch] == 4;
            // 记录青蛙叫的部分
            ++cnts[chMid[ch]];

            // 判断当前青蛙是否成功完成叫声 指前面必须大于或等于后面的数量
            i = 0;
            while (i < 4 && cnts[i] >= cnts[i + 1])
                ++i;
            if (i != 4)
                return -1;
        }
        // 如果还存在正在叫的青蛙，返回-1
        return cnt == 0 ? res : -1;
    }
};
// @lc code=end
