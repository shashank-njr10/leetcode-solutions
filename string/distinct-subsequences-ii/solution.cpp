class Solution {
public:
    int mod = 1e9 + 7;

    int distinctSubseqII(string s) {
        int n = s.size();

        vector<int> dp(n + 1, 0);
        // dp[i] = distinct subsequences that can be formed
        // from the first i characters, i.e. indices 0 to i - 1

        dp[0] = 1;
        // We need 0 characters to create the empty subsequence

        vector<int> last(26, -1);
        // last[c] = previous DP position where character c appeared

        for(int i = 1; i <= n; i++) {

            char c = s[i - 1];

            if(last[c - 'a'] == -1) {
                dp[i] = (2LL * dp[i - 1]) % mod;

                // First occurrence, so no duplicates are created
                last[c - 'a'] = i;
            }
            else {
                dp[i] = ((2LL * dp[i - 1]) % mod
                        - dp[last[c - 'a'] - 1] + mod) % mod;

                // Only subsequences formed before the previous
                // occurrence of this character are duplicated

                last[c - 'a'] = i;
            }
        }

        return (dp[n] - 1 + mod) % mod;
        // Remove the empty subsequence
    }
};