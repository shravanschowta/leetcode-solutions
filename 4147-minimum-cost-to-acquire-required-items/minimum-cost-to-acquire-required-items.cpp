class Solution {
public:
    long long minimumCost(int cost1,int cost2,int costBoth,int need1,int need2){
        if(costBoth>=cost1+cost2){
            return (long long)need1*cost1+(long long)need2*cost2;
        }
        long long common=min(need1,need2);
        long long totalCost=common*costBoth;
        need1-=common;
        need2-=common;
        if (need1>0) {
            totalCost+=min((long long)need1*cost1,(long long)need1*costBoth);
        }else if(need2>0){
            totalCost+=min((long long)need2*cost2, (long long)need2*costBoth);
        }
        
        return totalCost;
    }
};