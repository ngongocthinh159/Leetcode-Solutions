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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* p = head;
        ListNode* prev = dummy;
        unordered_set<int> S;
        for (auto x : nums) S.insert(x);
        while (p != nullptr) {
            auto nxt = p->next;
            if (S.count(p->val)) {
                prev->next = nxt;
            } else
                prev = p;
            p = p->next;
        }
        return dummy->next;
    }
};