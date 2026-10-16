#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    const long long MOD = 1e9 + 7;
    
    struct Node {
        long long sum = 0;
        long long sum_sq = 0;
        long long lazy = 0;
    };
    
    vector<Node> tree;
    
    void push(int node, int l, int r) {
        if (tree[node].lazy != 0) {
            long long v = tree[node].lazy;
            int mid = l + (r - l) / 2;
            
            // Left child
            long long len1 = mid - l + 1;
            tree[2 * node].sum_sq = (tree[2 * node].sum_sq + 2 * v * tree[2 * node].sum + v * v % MOD * len1) % MOD;
            tree[2 * node].sum = (tree[2 * node].sum + v * len1) % MOD;
            tree[2 * node].lazy = (tree[2 * node].lazy + v) % MOD;
            
            // Right child
            long long len2 = r - mid;
            tree[2 * node + 1].sum_sq = (tree[2 * node + 1].sum_sq + 2 * v * tree[2 * node + 1].sum + v * v % MOD * len2) % MOD;
            tree[2 * node + 1].sum = (tree[2 * node + 1].sum + v * len2) % MOD;
            tree[2 * node + 1].lazy = (tree[2 * node + 1].lazy + v) % MOD;
            
            tree[node].lazy = 0;
        }
    }
    
    void update(int node, int l, int r, int ql, int qr, long long val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            long long len = r - l + 1;
            tree[node].sum_sq = (tree[node].sum_sq + 2 * val * tree[node].sum + val * val % MOD * len) % MOD;
            tree[node].sum = (tree[node].sum + val * len) % MOD;
            tree[node].lazy = (tree[node].lazy + val) % MOD;
            return;
        }
        push(node, l, r);
        int mid = l + (r - l) / 2;
        update(2 * node, l, mid, ql, qr, val);
        update(2 * node + 1, mid + 1, r, ql, qr, val);
        
        tree[node].sum = (tree[2 * node].sum + tree[2 * node + 1].sum) % MOD;
        tree[node].sum_sq = (tree[2 * node].sum_sq + tree[2 * node + 1].sum_sq) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        tree.assign(4 * n, Node());
        
        unordered_map<int, int> last_pos;
        long long total_ans = 0;
        
        for (int j = 0; j < n; ++j) {
            int prev = -1;
            if (last_pos.find(nums[j]) != last_pos.end()) {
                prev = last_pos[nums[j]];
            }
            last_pos[nums[j]] = j;
            
            int L = prev + 1;
            int R = j;
            
            // Increment the distinct count for all subarrays starting from L to R ending at j
            update(1, 0, n - 1, L, R, 1);
            
            // Add the sum of squares of all subarrays ending at index j
            total_ans = (total_ans + tree[1].sum_sq) % MOD;
        }
        
        return total_ans;
    }
};