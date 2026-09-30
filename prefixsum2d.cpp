for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + a[i][j]; // row i, column j
        }
    }

int sumRegion(int a, int A, int b, int B) 
{
    return pref[A][B] - pref[a - 1][B] - pref[A][b - 1] + pref[a - 1][b - 1]; //row a -> A, column b -> B (inclusive)
}
