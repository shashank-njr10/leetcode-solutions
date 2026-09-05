class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        
        int peopleSize = people.size();
        int totalSkills = req_skills.size();
        int skillCombinations = 1 << totalSkills;

        unordered_map<string, int> skillToBitMap;

        for(int i = 0; i < totalSkills; i++) {
            skillToBitMap[req_skills[i]] = i;
        }


        vector<int> peopleSkillsToBit(peopleSize);
        for(int i = 0; i < peopleSize; i++) {
            
            for(auto string : people[i]) {
                peopleSkillsToBit[i] |= (1 << skillToBitMap[string]);
            }
        }

        vector<vector<int>> dp(skillCombinations);

        vector<int> isReachable(skillCombinations,false);

        isReachable[0] = true;

        //for every skill mask we have to check which set of people make the best team
        for(int currentSkillMask = 0; currentSkillMask < skillCombinations; currentSkillMask++) {

            if(!isReachable[currentSkillMask]) {
                continue;
            }

            for(int peopleIndex = 0; peopleIndex < peopleSize; peopleIndex++) {
                int newMask = currentSkillMask | peopleSkillsToBit[peopleIndex];

                if(newMask == currentSkillMask) {
                    continue; // did not add any new skill hence no point adding the person
                }

                if(!isReachable[newMask] || dp[currentSkillMask].size() +1 < dp[newMask].size()) {
                    dp[newMask] = dp[currentSkillMask];
                    dp[newMask].push_back(peopleIndex);
                    isReachable[newMask] = true;
                }
            }
        }

        return dp[skillCombinations - 1];
    }
};