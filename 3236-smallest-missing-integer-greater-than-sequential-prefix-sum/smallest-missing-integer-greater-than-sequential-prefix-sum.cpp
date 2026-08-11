class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int prev=nums[0];
        int current;
        int sum=nums[0];
        int i;
        for(i=1;i<nums.size();i++){
            current=nums[i];
            if(current==prev+1){
                sum+=nums[i];
            }
            else{
                break;
            }
            prev=current;
        }
        sort(nums.begin(),nums.end());
        for(int j=0;j<nums.size();j++){
            if(nums[j]>sum){
                return sum;
            }
            if(nums[j]==sum){
                sum+=1;
            }
        }
        return sum;
    }
};