const int maxn = 1000000 + 5; //10^6 + 5
bool is_prime[maxn];
void Eratosthenes(int n) {
    for (int i = 2; i <= n; i++)
        is_prime[i] = true;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            // j sẽ bắt đầu chạy từ i * i
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}
