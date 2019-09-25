#include "../l/lib.h"
#include "../l/random.h"

constexpr ll S = 10000000000LL;

class Zillionim {
public:
    void solve(istream& cin, ostream& cout) {
        int T, W; cin >> T >> W;
        for (int t = 0; t < T; ++t) {
            vector<ll> M{-S+1, 100*S+1};
            random_ll RR{0LL, S-3};
            while (true) {
                ll P; cin >> P;
                if (P == -1) return;
                if (P == -2 || P == -3) break;

                M.push_back(P);
                sort(M.begin(),M.end());
                vector<int> A, B, C;
                for (int i = 1; i < M.size(); ++i) {
                    ll D = M[i] - M[i-1];
                    if (D >= 4*S-1) {
                        C.push_back(i-1);
                    } else if (D >= 3*S) {
                        B.push_back(i-1);
                    } else if (D >= 2*S) {
                        A.push_back(i-1);
                    }
                }

                ll m;
                if (!C.empty()) {
                    m = M[C[random_int{0,(int)C.size()-1}(rng)]] + 3*S;
                } else if (B.size() > 1) {
                    if (!A.empty()) {
                        m = M[A[0]] + S;
                    } else if (B.size() % 2 == 1) {
                        m = M[B[0]]+2*S-1;
                    } else {
                        m = M[B[0]]+S;
                    }
                } else if (B.size() == 1) {
                    if (A.size() % 2 == 1) {
                        m = M[B[0]]+S;
                    } else {
                        m = M[B[0]]+2*S-1;
                    }
                } else {
                    m = M[A[0]] + S;
                }

                M.push_back(m);
                cout << m << endl;

            }
        }
    }
};
