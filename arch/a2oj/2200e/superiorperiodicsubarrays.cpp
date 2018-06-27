#include "../../../l/lib.h"
// #include "../l/mod.h"

class superiorperiodicsubarrays {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        ll ans = 0;
        vector<int> A(N, 1);
        cin >> A;


        vector<bool> R(2*N);
        for (int s = 1; s < N; ++s) {
            if (N%s) continue;
            for (int i = 0; i < s; ++i) {
                int m = A[i];
                for (int j = i+s; j < N; j+=s) m = max(m, A[j]);
                for (int j = i; j < N; j+=s) R[j+N] = R[j] = A[j] >= m;
            }

            vector<int> CP(N/s+1, 0);
            CP[1] = 1;
            for (int i = 2; i <= N/s; ++i) CP[i] = CP[i-1] + (gcd(N/s,i) == 1);


            int e = 0;
            for (int b = 0; b < N; ++b) {
                if (e < b) e++;
                while (e < b+N && R[e]) ++e;
                int l = e-b;
                ans += CP[l/s];
            }
        }
        cout << ans << '\n';

    }
};
