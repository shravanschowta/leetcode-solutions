class Solution {
public:
    void helper(string &s,int k){
        string ans="";
        int size=0;
        int sum=0;
        for(char i:s){
            size++;
            sum+=i-'0';
            if(size==k){
                ans+=to_string(sum);
                sum=0;
                size=0;
            }
        }
        if(size>0){
            ans+=to_string(sum);
        }
        s=ans;
    }
    string digitSum(string s, int k) {
        while(s.size()>k){
            helper(s,k);
        }
        return s;
    }
};