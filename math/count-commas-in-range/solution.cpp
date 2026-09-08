class Solution {
public:
    int countCommas(int n) {
        if(n < 1000){
            return 0;
        }
        if(n >= 1000 and n <= 9999) {
            return n - 1000 + 1;
        }
        if(n >= 10000 and n <= 1e5) {
            return n - 1000 + 1;
        }

        return 0;
    }
};