// 并查集 - 路径优化

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000;

vector<int> parent(MAXN, -1);  // 初始化每个元素都是一个单独的集合

int find(int x) {  // 查找元素x所在集合的根节点
    // 当前结点为根结点(<-1)或者为单独结点(-1)
    if (parent[x] < 0) {  // abs(parent[x]) 为以当前结点为根结点的数的结点个数
        return x;
    }
    return parent[x] = find(parent[x]);  // 路径压缩
}

void merge(int x, int y) {  // 合并元素x和y所在的集合
    int root1 = find(x);
    int root2 = find(y);
    if (root1 != root2) {
        // 将小集合合并到大集合中
        if (parent[root1] < parent[root2]) {  // 根结点越小的结点所在的树，其结点树越多，即集合越大
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
