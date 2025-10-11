int fib(int n, int * fibs) {
    if (n == 0 || n == 1) return 1;
    if (!fibs[n]) fibs[n] = fib(n-1, fibs) + fib(n-2, fibs);
    return fibs[n-1];
}

int climbStairs(int n) {
    int fibs[n];
    for (int i = 0; i < n; i++) fibs[i] = 0;

    int stairs = fib(n, fibs);
    return stairs;
}