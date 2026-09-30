for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + a[i][j]; // row i, column j
        }
    }

int sumRegion(int a, int b, int A, int B) {
        return prefix[A][B] 
             - prefix[a - 1][B] 
             - prefix[A][b - 1] 
             + prefix[a - 1][b - 1];
    }
