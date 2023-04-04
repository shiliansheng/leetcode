// 并查集

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000;

vector<int> parent(MAXN, -1);  // 初始化每个元素都是一个单独的集合

int fa[100001];                // 记录元素的祖先
void clean()                   // 初始化
{
    for (int i = 1; i <= MAXN; i++) {
        fa[i] = i;
    }
}
int find_pc(int x) {  // 查找元素x所在集合的根节点
    if (parent[x] < 0) {
        return x;
    }
    return parent[x] = find_pc(parent[x]);  // 路径压缩
}

int find_comm(int k)  // 寻找该元素的祖先
{
    while (k != fa[k]) {
        k = fa[k];
    }
    return k;
}

void merge_pc(int x, int y) {  // 合并元素x和y所在的集合
    int root1 = find_pc(x);
    int root2 = find_pc(y);
    if (root1 != root2) {
        if (parent[root1] < parent[root2]) {  // 将小集合合并到大集合中
            parent[root1] += parent[root2];
            parent[root2] = root1;
        } else {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
    }
}

void merge_comm(int x, int y)  // 合并两个集合
{
    x = find_comm(x);
    y = find_comm(y);
    if (x != y) {
        fa[x] = y;
    }
}

void PathCompression() {
    // 初始化并查集
    for (int i = 1; i <= 10; ++i) {
        parent[i] = -1;
    }

    // 将1和2合并到同一集合
    merge_pc(1, 2);

    // 将3、4、5合并到同一集合
    merge_pc(3, 4);
    merge_pc(4, 5);

    // 将1所在集合和3所在集合合并
    merge_pc(1, 3);

    // 输出每个元素所在的集合的根节点
    for (int i = 1; i <= 10; ++i) {
        cout << "parent[" << i << "] = " << find_pc(i) << endl;
    }
}

void CommonSet() {
    // 初始化并查集
    for (int i = 1; i <= 10; ++i) {
        fa[i] = i;
    }

    // 将1和2合并到同一集合
    merge_comm(1, 2);

    // 将3、4、5合并到同一集合
    merge_comm(3, 4);
    merge_comm(4, 5);

    // 将1所在集合和3所在集合合并
    merge_comm(1, 3);

    // 输出每个元素所在的集合的根节点
    for (int i = 1; i <= 10; ++i) {
        cout << "parent[" << i << "] = " << find_comm(i) << endl;
    }
}

int main() {
    PathCompression();
    cout << "common set" << endl;
    CommonSet();
    return 0;
}
