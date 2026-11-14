class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int size=0;
        int ans=INT_MAX;
        int sum=0;
        for(int i=0;i<nums.size();i++){
            sum=0;
            for(int j=i;j<nums.size();j++){
                sum+=nums[j];
                int len=j-i+1;
                if(len>=l && len<=r){
                    if(sum>0){
                        ans=min(sum,ans);
                    }
                }
                if(len>r){
                    break;
                }
            }
        }
        return (ans==INT_MAX?-1:ans);
    }
};