# 算法
> 一些算法

## 一般算法
> 普通算法，并非是数据结构等


## 图

### 并查集`disjoint-set`

#### 介绍

并查集（Disjoint-Set）是一种用于维护集合的数据结构，它支持快速合并（Union）和查找（Find）操作，常用于解决与连通性有关的问题。

并查集通常使用数组或者树来实现，其中每个元素都是一个独立的集合。在初始化时，每个元素都被视为一个单独的集合，其中的根节点指向自身。当需要将两个集合合并时，只需要将其中一个集合的根节点指向另一个集合的根节点即可。

同时，为了优化查询操作的效率，可以使用路径压缩（Path Compression）技术，即在查找根节点时将路径上的所有节点都指向根节点，从而使得下一次查找的速度更快。

#### 三种基本操作

1. clean：将并查集进行初始化，其祖先是该元素本身。
2. find：查询一个元素属于哪个集合。
3. Merge：合并两个集合。

#### 并查集优化

1. 路径压缩：
   所谓路径压缩就是在连接的时候把每一个子节点都连接到祖先节点上。
   路径压缩运行速度较快，也是现阶段较为常用的优化方法，但路径压缩会改变树的形态，不可以撤销操作或可持久化。
2. 按秩合并：
   所谓按序合并就是记录连接中两个树的高度，由低的连接到高的上，通常也可以记录 树 的大小。
   按秩合并的运行速度略慢与路径压缩，但是按秩合并不会改变树的形状态，多用于可撤销并查集和可持久化并查集中。

#### 代码

普通代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
int parent[MAXN];            // 记录元素的祖先,初始化每个元素都是一个单独的集合
void clean() {               // 初始化
    for (int i = 1; i <= MAXN; i++) {
        parent[i] = i;
    }
}
int find(int k) {     // 寻找该元素的祖先
    while (k != parent[k]) {
        k = parent[k];
    }
    return k;
}
void merge(int x, int y) { // 合并两个集合
    x = find(x);
    y = find(y);
    if (x != y) {
        parent[x] = y;
    }
}
int main() {
    // 初始化并查集
    for (int i = 1; i <= 10; ++i) {
        parent[i] = i;
    }
    // 将1和2合并到同一集合
    merge(1, 2);
    // 将3、4、5合并到同一集合
    merge(3, 4);
    merge(4, 5);
    // 将1所在集合和3所在集合合并
    merge(1, 3);
    // 输出每个元素所在的集合的根节点
    for (int i = 1; i <= 10; ++i) {
        cout << "parent[" << i << "] = " << find(i) << endl;
    }
    return 0;
}
```

路径压缩

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 10000;
vector<int> parent(MAXN, -1);  // 初始化每个元素都是一个单独的集合
int find(int x) {  // 查找元素x所在集合的根节点
    // 当前结点为根结点(<-1)或者为单独结点(-1)
    if (parent[x] < 0) { // abs(parent[x]) 为以当前结点为根结点的数的结点个数
        return x;
    }
    return parent[x] = find(parent[x]);  // 路径压缩
}
void merge(int x, int y) {  // 合并元素x和y所在的集合
    int root1 = find(x);
    int root2 = find(y);
    if (root1 != root2) { // 根结点不同，执行路径压缩
        // 将小集合合并到大集合中
        if (parent[root1] < parent[root2]) { // 根结点越小的结点所在的树，其结点树越多，即集合越大
            parent[root1] += parent[root2];
            parent[root2] = root1;
        } else {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
    }
}
int main() {
    // 初始化并查集
    for (int i = 1; i <= 10; ++i) {
        parent[i] = -1;
    }
    // 将1和2合并到同一集合
    merge(1, 2);
    // 将3、4、5合并到同一集合
    merge(3, 4);
    merge(4, 5);
    // 将1所在集合和3所在集合合并
    merge(1, 3);
    // 输出每个元素所在的集合的根节点
    for (int i = 1; i <= 10; ++i) {
        cout << "parent[" << i << "] = " << find(i) << endl;
    }
    return 0;
}
```

# 剑指 Offer

> 剑指 Offer 合集

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

因为所有的数都在 0~N-1 之间，所以只需要将当前 num 移动到 nums[num]处，如果当前位置的值和待移动处的值相同，则该位置的数为重复数

## 04. 二维数组中的查找 (240.搜索二维矩阵-ii)

> [240.搜索二维矩阵-ii](https://leetcode.cn/problems/search-a-2d-matrix-ii/)

根据已知规律：该矩阵内元素符合

-   每行的元素从左到右升序排列。
-   每列的元素从上到下升序排列。

对该矩阵按照某种方向进行遍历。

### 解法一

对该矩阵进行往右查找：

1. 如果当前元素比 target 小，先从上往下进行查找，找到第一个比 target 大或者找到**最后一行**，然后向右转
2. 如果当前元素比 target 大，再进行从下往上查找，直到找打一个比 target 小的数然后进行 1 的操作。

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

### 解法二 —— Z 形查找

在对于第一种解法中，我们不能保证 target 在当前位置`<i,j>`的指定方向（有可能在`<i,j>`的右上角，也有可能在`<i,j>`的右下角。

现在从右上角进行查找，因为对于规定矩阵：

1. 如果当前位置`<i,j>`比 target 大，那么下方所有的数都比 target 的大，那么只需要向左查找
2. 如果当前位置`<i,j>`比 target 小，那么左方所有的数都比 target 的小，那么只需要向下查找（`<i,j>`在最右侧，不需要考虑右边比 target 大的情况）

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

## 07. 重建二叉树 (105.从前序与中序遍历序列构造二叉树)

> [105.从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

### 方法一 递归

首先明白：
先序遍历遍历顺序是：根->左子树->右子树
中序遍历遍历顺序是：左子树->根->右子树

步骤：

1. 首先在先序序列的第一个结点是根节点，通过遍历中序序列找到根节点位置
2. 然后中序序列根节点前是根的左子树，根节点后是根的右子树
3. 最后分别将中序序列的左/右子树和先序序列的左/右子树进行构建，找准位置即可

优化：
如果使用传统的遍历方式去找到 root 结点在 inorder 中的 index 值，会增加时间复杂度，使用`unordered_map`进行存储`<value, index>`将会节省大量时间。

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

## 11. 旋转数组的最小数字 (154.寻找旋转排序数组中的最小值 II)

> [154.寻找旋转排序数组中的最小值 II](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/)

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

# Leetcode

> leetcode 普通合集

## 05. 最长回文子串

给你一个字符串 s，找到 s 中最长的回文子串。

如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。

示例 1：

输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
示例 2：

输入：s = "cbbd"
输出："bb"

提示：

1 <= s.length <= 1000
s 仅由数字和英文字母组成

### 算法一 贪心

```cpp
bool isPalindrome(string& s, int begin, int end) {
    while (begin <= end && s[begin] == s[end]) ++begin, --end;
    return s[begin] == s[end];
}
// 贪心算法，从回文子串最长长度开始遍历
string longestPalindrome2(string s) {
    int size = s.size(), len = size, begin = 0;
    // 枚举回文串的长度，最长是s.size，最短是2，默认不考虑1，N次
    while (len > 1) {
        // 遍历回文子串的开始位置，最大开始位置为size - len，因为要保证回文子串的长度，N次
        for (int i = 0; i <= size - len; ++i) {
            if (isPalindrome(s, i, i + len - 1)) {  // N / 2次
                return s.substr(i, len);
            }
        }
        --len;
    }
    return s.substr(0, 1);
}
```

### 算法二 动态规划

```cpp
// 动态规划
string longestPalindrome(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }
    // 定义最长回文子串的开始位置和最大长度
    int begin = 0, maxlen = 1;
    // 回文子串可能的长度为2~n
    for (int len = 2; len <= n; ++len) {
        // 遍历回文子串可能开始的地方为：0 ~ n-len
        for (int i = 0; i <= n - len; ++i) {
            // 获取回文子串结束的位置
            int j = i + len - 1;
            // 如果两端相等，判断除去两端的子串，即i+1 ~ j-1
            if (s[i] == s[j]) {
                // 如果去掉端点的子串至多只含有一个元素，即 j - 1 - (i + 1) + 1 < 2 即 j - i < 3
                // 或者长度大于3，且除去端点子串为回文串
                dp[i][j] = j - i < 3 || dp[i + 1][j - 1];
            }
            if (dp[i][j] && maxlen < len) {
                maxlen = len;
                begin = i;
            }
        }
    }
    return s.substr(begin, maxlen);
}
```

## 300. 最长递增子序列

给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，`[3,6,2,7]` 是数组 `[0,3,1,6,2,2,7]` 的子序列。

示例 1：

```
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
```

示例 2：

```
输入：nums = [0,1,0,3,2,3]
输出：4
```

示例 3：

```
输入：nums = [7,7,7,7,7,7,7]
输出：1
```

提示：

```
1 <= nums.length <= 2500
-10^4 <= nums[i] <= 10^4
```

进阶：

你能将算法的时间复杂度降低到 O(n log(n)) 吗?

### 方法一 动态规划

思路
定义一个`dp[i]`数组，表示前`i`个数中，最长递增子序列的最长长度。
`dp[i] = max(dp[j]) + 1`，其中`0<j<i且nums[j] < nums[i]`

```cpp
int lengthOfLIS(vector<int>& nums) {
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
```

### 方法二 贪心、二分查找

思路与算法
考虑一个简单的贪心，如果我们要使上升子序列尽可能的长，则我们需要让序列上升得尽可能慢，因此我们希望每次在上升子序列最后加上的那个数尽可能的小。

基于上面的贪心思路，我们维护一个数组`d[i]`，表示长度为`i`的最长上升子序列的末尾元素的最小值，用`len`记录目前最长上升子序列的长度，起始时`len`为 `1`， `d[1] = nums[0]`。

同时我们可以注意到`d[i]`是关于`i`单调递增的。因为如果`d[j] ≥ d[i]`且`j<i`， 我们考虑从长度为`i`的最长上升子序列的末尾删除`i-h`个元素，那么这个序列长度变为`j`，且第`j`个元素`x`(末尾元素)必然小于`d[i]`，也就小于`d[j]`。 那么我们就找到了一个长度为`j`的最长上升子序列，并且未尾元素比`d[j]`小，从而产生了矛盾。因此数组`d`的单调性得证。

我们依次遍历数组`nums`中的每个元素，并更新数组`d`和`len`的值。如果`nums[i]>d[len]`则更新`len=len+1`，否则在`d[1...len]`中找满足`d[i-1] < nums[j] < d[i]`的下标`i`，并更新`d[i]=nums[j]`。

根据`d`数组的单调性，我们可以使用二分查找寻找下标`i`，优化时间复杂度。
最后整个算法流程为:

设当前已求出的最长上升子序列的长度为`len`(初始时为 1)，从前往后遍历数组`nums`，在遍历到`nums[i]`时:

-   如果`nums[i]>d[len]`，则直接加入到`d`数组末尾，并更新`len=len+1`;
-   否则，在`d`数组中二分查找，找到第一个比`nums[i]`小的数`d[k]`，并更新`d[k+1]=nums[i]`。

```cpp
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
```

## 354. 俄罗斯套娃信封问题

给你一个二维整数数组 `envelopes` ，其中 `envelopes[i] = [wi, hi]` ，表示第 i 个信封的宽度和高度。
当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。

注意：不允许旋转信封。

示例 1：

```
输入：envelopes = [[5,4],[6,4],[6,7],[2,3]]
输出：3
解释：最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
```

示例 2：

```
输入：envelopes = [[1,1],[1,1],[1,1]]
输出：1
```

提示：

`1 <= envelopes.length <= 10^5`
`envelopes[i].length == 2`
`1 <= wi, hi <= 10^5`

### 方法一 动态规划

### 方法二 基于二分查找的动态规划

```cpp
int maxEnvelopes(vector<vector<int>>& envelopes) {
    int size = envelopes.size();
    // 宽度作为第一排序关键字，进行升序排列
    // 高度作为第二排序关键字，进行降序排列
    // 这样可以保证在宽度一定的情况下，只选择唯一高度的信封
    // 从而将问题转换为，忽略宽度，寻找高度的最长单调递增子序列
    sort(envelopes.begin(), envelopes.end(), [](const auto& a, const auto& b) {
        return a[0] < b[0] || a[0] == b[0] && a[1] > b[1];
    });
    vector<int> f = {envelopes[0][1]};
    int num;
    for (int i = 1; i < size; ++i) {
        num = envelopes[i][1];
        if (num > f.back()) {
            f.push_back(num);
        } else {
            auto pos = lower_bound(f.begin(), f.end(), num);
            *pos = num;
        }
    }
    return f.size();
}
```

## 698.划分为 K 个相等的子集

给定一个整数数组   nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。

示例

```
示例 1：
输入： nums = [4, 3, 2, 3, 5, 2, 1], k = 4
输出： True
说明： 有可能将其分成 4 个子集（5），（1,4），（2,3），（2,3）等于总和。

示例 2:
输入: nums = [1,2,3,4], k = 3
输出: false
```

提示：

`1 <= k <= len(nums) <= 16`
`0 < nums[i] < 10000`
每个元素的频率在 `[1,4]` 范围内

### 最优解 回溯剪枝

首先建立 k 个桶，往里面挨个放数字
当当前桶放入数字后大于 sum 或者当前桶的值和前一个桶相等，就去找下一个桶，否则就开始回溯。
当将整个 nums 遍历完时，由于进入递归时必然每个桶值都不大于 sum，而最终所有桶必然平均为 sum，因此此时必定满足每个桶都为 sum，返回 true。当存在一个值放不进每一个桶，返回 false。

```
为什么这里是剪枝呢？
有一个前提条件，nums是非递减数组，从nums尾部加入顺序桶中，则nums[end]会顺序依次判断能否加入当前桶中，
对于每次递归总是从i=0开始，当i>0时，我们就应该考虑为什么i>0时bucket[i] == buckets[i - 1]要跳过呢？
因为对于nums[end]加入[桶i]来说，加入[桶i-1]是其前一步
如果nums[end]加入[桶i-1]满足成功条件，则将不会判断能不能够加入[桶i]这一层循环
判断能否加入[桶i]说明nums[end]是不能够加入[桶i-1]的，因为[桶i]和[桶i-1]两个桶值相等，加入[桶i]也会失败
```

```cpp
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
```

### 解法一 状态压缩+记忆化搜索

题目给定长度为 `n` 的数组 `nums`，和整数 `k`，我们需要判断是否能将数组分成 `k` 个总和相等的非空子集。
首先计算数组的和 `all`，如果 `all` 不是 `k` 的倍数，那么不可能能有合法方案，此时直接返回 `False`。
否则我们需要得到 k 个和为 `per=all/k` 的集合，那么我们每次尝试选择一个还在数组中的数，若选择后当前已选数字和等于 `per` 则说明得到了一个集合，而已选数字和大于 `per` 时，不可能形成一个集合从而停止继续往下选择新的数字。
又因为 `n` 满足 `1≤n≤16` ，所以我们可以用一个整数 `S` 来表示当前可用的数字集合：从低位到高位，第 `i` 位为 `1` 则表示数字 `nums[i]` 可以使用，否则表示 `nums[i]` 已被使用。为了避免相同状态的重复计算，我们用 `dp[S]` 来表示在可用的数字状态为 `S` 的情况下是否可行，初始全部状态为记录为可行状态 `True`。
这样我们就可以通过记忆化搜索这种「自顶向下」的方式来进行求解原始状态的可行性，而当状态集合中不存在任何数字时，即 `S=0` 时，表示原始数组可以按照题目要求来进行分配，此时返回 `True` 即可。

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        // 将 nums 数组中的所有元素求和
        int all = accumulate(nums.begin(), nums.end(), 0);
        // 如果所有元素的和不能被 k 整除，就不可能将 nums 分成 k 个子集
        if (all % k > 0) {
            return false;
        }
        // 每个子集的和应该是 all / k
        int per = all / k;
        // 如果 nums 中最大的元素比 per 还大，那么肯定无法将 nums 分成 k 个和相等的子集
        sort(nums.begin(), nums.end());
        if (nums.back() > per) {
            return false;
        }
        // n 表示 nums 数组的大小
        int n = nums.size();
        // dp 数组表示是否能从 nums 中的一些数中取出一些元素，使得它们的和等于 j
        // 初始时，全部置为 true
        vector<bool> dp(1 << n, true);
        // 利用动态规划实现搜索过程
        // dfs 表示深度优先搜索的函数
        // s 表示当前还未被分配到子集中的元素集合对应的状态，每个二进制位对应一个元素是否被分配
        // p 表示当前正在填充的子集的和
        function<bool(int,int)> dfs = [&](int s, int p)->bool {
            // 如果 s 已经被分配完了，就返回 true
            if (s == 0) {
                return true;
            }
            // 如果之前搜索过相同状态，则直接返回
            if (!dp[s]) {
                return dp[s];
            }
            // 假设当前的状态 s 无法得到合法的子集，将 dp[s] 置为 false
            dp[s] = false;
            // 遍历 nums 数组中的所有元素，尝试将它们加入到当前正在填充的子集中
            for (int i = 0; i < n; i++) {
                // 如果加上当前元素 nums[i] 之后，当前子集的和已经大于 per 了，就无需继续尝试
                if (nums[i] + p > per) {
                    break;
                }
                // 如果第 i 个元素尚未被分配到任何一个子集中，就尝试将其分配到当前子集中
                if ((s >> i) & 1) {
                    // dfs(s ^ (1 << i), (p + nums[i]) % per) 表示将第 i 个元素分配到当前子集中，并递归地寻找剩下的元素是否能被分配到其他子集中
                    // 如果 dfs(s ^ (1 << i), (p + nums[i]) % per) 返回 true，表示剩下的元素都能被分配到其他子集中，那么就直接返回 true
                    if (dfs(s ^ (1 << i), (p + nums[i]) % per)) {
                        return true;
                    }
                }
            }
            // 搜索失败
            return false;
        };
        // 从所有元素都未被选中的状态开始搜索
        return dfs((1 << n) - 1, 0);
    }
};
```

### 解法二 状态压缩+动态规划

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int all = accumulate(nums.begin(), nums.end(), 0); // 计算数组nums中所有元素的和
        if (all % k > 0) { // 如果sum不能被k整除，无法将数组划分为k个相等的子集，返回false
            return false;
        }
        int per = all / k; // 每个子集的和应该为per
        sort(nums.begin(), nums.end()); // 对数组nums排序
        if (nums.back() > per) { // 如果数组中最大的元素大于per，返回false
            return false;
        }
        int n = nums.size(); // 数组nums的大小
        vector<bool> dp(1 << n, false); // dp数组，大小为2^n，初始值均为false
        vector<int> curSum(1 << n, 0); // curSum数组，大小为2^n，初始值均为0
        dp[0] = true; // 不使用任何元素可以构成和为0的子集
        for (int i = 0; i < 1 << n; i++) { // 枚举dp数组中所有为true的下标i
            if (!dp[i]) { // 如果dp[i]为false，跳过本次循环
                continue;
            }
            for (int j = 0; j < n; j++) { // 枚举数组nums中的所有元素j
                if (curSum[i] + nums[j] > per) { // 如果将nums[j]加入到和为i的子集中，使得和超过per，跳过本次循环
                    break;
                }
                if (((i >> j) & 1) == 0) { // 如果nums[j]没有被使用过
                    int next = i | (1 << j); // 将nums[j]加入到和为i的子集中，得到新的下标next
                    if (!dp[next]) { // 如果dp[next]为false
                        curSum[next] = (curSum[i] + nums[j]) % per; // 更新curSum[next]的值
                        dp[next] = true; // 将dp[next]设为true
                    }
                }
            }
        }
        // 如果dp[(1 << n) - 1]为true，表示可以使用nums中的所有元素构成和为per的k个相等的子集，返回true，否则返回false
        return dp[(1 << n) - 1];
    }
};
```

## 1149. 数青蛙

给你一个字符串 `croakOfFrogs`，它表示不同青蛙发出的蛙鸣声（字符串 `"croak" `）的组合。由于同一时间可以有多只青蛙呱呱作响，所以 `croakOfFrogs` 中会混合多个 `“croak”` 。

请你返回模拟字符串中所有蛙鸣所需不同青蛙的最少数目。

要想发出蛙鸣 `"croak"`，青蛙必须 依序 输出 `‘c’, ’r’, ’o’, ’a’, ’k’` 这 5 个字母。如果没有输出全部五个字母，那么它就不会发出声音。如果字符串 `croakOfFrogs` 不是由若干有效的 `"croak"` 字符混合而成，请返回 -1 。

### 解法

统计青蛙叫的组成部分（5 份，以各个字母为一份）

-   如果当前不是`c`，则必须保证当前部分必须小于前面部分的个数，否则返回`-1`，表示不能组成青蛙叫
-   出现`c`表示青蛙开始叫，增加当前在叫青蛙个数，并更新最大青蛙数
-   出现`k`表示青蛙结束叫，减少当前在叫的青蛙个数
-   循环各个字符直到结尾
-   如果最终还有青蛙在叫（有的青蛙没叫完），说明有的青蛙不完整，返回`-1`，否则返回最大青蛙数

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
