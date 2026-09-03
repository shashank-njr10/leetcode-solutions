class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        //find the smallest element
        int mini = *min_element(nums1.begin(),nums1.end());

        //if the smallest element's parity is odd then we can always construct nums2
        if(mini % 2) {
            return true;
        }
        else {
            //if parity is even then all elements must be even
            for(int i = 0; i < nums1.size(); i++) {
                if(nums1[i] % 2) {
                    return false;
                }
            }
        }
        return true;
    }
};