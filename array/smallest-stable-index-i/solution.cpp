class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        int max_array[n];
        int min_array[n];
        max_array[0] = nums[0];
        min_array[n-1] = nums[n-1];

        int curr_max = nums[0];
        for(int i = 1; i < n; i++) {
            curr_max = max(curr_max,nums[i]);
            max_array[i] = curr_max;
        }

        int curr_min = nums[n-1];
        for(int i = n-2; i >= 0; i--) {
            curr_min = min(curr_min,nums[i]);
            min_array[i] = curr_min;
        }

        for(int i = 0; i< n; i++) {
            if(max_array[i] - min_array[i] <= k){
                return i;
            }
        }
        return -1;
    }
};