class Solution {
public:
    int maxLength(vector<int>& nums) {
        int ans=1;
        int n=nums.size();
        for(int i=0;i<n;i++){
            long long product=1;
            long LCM=1;
            long long GCD=0;
            for(int j=i;j<n;j++){
                if (nums[j]<=0||product>LLONG_MAX/nums[j]){
                    break;
                }
                product*=nums[j];
                GCD=gcd(GCD,nums[j]);
                LCM=lcm(LCM,nums[j]);
                if(product==GCD*LCM){
                    ans=max(ans,j-i+1);
                }
            }
        }
        return ans;
    }
};