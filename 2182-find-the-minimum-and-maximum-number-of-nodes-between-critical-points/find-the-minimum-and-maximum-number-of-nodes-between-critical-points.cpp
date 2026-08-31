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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        ListNode* prev = head;
        ListNode* curr = head->next;
        ListNode* next_node = curr->next;

        int first_cp = -1;
        int prev_cp = -1;
        int min_dist = INT_MAX;
        int index = 1;
        while (next_node != nullptr) {
            bool is_local_max = (curr->val > prev->val && curr->val > next_node->val);
            bool is_local_min = (curr->val < prev->val && curr->val < next_node->val);

            if (is_local_max || is_local_min) {
                if (first_cp == -1) {
                    first_cp = index;
                } else {
                    min_dist = min(min_dist, index - prev_cp);
                }
                prev_cp = index;
            }
            prev = curr;
            curr = next_node;
            next_node = next_node->next;
            index++;
        }
        if (first_cp == -1 || prev_cp == first_cp) {
            return {-1, -1};
        }
        int max_dist = prev_cp - first_cp;
        return {min_dist, max_dist};
    }
};