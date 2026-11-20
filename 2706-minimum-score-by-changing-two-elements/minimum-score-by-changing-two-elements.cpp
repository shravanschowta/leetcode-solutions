class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        int dif_mid;
        int sum=0;
        int dif_start=0;
        int dif_end=0;
        int n=nums.size();
        if(n<=3){
            return 0;
        }
        sort(nums.begin(),nums.end());
        dif_start=nums[n-1]-nums[2];
        dif_end=nums[n-3]-nums[0];
        dif_mid=nums[n-2]-nums[1];
        sum=min(dif_end,dif_start);
        sum=min(sum,dif_mid);
        return sum;
    }
};