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
    int pairSum(ListNode* head) {
        int len = 0;
        ListNode* p = head;
        while (p != nullptr) {
            len++;
            p = p->next;
        }
        p = head; 
        for (int i = 1; i <= len/2; i++) p = p->next;
        ListNode* prev = nullptr;
        while (p != nullptr) {
            ListNode* nxt = p->next;
            p->next = prev;
            prev = p;
            p = nxt;
        }
        ListNode* l = head;
        ListNode* r = prev;
        int ans = -1;
        for (int i = 1; i <= len/2; i++) {
            ans = max(ans, l->val + r->val);
            l = l->next;
            r = r->next;
        }
        return ans;
    }
};