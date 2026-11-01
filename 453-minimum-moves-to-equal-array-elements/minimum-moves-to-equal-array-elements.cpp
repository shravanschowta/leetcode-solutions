class Solution {
public:
    int minMoves(vector<int>& nums) {
        int min_element=nums[0];
        for(int num:nums){
            min_element=min(min_element,num);
        }
        int ans=0;
        for(int num:nums){
            ans+=num-min_element;
        }
        return ans;
    }
};