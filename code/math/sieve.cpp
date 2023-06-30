// nao "otimizado"

vector<bool> sieve(int lim=1e5+17) {
    vector<bool> isprime(lim+1, true);

    isprime[0] = isprime[1] = false;
    
    for (int i = 2; i*i < lim; i++) {
        if (isprime[i]) {
            for (int j = i+i; j < lim; j += i) {
                isprime[j] = false;
            }
        }
    }

    return isprime;
}