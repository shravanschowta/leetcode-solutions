class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        bool found=false;
        for(int i=0;i<nums.size();i++)
        {
            for(int j=i+1;j<nums.size();j++)
            {
                if(nums[i]+nums[j]==target)
                {
                    bool found=true;
                    return {i,j};
                }
            }
        }
       return{};
    }
};
// int main()
// {
//     Solution s;
//     vector <int> nums={2,7,11,15};
//     int target=9;
//     vector<int>ans=s.twoSum(nums,target);
//     for(int i=0;i<2;i++)
//     {
//         cout<<ans[i];
//     }
//     return 0;

// }