class Solution {
    int numOfDays(string date) {
        // Convert characters to integers directly using ASCII values
        int month = (date[0] - '0') * 10 + (date[1] - '0');
        int day = (date[3] - '0') * 10 + (date[4] - '0');
        
        int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        for (int i = 1; i < month; ++i) day += days[i];
        return day;
    }

public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int start = max(numOfDays(arriveAlice), numOfDays(arriveBob));
        int end = min(numOfDays(leaveAlice), numOfDays(leaveBob));
        return max(0, end - start + 1);
    }
};