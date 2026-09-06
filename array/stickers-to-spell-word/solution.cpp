class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        
        // Get the length of the target and calculate all possible bitmask combinations.
        // Each bit represents whether the corresponding target character is already covered.
        int targetSize = target.size();
        int targetCombinations = 1 << targetSize;

        // dp[mask] stores the minimum number of stickers required to reach this mask.
        // Initially, every state is unreachable, so we set them to INT_MAX.
        vector<int> dp(targetCombinations, INT_MAX);

        // With zero stickers, we have covered zero characters.
        // Therefore, the starting state is mask = 0 with cost 0.
        dp[0] = 0;

        // Iterate through every possible state of covered target characters.
        // We will try using every sticker from each reachable state.
        for(int mask = 0; mask < targetCombinations; mask++) {

            // If this state cannot be reached, there is no point processing it.
            // We only perform transitions from states that have a valid answer.
            if(dp[mask] == INT_MAX) {
                continue;
            }

            // Try using every sticker to cover currently uncovered target characters.
            // Each sticker can potentially take us from the current mask to a new mask.
            for(auto& sticker : stickers) {

                // Store the frequency of every character present in the current sticker.
                // This allows us to know how many times each character can be used.
                vector<int> freq(26, 0);

                // Count the occurrences of every character in the sticker.
                // For example, "abb" gives a = 1 and b = 2.
                for(int i = 0; i < sticker.size(); i++) {
                    freq[sticker[i] - 'a']++;
                }

                // Start with the current mask because this sticker should only add coverage.
                // newMask will represent all target characters covered after using this sticker.
                int newMask = mask;

                // Try to use the sticker to cover every currently uncovered target position.
                // We scan the target positions and greedily consume matching characters from the sticker.
                for(int i = 0; i < targetSize; i++) {

                    // If this bit is already set, this target character is already covered.
                    // Therefore, we do not need to use a character from the current sticker for it.
                    if(newMask & (1 << i)) {
                        continue;
                    }

                    // Get the character at the current target position.
                    // We need to check whether the current sticker contains this character.
                    char c = target[i];

                    // If the sticker has this character available, use one occurrence of it.
                    // Then mark this target position as covered by setting its corresponding bit.
                    if(freq[c - 'a'] > 0) {
                        freq[c - 'a']--;
                        newMask |= (1 << i);
                    }
                }

                // Using this sticker costs one additional sticker.
                // Update the minimum number of stickers needed to reach the new state.
                dp[newMask] = min(dp[newMask], dp[mask] + 1);
            }
        }

        // The final mask has every target position covered.
        // Return its minimum sticker count, or -1 if the target cannot be formed.
        return dp[targetCombinations - 1] == INT_MAX
            ? -1
            : dp[targetCombinations - 1];
    }
};