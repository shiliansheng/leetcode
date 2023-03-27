# 剑指 Offer

## 03. 数组中重复的数字

前提描述：
给定大小为 N 的数组，数组内所有元素均属于[0~N-1]

### 解法一

使用 unordered_map 进行 hash 查询，将找到的所有键值不唯一的存入结果数组中。

```c++
vector<int> findDuplicates(vector<int>& nums) {
    unordered_map<int, int> numMap;
    vector<int> res;
    for (int num : nums) {
        if (numMap.find(num) != numMap.end())
            res.push_back(num);
        else
            numMap[num] = 1;
    }
    return res;
}
```

### 解法二

因为所有的数都在0~N-1之间，所以只需要将当前num移动到nums[num]处，如果当前位置的值和待移动处的值相同，则该位置的数为重复数



## 04. 二维数组中的查找

*==>240.搜索二维矩阵-ii*

根据已知规律：该矩阵内元素符合

- 每行的元素从左到右升序排列。
- 每列的元素从上到下升序排列。

对该矩阵按照某种方向进行遍历。

### 解法一

对该矩阵进行往右查找：
1. 如果当前元素比target小，先从上往下进行查找，找到第一个比target大或者找到**最后一行**，然后向右转
2. 如果当前元素比target大，再进行从下往上查找，直到找打一个比target小的数然后进行1的操作。

```cpp
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
```

### 解法二 —— Z形查找

在对于第一种解法中，我们不能保证target在当前位置`<i,j>`的指定方向（有可能在`<i,j>`的右上角，也有可能在`<i,j>`的右下角。

现在从右上角进行查找，因为对于规定矩阵：
1. 如果当前位置`<i,j>`比target大，那么下方所有的数都比target的大，那么只需要向左查找
2. 如果当前位置`<i,j>`比target小，那么左方所有的数都比target的小，那么只需要向下查找（`<i,j>`在最右侧，不需要考虑右边比target大的情况）

官方解释：

我们可以从矩阵 matrix 的右上角 `(0,n−1)` 进行搜索。在每一步的搜索过程中，如果我们位于位置 `(x,y)`，那么我们希望在以 matrix 的左下角为左下角、以 `(x,y)` 为右上角的矩阵中进行搜索，即行的范围为 `[x,m−1]`，列的范围为`[0,y]`：

如果 `matrix[x,y]=target`，说明搜索完成；

如果 `matrix[x,y]>target`，由于每一列的元素都是升序排列的，那么在当前的搜索矩阵中，所有位于第 y 列的元素都是严格大于 target 的，因此我们可以将它们全部忽略，即将 y 减少 1；

如果 `matrix[x,y]<target`，由于每一行的元素都是升序排列的，那么在当前的搜索矩阵中，所有位于第 x 行的元素都是严格小于 target 的，因此我们可以将它们全部忽略，即将 x 增加 1。

在搜索的过程中，如果我们超出了矩阵的边界，那么说明矩阵中不存在 target。

```cpp
// 官方代码
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rown = matrix.size(), coln = matrix[0].size();
    int i = 0, j = coln - 1;
    while (i < rown && j >= 0) {
        if (matrix[i][j] == target) {
            return true;
        }
        if (matrix[i][j] > target) {
            j--;
        } else {
            i++;
        }
    }
    return false; // 越界即找不到

}
```

## 07. 重建二叉树

### 方法一 递归
首先明白：
先序遍历遍历顺序是：根->左子树->右子树
中序遍历遍历顺序是：左子树->根->右子树

步骤：
1. 首先在先序序列的第一个结点是根节点，通过遍历中序序列找到根节点位置
2. 然后中序序列根节点前是根的左子树，根节点后是根的右子树
3. 最后分别将中序序列的左/右子树和先序序列的左/右子树进行构建，找准位置即可

优化：
如果使用传统的遍历方式去找到root结点在inorder中的index值，会增加时间复杂度，使用`unordered_map`进行存储`<value, index>`将会节省大量时间。

```cpp
class Solution {
public:
    // 使用map[inorder.val] = inorder.index增加查找速度
    unordered_map<int, int> inorder_root_index;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int size = preorder.size();
        for (int i = 0; i < size; i++)
            inorder_root_index[inorder[i]] = i;
        return buildTreeExec(preorder, inorder, 0, size - 1, 0, size - 1);
    }
    // pb - pe 为整棵树在preorder中的范围，ib - ie为整棵树在inorder中的范围
    TreeNode* buildTreeExec(vector<int> preorder, vector<int> inorder, int pb, int pe, int ib, int ie) {
        if (pb > pe || ib > ie) {
            return nullptr;
        }
        int rootIdx = inorder_root_index[preorder[pb]];
        int left_size = rootIdx - ib;
        // 此时rootIdx为inorder中root的index
        TreeNode *root = new TreeNode(preorder[pb]);
        root->left = buildTreeExec(preorder, inorder, pb + 1, pb + left_size, ib, rootIdx - 1);
        root->right = buildTreeExec(preorder, inorder, pb + 1 + left_size, pe, rootIdx + 1, ie);
        return root;
    }
};
```

### 方法二 迭代




## 11. 旋转数组的最小数字
*[154] 寻找旋转排序数组中的最小值 II*

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。

该数组可能存在重复元素

### 解法一 直接遍历

思路：
进行遍历，找到下一个数比前一个数小的数，小的数就是最小的数。
```cpp
int minArray(vector<int>& numbers) {
    int size = numbers.size(), i = 0, minNum = numbers[0];
    while (i < size - 1) {
        if (numbers[i] > numbers[i + 1]) {
            minNum = numbers[i + 1]; 
        }
        i++;
    }
    return minNum;
}
```

### 解法二 二分查找

二分法基本标准：找到某一游标，左边和右边所有数据对比游标分别符合某种规则

前提：对于旋转数组来说，`arr[left] >= arr[right]`

思路：

我们考虑数组中的最后一个元素 x：在最小值右侧的元素，它们的值一定都小于等于 x；而在最小值左侧的元素，它们的值一定都大于等于 x。因此，我们可以根据这一条性质，通过二分查找的方法找出最小值。

在二分查找的每一步中，左边界为 low，右边界为 high，区间的中点为 pivot，最小值就在该区间内。我们将中轴元素 `nums[pivot]` 与右边界元素 `nums[high]` 进行比较，可能会有以下的三种情况：

第一种情况是 `nums[pivot]<nums[high]`。说明 `nums[pivot]` 是最小值右侧的元素，因此我们可以忽略二分查找区间的右半部分。

第二种情况是 `nums[pivot]>nums[high]`。这说明 `nums[pivot]` 是最小值左侧的元素，因此我们可以忽略二分查找区间的左半部分。

第三种情况是 `nums[pivot]==nums[high]`。由于重复元素的存在，我们并不能确定 `nums[pivot]` 究竟在最小值的左侧还是右侧，因此我们不能莽撞地忽略某一部分的元素。我们唯一可以知道的是，由于它们的值相同，所以无论 `nums[high]` 是不是最小值，都有一个它的「替代品」`nums[pivot]`，因此我们可以忽略二分查找区间的右端点。

```cpp
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
```

## 1149. 数青蛙

给你一个字符串 `croakOfFrogs`，它表示不同青蛙发出的蛙鸣声（字符串 `"croak" `）的组合。由于同一时间可以有多只青蛙呱呱作响，所以 `croakOfFrogs` 中会混合多个 `“croak”` 。

请你返回模拟字符串中所有蛙鸣所需不同青蛙的最少数目。

要想发出蛙鸣 `"croak"`，青蛙必须 依序 输出 `‘c’, ’r’, ’o’, ’a’, ’k’` 这 5 个字母。如果没有输出全部五个字母，那么它就不会发出声音。如果字符串 `croakOfFrogs` 不是由若干有效的 `"croak"` 字符混合而成，请返回 -1 。

### 解法

统计青蛙叫的组成部分（5份，以各个字母为一份）
- 如果当前不是`c`，则必须保证当前部分必须小于前面部分的个数，否则返回`-1`，表示不能组成青蛙叫
- 出现`c`表示青蛙开始叫，增加当前在叫青蛙个数，并更新最大青蛙数
- 出现`k`表示青蛙结束叫，减少当前在叫的青蛙个数
- 循环各个字符直到结尾
- 如果最终还有青蛙在叫（有的青蛙没叫完），说明有的青蛙不完整，返回`-1`，否则返回最大青蛙数
```cpp
class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs)
    {
        unordered_map<char, int> chMid { { 'c', 0 }, { 'r', 1 }, { 'o', 2 }, { 'a', 3 }, { 'k', 4 } };
        // cnts 统计青蛙叫的各个部分的数量，必须满足前面的数量大于或等于后面的数量
        // cnt 统计当前正在叫的青蛙的数量
        // res 统计正在叫的青蛙的最大数量
        int cnts[5] = { 0 }, cnt = 0, res = 0, idx = 0;
        for (auto ch : croakOfFrogs) {
            idx = chMid[ch];
            // 当出现c 表示青蛙开始叫，增加当前青蛙在叫的个数
            // 统计需要青蛙最多的数量
            if (idx == 0) {
                ++cnt;
                res = max(res, cnt);
            }
            // 当出现k 青蛙完成叫，减少当前正在叫的青蛙个数
            if (idx == 4) --cnt;
            // 如果不是开始叫的情况下，后面的部分如果大于或者等于前面的部分，说明当前部分叫不出来
            if (idx && cnts[idx - 1] <= cnts[idx])
                return -1;
            // 记录青蛙叫的部分
            ++cnts[idx];
        }
        // 如果还存在正在叫的青蛙，返回-1
        return cnt == 0 ? res : -1;
    }
};
```