class Solution {
public:
    int scoreOfParentheses(std::string s) {
        stack<int> st;
        st.push(0); // Initialize with a base score for the outer level

        for (char c : s) {
            if (c == '(') {
                st.push(0); // Entering a new nested level, start with 0
            } else {
                int innerScore = st.top();
                st.pop();
                
                // If innerScore is 0, it means we had "()", which scores 1.
                // Otherwise, we had "(A)", which doubles the inner score `A`.
                int currentScore = (innerScore == 0) ? 1 : 2 * innerScore;
                
                // Add the score to the parent level
                int outerScore = st.top();
                st.pop();
                st.push(outerScore + currentScore);
            }
        }

        return st.top();
    }
};