class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if ((long long)num * 9 < sum) {
            return "";
        } 
        int k = sum / 9; 
        int s = sum % 9;        
        string ans = "";
        ans.append(k, '9');
        if (s > 0) {
            ans.push_back('0' + s);
        }
        ans.append(num - ans.size(), '0');
        return ans;
    }
};