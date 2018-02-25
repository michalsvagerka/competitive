#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
    set<int> P;

    void primes(int a) {
        set<int> res;
        for (int i = 2; i < 100000; ++i) {
            if (a%i == 0) {
                P.insert(i);
                while (a%i == 0) a /= i;
            }
        }
        if (a != 1) {
            P.insert(a);
        }
    }
    
    void solve(istream& cin, ostream& cout) {
        int N;
        ll A, B; cin >> N >> A >> B;
        vector<int> R(N); cin >> R;
        primes(R[0]);
        primes(R[0]-1);
        primes(R[0]+1);
        primes(R[N-1]);
        primes(R[N-1]-1);
        primes(R[N-1]+1);


        ll ans = 1e16;
        for (int p: P) {
            vector<ll> D(N+1,1e16), E = D;
            E[N] = 0;

            for (int i = 0; i < N; ++i) {
                ll v = 1e16;
                if (R[i] % p == 0) {
                    v = 0;
                } else if (R[i] % p == p-1 || R[i] % p == 1) {
                    v = B;
                }
                if (i != 0) v += D[i-1];
                D[i] = min(D[i], v);
            }


            for (int i = N-1; i >= 0; --i) {
                ll v = 1e16;
                if (R[i] % p == 0) {
                    v = 0;
                } else if (R[i] % p == p-1 || R[i] % p == 1) {
                    v = B;
                }
                v += E[i+1];
                E[i] = min(E[i], v);
            }

            ll q = 0;
            for (int i = 0; i < N; ++i) {
                q = min(D[i], q + A);
                ans = min(ans, q + E[i+1]);
            }
        }

        cout << ans << endl;
    }
};
