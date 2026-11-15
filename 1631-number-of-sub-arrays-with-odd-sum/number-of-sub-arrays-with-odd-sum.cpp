class Solution {
public:
    int numOfSubarrays(vector<int>& arr){
        long long oddCount = 0;
        long long evenCount = 0;
        long long totalOdd = 0;
        int MOD=1e9+7; 
        for(int num:arr){
            if(num%2!=0){
                long long temp=evenCount;
                evenCount=oddCount;
                oddCount=temp+1;
            }else{
                evenCount=evenCount+1;
            }   
            totalOdd=(totalOdd+oddCount)%MOD;
        }
        return totalOdd;
    }
};