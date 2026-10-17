class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        
        auto getDigitSum = [](int num) {
            int sum = 0;
            while (num > 0) {
                sum += num % 10;
                num /= 10;
            }
            return sum;
        };
        
        // Store pairs of {digit_sum, value}
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {getDigitSum(nums[i]), nums[i]};
        }
        
        // Sort based on digit sum first, then by value
        sort(arr.begin(), arr.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });
        
        // Map each unique value to its target index
        unordered_map<int, int> val_to_index;
        for (int i = 0; i < n; ++i) {
            val_to_index[arr[i].second] = i;
        }
        
        // Correct cycle decomposition counting self-loops (length 1 cycles)
        vector<bool> visited(n, false);
        int cycles = 0;
        
        for (int i = 0; i < n; ++i) {
            if (visited[i]) {
                continue;
            }
            
            // If the element is already in its correct position, it's a cycle of length 1
            if (val_to_index[nums[i]] == i) {
                visited[i] = true;
                cycles++;
                continue;
            }
            
            // Otherwise, traverse the multi-element cycle
            int curr = i;
            while (!visited[curr]) {
                visited[curr] = true;
                curr = val_to_index[nums[curr]];
            }
            cycles++;
        }
        
        return n - cycles;
    }
};