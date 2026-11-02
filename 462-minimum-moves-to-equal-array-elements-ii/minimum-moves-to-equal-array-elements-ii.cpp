class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int start=0;
        int ans=0;
        int end=nums.size()-1;
        while(start<end){
            ans+=nums[end]-nums[start];
            start++;
            end--;
        }
        return ans;
    }
};