class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int temp=nums[0];
        int ans=1;
        int final_ans=0;
        bool increasing=true;
        for(int i=1;i<nums.size();i++){
            if(nums[i]>temp && increasing){
                ans+=1;
            }
            else if(nums[i]>temp && !increasing){
                final_ans=max(final_ans,ans);
                ans=2;
                increasing=true;
            }
            else if(nums[i]<temp && !increasing){
                ans+=1;
            }
            else if(nums[i]<temp && increasing){
                final_ans=max(final_ans,ans);
                ans=2;
                increasing=false;
            }
            else{
                final_ans=max(final_ans,ans);
                ans=1;
            }
            temp=nums[i];
        }
        final_ans=max(final_ans,ans);
        return final_ans;
    }
};