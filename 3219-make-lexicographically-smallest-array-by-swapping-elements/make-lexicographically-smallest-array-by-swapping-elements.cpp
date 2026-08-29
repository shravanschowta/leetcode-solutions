class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        
        // Pair each value with its original index
        vector<pair<int, int>> sortedNums(n);
        for (int i = 0; i < n; ++i) {
            sortedNums[i] = {nums[i], i};
        }
        
        // Sort pairs primarily by value
        sort(sortedNums.begin(), sortedNums.end());
        
        vector<int> result(n);
        int i = 0;
        
        while (i < n) {
            int j = i;
            // Expand group while adjacent elements satisfy the limit condition
            while (j + 1 < n && sortedNums[j + 1].first - sortedNums[j].first <= limit) {
                j++;
            }
            
            // Collect original indices for the current group
            vector<int> indices;
            for (int k = i; k <= j; ++k) {
                indices.push_back(sortedNums[k].second);
            }
            
            // Sort indices so smaller values go to earlier positions
            sort(indices.begin(), indices.end());
            
            // Place sorted values into sorted positions
            for (int k = 0; k < indices.size(); ++k) {
                result[indices[k]] = sortedNums[i + k].first;
            }
            
            // Move to next group
            i = j + 1;
        }
        
        return result;
    }
};