class Solution {
public:
    string reverseParentheses(string s) {
        stack<int> st;
        string result = "";
        
        for (char c : s) {
            if (c == '(') {
                // Push the current length of the result to the stack
                st.push(result.length());
            } else if (c == ')') {
                // Pop the starting index for the substring to reverse
                int start = st.top();
                st.pop();
                // Reverse the substring between the matching parentheses
                reverse(result.begin() + start, result.end());
            } else {
                // Append normal characters to the result
                result += c;
            }
        }
        
        return result;
    }
};