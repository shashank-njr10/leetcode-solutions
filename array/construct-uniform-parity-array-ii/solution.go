func uniformArray(nums1 []int) bool {
    min := slices.Min(nums1)

    if min%2 != 0 {
        return true
    } else {
        for _, val := range nums1 {
            if val%2 != 0 {
                return false
            }
        }
    }

    return true
}