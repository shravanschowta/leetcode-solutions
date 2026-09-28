class Solution {
public:
    int maxDepth(string s) {
        int curr_size=0;
        int ans=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                curr_size++;
            }
            else if(s[i]==')'){
                curr_size--;
            }
            ans=max(ans,curr_size);
        }
        return ans;
    }
};