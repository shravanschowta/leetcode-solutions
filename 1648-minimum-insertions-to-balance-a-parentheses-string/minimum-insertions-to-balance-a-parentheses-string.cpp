class Solution {
public:
    int minInsertions(string s) {
        int neededRight = 0; // Number of ')' needed (each '(' expects 2 ')' )
        int missingLeft = 0; // Number of '(' insertions needed for stray ')'
        int missingRight = 0; // Number of ')' insertions needed if '(' expects an odd count

        for (char c : s) {
            if (c == '(') {
                // If we have an odd expectation of ')' and encounter '(', 
                // we need to insert a ')' right here to satisfy the previous expectation.
                if (neededRight % 2 == 1) {
                    missingRight++;
                    neededRight--;
                }
                neededRight += 2; // Each '(' requires two ')' characters
            } else { // c == ')'
                neededRight--;
                // If neededRight drops below 0, it means we found a ')' 
                // without an opening '(', so we need to insert a '('
                if (neededRight < 0) {
                    missingLeft++;
                    neededRight += 2; // Reset expectation for that newly assumed '('
                }
            }
        }

        // Total insertions = missing left '(' + missing right ')' + remaining unmatched ')' needs
        return neededRight + missingLeft + missingRight;
    }
};