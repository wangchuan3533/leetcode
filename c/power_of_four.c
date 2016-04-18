bool isPowerOfFour(int num) {
    return (num > 0) && ((num & 0xaaaaaaaa) == 0) && (((num - 1) & num) == 0);
}
