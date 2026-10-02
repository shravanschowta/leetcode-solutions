class Solution {
public:
    void helper(int n,int start,int end,string& curr,vector<string>& ans){
        if(curr.length()==2*n){
            ans.push_back(curr);
            return;
        }

        if(start<n){
            curr+='(';
            helper(n,start+1,end,curr,ans);
            curr.pop_back();
        }

        if(end<start){
            curr+=')';
            helper(n,start,end+1,curr,ans);
            curr.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string>ans;
        string curr="";
        helper(n,0,0,curr,ans);
        return ans;
    }
};