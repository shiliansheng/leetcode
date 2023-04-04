// �����㷨

#include <iostream>
#include <vector>
using namespace std;

// ���ݺ���
void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& used, vector<vector<int>>& res) {
    if (path.size() == nums.size()) {  // ����Ѿ�ѡ����������������ǰ���м��뵽�������
        res.push_back(path);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) {  // ��������Ѿ���ѡ��������
            continue;
        }
        path.push_back(nums[i]);           // ���������뵽��ǰ������
        used[i] = true;                    // ��Ǹ����Ѿ���ѡ��
        backtrack(nums, path, used, res);  // ����������һ����
        used[i] = false;                   // ���ݣ����������Ϊδѡ��
        path.pop_back();                   // ���ݣ��������ӵ�ǰ������ɾ��
    }
}

// ���ȫ��������
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> used(nums.size(), false);  // ��¼ÿ�����Ƿ��Ѿ���ѡ��
    backtrack(nums, path, used, res);
    return res;
}

// ���Դ���
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
