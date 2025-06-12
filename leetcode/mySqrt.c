int mySqrt(int x) {
    if (x == 0 || x == 1) return x;

    int start = 1, end = x;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        long long sqr = (long long) mid * mid;
        if (sqr == x) return mid;
        if (sqr > x) {
            if (start == end) return mid - 1;
            end = mid;
        }
        else {
            if (start == end) return mid + 1;
            start = mid + 1;
        }
    }

    return -1;
}