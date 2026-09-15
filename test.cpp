#include <bits/stdc++.h>
using namespace std;

// High-quality random number generator
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int getRandom(int l, int r) // Renamed to avoid shadowing std::rand
{
    return uniform_int_distribution<int>(l, r)(rng);
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int tests = 100;
    for (int test = 1; test <= tests; test++)
    {
        // 1. Use a distinct name for the file stream
        ofstream inp("hehe.inp");
        
        int n = getRandom(1, 100);
        inp << n << '\n'; 
        
        // 2. CRITICAL: Close the file so the executables can read the flushed data
        inp.close(); 

        // 3. Run the executables
        system("hehe.exe");
        system("bruteforce.exe");

        // 4. Compare outputs
        if (system("fc hehe.out bruteforce.out") == 1) // fc file compare
        {
            cout << "Output Files are different.";
            exit(0);
        }
    }

    
    return 0;
}
