int trailingZeroes(int n) {
    int m = 0;
    while (n > 1) {
        m += n / 5;
        n /= 5;
    }
    return m;
}
