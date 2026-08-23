class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int leftSum = 0, rightSum = 0;
        int leftQ = 0, rightQ = 0;

        // Step 1: Count initial sums and '?' marks for both halves
        for (int i = 0; i < n / 2; ++i) {
            if (num[i] == '?') leftQ++;
            else leftSum += num[i] - '0';
        }

        for (int i = n / 2; i < n; ++i) {
            if (num[i] == '?') rightQ++;
            else rightSum += num[i] - '0';
        }

        // Step 2: If total '?' is odd, Alice always wins
        if ((leftQ + rightQ) % 2 != 0) {
            return true;
        }

        // Step 3: Check if Bob can balance the sums
        // Bob wins (returns false) if the remaining delta offsets the sum difference.
        return (leftSum - rightSum) + (leftQ - rightQ) * 9 / 2 != 0;
    }
};