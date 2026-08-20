class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        int n=nums.size();
        int p1=0;
        int p2=n-1;
        vector<int>result(n);
        result[0]=nums[0];
        result[n-1]=nums[1];
        for(int i=2;i<n;i++){
            if(result[p1]>result[p2]){
                result[++p1]=nums[i];
            }
            else{
                result[--p2]=nums[i];
            }
        }
        reverse(result.begin()+p2,result.end());
        return result;
    }
};