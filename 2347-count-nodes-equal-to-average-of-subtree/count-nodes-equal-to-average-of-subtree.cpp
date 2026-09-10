/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    // Helper function that returns a pair containing: {sum_of_subtree, count_of_nodes}
    std::pair<int, int> dfs(TreeNode* root, int& count) {
        if (root == nullptr) {
            return {0, 0};
        }

        auto left = dfs(root->left, count);
        auto right = dfs(root->right, count);

        int current_sum = root->val + left.first + right.first;
        int current_count = 1 + left.second + right.second;

        // Check if the current node's value matches the average of its subtree
        if (current_sum / current_count == root->val) {
            count++;
        }

        return {current_sum, current_count};
    }

public:
    int averageOfSubtree(TreeNode* root) {
        int count = 0;
        dfs(root, count);
        return count;
    }
};