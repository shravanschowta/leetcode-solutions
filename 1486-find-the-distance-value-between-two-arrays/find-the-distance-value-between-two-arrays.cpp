class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int ans=0;
        bool change=true;
        sort(arr2.begin(),arr2.end());
        for(int i=0;i<arr1.size();i++){
            int start=0;
            int end=arr2.size()-1;
            change=true;
            while(start<=end){
                if(arr1[i]-arr2[start]<=d && arr1[i]-arr2[start]>=(-1)*d){
                    start++;
                    change=false;
                    break;
                }
                start++;
            }
            if(change==true){
                ans+=1;
            }
        }
        return ans;
    }
};