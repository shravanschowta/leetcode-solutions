class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        // right[j] = maximum index in word1 from which word2[j...m-1] 
        // can be matched as an EXACT subsequence.
        vector<int> right(m + 1, -1);
        right[m] = n;

        int p = n - 1;
        for (int j = m - 1; j >= 0; --j) {
            while (p >= 0 && word1[p] != word2[j]) {
                p--;
            }
            right[j] = p;
            if (p >= 0) {
                p--;
            }
        }

        vector<int> ans;
        bool used_mismatch = false;
        int i = 0; // Pointer in word1

        for (int j = 0; j < m; ++j) {
            int chosen_i = -1;

            while (i < n) {
                bool is_match = (word1[i] == word2[j]);

                if (is_match) {
                    if (used_mismatch) {
                        // Must match remaining word2[j+1...] strictly
                        if (right[j + 1] > i) {
                            chosen_i = i;
                            break;
                        }
                    } else {
                        // We haven't used mismatch yet.
                        // Either remainder matches strictly (right[j+1] > i)
                        // OR we will use our 1 mismatch somewhere in word2[j+1...]
                        // We test if word2[j+1...] can be matched with 1 mismatch.
                        // To test this easily: if we match word2[j] exactly at i, 
                        // can the rest be formed? 
                        // It can be formed if right[j + 1] > i OR if we can greedily advance.
                        
                        // Actually, if we match word2[j] at i and keep used_mismatch = false,
                        // we just need to verify that a valid sequence exists starting after i.
                        // A valid suffix with 1 mismatch from j+1 exists if right[j+1] > i,
                        // OR if there exists some split point. 
                        // But greedily taking the match ALWAYS preserves maximum remaining options!
                        chosen_i = i;
                        break;
                    }
                } else {
                    // Try using our 1 allowed mismatch at position j
                    if (!used_mismatch && right[j + 1] > i) {
                        chosen_i = i;
                        used_mismatch = true;
                        break;
                    }
                }

                i++;
            }

            if (chosen_i == -1) {
                return {};
            }

            ans.push_back(chosen_i);
            i = chosen_i + 1; // Move past chosen index for next character
        }

        return ans;
    }
};