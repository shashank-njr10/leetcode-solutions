class Solution {
public:
    int numDistinct(string s, string t) {
        int sourceLength = s.size();
        int targetLength = t.size();

        vector<vector<long long>> dp(sourceLength+1,vector<long long>(targetLength+1,0));
        //number of distinct ways we can form substring t[j....] from s[i....]
        for(int i = 0; i <= sourceLength; i++) {
            dp[i][targetLength] = 1;
            //if target length is reached then doesnt matter how much of s[i...] we used
        }
        for(int j = 0; j < targetLength; j++) {
            dp[sourceLength][j] = 0;
            //if sourceLength is reached but target length isnt then we can never form target
        }

        for(int i = sourceLength - 1; i >=0 ; i--) {
            for(int j = targetLength - 1; j >=0 ; j--) {
                if(s[i] == t[j]) {

                    //check if adding the two values would exceed INT_MAX
                    if(dp[i+1][j+1] > INT_MAX - dp[i+1][j]) {
                        dp[i][j] = INT_MAX;
                    }
                    else {
                        dp[i][j] = dp[i+1][j+1] + dp[i+1][j];
                    }
                }
                else {
                    dp[i][j] = dp[i+1][j];
                }
            }
        }

        return dp[0][0];

    }
};