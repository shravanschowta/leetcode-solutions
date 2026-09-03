class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        sort(nums1.begin(),nums1.end());
        int n=nums1.size();
        int rem=nums1[0]%2;
        int same=0;
        int other=0;
        for(int i=0;i<n;i++){
            if(nums1[i]%2!=rem && rem==0){
                if(other<1){
                    return false;
                }
                other++;
            }
            else if(nums1[i]%2!=rem && rem==1){
                if(same<1){
                    return false;
                }
                other++;
            }
            else{
                same++;
            }
        }
        return true;
    }
};