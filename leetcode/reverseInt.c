int reverseInt(int x){
    long int newNum = 0;
    int res = 0;
    int signal = x < 0 ? -1 : 1;

    while (x != 0) {
        res = x % 10;
        x = (x - res) / 10;
        newNum *= 10;
        newNum += res;

        if (newNum > INT_MAX || newNum < INT_MIN) return 0;
    }
    

    return (int)newNum;
}