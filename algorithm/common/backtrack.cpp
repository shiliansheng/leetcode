// 回溯算法

#include <iostream>
#include <vector>
using namespace std;

// 回溯函数
void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& used, vector<vector<int>>& res) {
    if (path.size() == nums.size()) {  // 如果已经选完了所有数，将当前排列加入到结果集中
        res.push_back(path);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) {  // 如果该数已经被选过，跳过
            continue;
        }
        path.push_back(nums[i]);           // 将该数加入到当前排列中
        used[i] = true;                    // 标记该数已经被选过
        backtrack(nums, path, used, res);  // 继续搜索下一个数
        used[i] = false;                   // 回溯，将该数标记为未选过
        path.pop_back();                   // 回溯，将该数从当前排列中删除
    }
}

// 解决全排列问题
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> used(nums.size(), false);  // 记录每个数是否已经被选过
    backtrack(nums, path, used, res);
    return res;
}

// 测试代码
int main() {
    vector<int> nums{1, 2, 3};
    vector<vector<int>> res = permute(nums);
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
