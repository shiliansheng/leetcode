// 排列算法

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 无序
void backtrackRec(vector<int> nodes, int limit, vector<int>& rec, vector<bool>& used, int idx) {
    if (rec.size() == limit) {
        for (auto i : rec)
            cout << i << " ";
        cout << endl;
        return;
    }
    for (int i = idx; i < nodes.size(); ++i) {
        if (used[i])
            continue;
        used[i] = true;
        rec.push_back(nodes[i]);
        backtrackRec(nodes, limit, rec, used, idx);
        used[i] = false;
        rec.pop_back();
    }
}

// 有序 重复
void backtrackOrderRepeat(vector<int> nodes, int limit, vector<int>& rec, int idx) {
    if (rec.size() == limit) {
        for (auto i : rec)
            cout << i << " ";
        cout << endl;
        return;
    }
    for (int i = idx; i < nodes.size(); ++i) {
        rec.push_back(nodes[i]);
        backtrackOrderRepeat(nodes, limit, rec, i);
        rec.pop_back();
    }
}

// 无序 重复
void backtrackDisorderRepeat(vector<int> nodes, int limit, vector<int>& rec) {
    if (rec.size() == limit) {
        for (auto i : rec)
            cout << i << " ";
        cout << endl;
        return;
    }
    for (int i = 0; i < nodes.size(); ++i) {
        rec.push_back(nodes[i]);
        backtrackDisorderRepeat(nodes, limit, rec);
        rec.pop_back();
    }
}

// 有序 不重复
void backtrackOrderNorepeat(vector<int> nodes, int limit, vector<int>& rec, int idx) {
    if (rec.size() == limit) {
        for (auto i : rec)
            cout << i << " ";
        cout << endl;
        return;
    }
    for (int i = idx; i < nodes.size(); ++i) {
        rec.push_back(nodes[i]);
        backtrackOrderNorepeat(nodes, limit, rec, i + 1);
        rec.pop_back();
    }
}

// 无序 不重复
void backtrackDisorderNorepeat(vector<int> nodes, int limit, vector<int>& rec, vector<bool> used) {
    if (rec.size() == limit) {
        for (auto i : rec)
            cout << i << " ";
        cout << endl;
        return;
    }
    for (int i = 0; i < nodes.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;
        rec.push_back(nodes[i]);
        backtrackDisorderNorepeat(nodes, limit, rec, used);
        used[i] = false;
        rec.pop_back();
    }
}

/*
1 2 3 / 3
1 1 1
1 1 2
1 1 3
1 2 2
...
3 3 3
== unknown
*/
void selectPermuteOrderRepeat(vector<int> nodes, int limit) {
    cout << endl
         << "select permute   order[1] repeat[1]:" << endl;
    cout << "limit    : " << limit << endl
         << "node list: ";

    for (auto& i : nodes) {
        cout << i << " ";
    }
    cout << endl;

    vector<int> rec;
    backtrackOrderRepeat(nodes, limit, rec, 0);
}

/*

1 2 3 4 / 3
1 2 3
1 2 4
1 3 4
2 3 4
==   /C limit
==  C
==   \C size

*/
void selectPermuteOrderNorepeat(vector<int> nodes, int limit) {
    cout << endl
         << "select permute   order[1] repeat[0]:" << endl;
    cout << "limit    : " << limit << endl
         << "node list: ";
    for (auto& i : nodes) {
        cout << i << " ";
    }
    if (limit > nodes.size()) {
        cout << "元素个数不支持 有序 不重复 排列：" << endl;
        return;
    }
    cout << endl;
    vector<int> rec;
    backtrackOrderNorepeat(nodes, limit, rec, 0);
}

/*
1 2 3 / 3
1 1 1
1 1 2
1 2 1
1 2 2
...
3 3 3
==      size
== limit
*/
void allPermuteDisorderRepeat(vector<int> nodes, int limit) {
    cout << endl
         << "all permute   order[0] repeat[1]:" << endl;
    cout << "limit    : " << limit << endl
         << "node list: ";
    for (auto& i : nodes) {
        cout << i << " ";
    }
    cout << endl;
    vector<int> rec;
    backtrackDisorderRepeat(nodes, limit, rec);
}

/*
1 2 3 / 3
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
==   /\   limit
==  /--\
== /    \ size

*/
void allPermuteDisorderNorepeat(vector<int> nodes, int limit) {
    cout << endl
         << "all permute   order[0] repeat[0]:" << endl;
    cout << "limit    : " << limit << endl
         << "node list: ";
    for (auto& i : nodes) {
        cout << i << " ";
    }
    cout << endl;

    if (limit > nodes.size()) {
        cout << "元素个数不支持 无序 不重复 排列：" << endl;
        return;
    }

    vector<int> rec;
    vector<bool> used(nodes.size(), false);
    backtrackDisorderNorepeat(nodes, limit, rec, used);
}

int main() {
    vector<int> nodes{1, 2, 3};
    int limit = 3;
    selectPermuteOrderRepeat({1, 2, 3}, 3);
    // selectPermuteOrderNorepeat({ 1, 2, 3, 4 }, 3);
    // allPermuteDisorderRepeat({ 1, 2, 3 }, 2);
    // allPermuteDisorderNorepeat({ 1, 2, 3 }, 2);
    return 0;
}