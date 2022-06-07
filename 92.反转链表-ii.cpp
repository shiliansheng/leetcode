/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] 反转链表 II
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *rth = new ListNode(-1), *zoom = rth, *pren = rth, *t;
        rth->next = head;
        int cnt = 1;
        for ( ; cnt < left; cnt++) {
            pren = pren->next;
        }
        // 此时找到待翻转的链表头
        zoom = pren->next;
        for ( ; cnt < right; cnt++) {
            t = zoom->next;
            zoom->next = t->next; // 把t结点从待翻转链表中取出来
            t->next = pren->next;
            pren->next = t;
        }
        return rth->next;
    }
};
// @lc code=end

