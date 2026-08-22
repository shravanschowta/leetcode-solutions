class Solution {
public:
    bool checkDivisibility(int n) {
        int sum=0;
        int product=1;
        int temp=n;
        while(temp>0){
            int rem=temp%10;
            temp=temp/10;
            product*=rem;
            sum+=rem;
        }
        if(n%(sum+product)==0) return true ;
        else return false;
    }
};