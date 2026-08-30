class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0;
        int cnt = 0;
        int res = 0;
        unordered_map<char,int> mpp;
        for(int right = 0; right < s.size(); right++) {
            mpp[s[right]]++;

            while(mpp[s[right]] > 1) {
                mpp[s[left]]--;
                left++;
            }

            res = max(res, right - left + 1);
        }
        return res;
    }
};