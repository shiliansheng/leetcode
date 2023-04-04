// ���鼯

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000;

vector<int> parent(MAXN, -1);  // ��ʼ��ÿ��Ԫ�ض���һ�������ļ���

int fa[100001];                // ��¼Ԫ�ص�����
void clean()                   // ��ʼ��
{
    for (int i = 1; i <= MAXN; i++) {
        fa[i] = i;
    }
}
int find_pc(int x) {  // ����Ԫ��x���ڼ��ϵĸ��ڵ�
    if (parent[x] < 0) {
        return x;
    }
    return parent[x] = find_pc(parent[x]);  // ·��ѹ��
}

int find_comm(int k)  // Ѱ�Ҹ�Ԫ�ص�����
{
    while (k != fa[k]) {
        k = fa[k];
    }
    return k;
}

void merge_pc(int x, int y) {  // �ϲ�Ԫ��x��y���ڵļ���
    int root1 = find_pc(x);
    int root2 = find_pc(y);
    if (root1 != root2) {
        if (parent[root1] < parent[root2]) {  // ��С���Ϻϲ����󼯺���
            parent[root1] += parent[root2];
            parent[root2] = root1;
        } else {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
    }
}

void merge_comm(int x, int y)  // �ϲ���������
{
    x = find_comm(x);
    y = find_comm(y);
    if (x != y) {
        fa[x] = y;
    }
}

void PathCompression() {
    // ��ʼ�����鼯
    for (int i = 1; i <= 10; ++i) {
        parent[i] = -1;
    }

    // ��1��2�ϲ���ͬһ����
    merge_pc(1, 2);

    // ��3��4��5�ϲ���ͬһ����
    merge_pc(3, 4);
    merge_pc(4, 5);

    // ��1���ڼ��Ϻ�3���ڼ��Ϻϲ�
    merge_pc(1, 3);

    // ���ÿ��Ԫ�����ڵļ��ϵĸ��ڵ�
    for (int i = 1; i <= 10; ++i) {
        cout << "parent[" << i << "] = " << find_pc(i) << endl;
    }
}

void CommonSet() {
    // ��ʼ�����鼯
    for (int i = 1; i <= 10; ++i) {
        fa[i] = i;
    }

    // ��1��2�ϲ���ͬһ����
    merge_comm(1, 2);

    // ��3��4��5�ϲ���ͬһ����
    merge_comm(3, 4);
    merge_comm(4, 5);

    // ��1���ڼ��Ϻ�3���ڼ��Ϻϲ�
    merge_comm(1, 3);

    // ���ÿ��Ԫ�����ڵļ��ϵĸ��ڵ�
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
