class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        pair<int,int>max_num={INT_MIN,-1};
        pair<int,int>min_num={INT_MAX,-1};
        for(int i=0;i<nums.size();i++){
            if(nums[i]>max_num.first){
                max_num={nums[i],i};
            }
            if(nums[i]<min_num.first){
                min_num={nums[i],i};
            }
        }
        int n=nums.size();
        int ans;
        int j=max(max_num.second,min_num.second);
        int i=min(max_num.second,min_num.second);
        ans=min((n-j)+(i+1),j+1);
        ans=min(ans,n-i);
        return ans;
    }
};