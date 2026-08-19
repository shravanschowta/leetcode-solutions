class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, vector<int>> rowToSeats;
        
        for (const auto& seat : reservedSeats) {
            rowToSeats[seat[0]].push_back(seat[1]);
        }

        int total = n * 2;

        for (const auto& [row, seats] : rowToSeats) {
            // Flags for reserved seats in this row
            bool s2 = false, s3 = false, s4 = false, s5 = false;
            bool s6 = false, s7 = false, s8 = false, s9 = false;

            // Mark seats that are taken
            for (int col : seats) {
                if (col == 2) s2 = true;
                if (col == 3) s3 = true;
                if (col == 4) s4 = true;
                if (col == 5) s5 = true;
                if (col == 6) s6 = true;
                if (col == 7) s7 = true;
                if (col == 8) s8 = true;
                if (col == 9) s9 = true;
            }

            // Check block availability
            bool left   = !s2 && !s3 && !s4 && !s5;
            bool middle = !s4 && !s5 && !s6 && !s7;
            bool right  = !s6 && !s7 && !s8 && !s9;

            if (left && right) {
                continue; // Fits 2 families
            } else if (left || right || middle) {
                total -= 1; // Fits 1 family
            } else {
                total -= 2; // Fits 0 families
            }
        }

        return total;
    }
};