// ���鼯 - ·���Ż�

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000;

vector<int> parent(MAXN, -1);  // ��ʼ��ÿ��Ԫ�ض���һ�������ļ���

int find(int x) {  // ����Ԫ��x���ڼ��ϵĸ��ڵ�
    // ��ǰ���Ϊ�����(<-1)����Ϊ�������(-1)
    if (parent[x] < 0) {  // abs(parent[x]) Ϊ�Ե�ǰ���Ϊ���������Ľ�����
        return x;
    }
    return parent[x] = find(parent[x]);  // ·��ѹ��
}

void merge(int x, int y) {  // �ϲ�Ԫ��x��y���ڵļ���
    int root1 = find(x);
    int root2 = find(y);
    if (root1 != root2) {
        // ��С���Ϻϲ����󼯺���
        if (parent[root1] < parent[root2]) {  // �����ԽС�Ľ�����ڵ�����������Խ�࣬������Խ��
            parent[root1] += parent[root2];
            parent[root2] = root1;
        } else {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
    }
}

int main() {
    // ��ʼ�����鼯
    for (int i = 1; i <= 10; ++i) {
        parent[i] = -1;
    }

    // ��1��2�ϲ���ͬһ����
    merge(1, 2);

    // ��3��4��5�ϲ���ͬһ����
    merge(3, 4);
    merge(4, 5);

    // ��1���ڼ��Ϻ�3���ڼ��Ϻϲ�
    merge(1, 3);

    // ���ÿ��Ԫ�����ڵļ��ϵĸ��ڵ�
    for (int i = 1; i <= 10; ++i) {
        cout << "parent[" << i << "] = " << find(i) << endl;
    }

    return 0;
}
