class Solution {
public:
    vector<int> smallestSufficientTeam(
        vector<string>& req_skills,
        vector<vector<string>>& people
    ) {

        // Store the number of people and the number of skills we need.
        // We use these values to determine the size of our DP state space.
        int peopleSize = people.size();
        int totalSkills = req_skills.size();

        // Each skill can either be present or absent, giving 2^totalSkills combinations.
        // Each combination is represented by a unique bitmask.
        int skillCombinations = 1 << totalSkills;


        // Map every required skill to a unique bit position.
        // This allows us to represent a person's skills using a single integer.
        unordered_map<string, int> skillToBitMap;

        for(int i = 0; i < totalSkills; i++) {
            skillToBitMap[req_skills[i]] = i;
        }


        // Convert the skills of every person into a bitmask.
        // Each set bit in the mask represents a skill that the person has.
        vector<int> peopleSkillsToBit(peopleSize);

        for(int i = 0; i < peopleSize; i++) {

            // Go through every skill that the current person possesses.
            // Convert that skill into its corresponding bit and add it to the person's mask.
            for(auto string : people[i]) {
                peopleSkillsToBit[i] |= (1 << skillToBitMap[string]);
            }
        }


        // dp[mask] stores the smallest team of people that can provide the skills in mask.
        // The vector contains the indices of the people belonging to that team.
        vector<vector<int>> dp(skillCombinations);


        // Track whether we have found any valid team for a particular skill mask.
        // This is needed because an empty vector can represent either an unreachable state or the valid empty team.
        vector<int> isReachable(skillCombinations, false);


        // Mask 0 represents having no skills, which is possible with an empty team.
        // Therefore, mask 0 is our starting state for the DP.
        isReachable[0] = true;


        // Go through every possible set of skills that we can currently have.
        // For each skill set, try adding every person to see if we can improve the team.
        for(int currentSkillMask = 0;
            currentSkillMask < skillCombinations;
            currentSkillMask++) {

            // If no team can produce this skill mask, there is nothing to build from.
            // Therefore, skip this state and move to the next one.
            if(!isReachable[currentSkillMask]) {
                continue;
            }


            // Try adding every person to the team represented by currentSkillMask.
            // This lets us find the best possible team for every new skill combination.
            for(int peopleIndex = 0;
                peopleIndex < peopleSize;
                peopleIndex++) {

                // Combine the skills we already have with the skills of this person.
                // Bitwise OR keeps every skill that either the current team or the person has.
                int newMask =
                    currentSkillMask | peopleSkillsToBit[peopleIndex];


                // If the person does not provide any new skill, adding them is unnecessary.
                // Keeping the current team is always better than adding an extra person.
                if(newMask == currentSkillMask) {
                    continue;
                }


                // Check whether this is the first team that reaches newMask or a smaller team than the existing one.
                // If the candidate team is better, replace the existing team for this skill combination.
                if(!isReachable[newMask] ||
                   dp[currentSkillMask].size() + 1 < dp[newMask].size()) {

                    // Start with the team that produced the current skill mask.
                    // Then add the current person to create the candidate team.
                    dp[newMask] = dp[currentSkillMask];
                    dp[newMask].push_back(peopleIndex);


                    // Mark this new skill combination as reachable.
                    // Future DP states can now use this team to obtain additional skills.
                    isReachable[newMask] = true;
                }
            }
        }


        // skillCombinations - 1 has every skill bit set to 1.
        // Therefore, its DP entry contains the smallest team that has all required skills.
        return dp[skillCombinations - 1];
    }
};