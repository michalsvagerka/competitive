#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC optimize ("unroll-loops")
#include "../l/lib.h"


ll S[1050000];
int U[1050000];
class FHarryThePotter {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;

        vector<ll> A(N); cin >> A;
        for (int i = 0; i < (1<<N); ++i) {
            for (int j = 0; j < N; ++j) {
                if (i&1<<j) continue;
                S[i|1<<j] = S[i] + A[j];
            }
            U[i] = 100;
        }

        
        for (int i = 1; i < (1<<N); ++i) {
            int edg = __builtin_popcount(i) - 1;
            if (((S[i] + edg)&1) == 0) {
                ll lo = (S[i] - edg)/2;
                ll hi = (S[i] + edg)/2;
                for (int j = (i-1)&i; j; j = (j - 1) & i) {
                    if (S[j] >= lo && S[j] <= hi) {
                        U[i] = __builtin_popcount(i) - 1;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < N; ++i) U[1<<i] = A[i] != 0;
        for (int i = 1; i < (1<<N); ++i) {
            for (int j = i; j; j = (j - 1) & i) {
                U[i] = min(U[i], U[i^j] + U[j]);
            }
        }

        cout << U[(1<<N)-1] << '\n';
    }
};
