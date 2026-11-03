class Solution {
public:
    int minMoves(vector<int>& nums) {
        int maxx=INT_MIN;
        for(int i=0;i<nums.size();i++){
            maxx=max(maxx,nums[i]);
        }
        int ans=0;
        for(int i=0;i<nums.size();i++){
            ans+=maxx-nums[i];
        }
        return ans;
    }
};