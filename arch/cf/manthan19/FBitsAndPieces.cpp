#include "../l/lib.h"

constexpr int L = 21;
constexpr int M = 1<<L;

class FBitsAndPieces {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> B(M, 0);
        int best = 0;
        for (int i = N-1; i >= 0; --i) {
            if (i+3 <= N) {
                int a = A[i], b = 0;
                for (int j = L - 1; j >= 0; --j) {
                    if (a&1<<j) continue;
                    b |= 1<<j;
                    if (B[b] < 2) b ^= 1<<j;
                }
                best = max(best, a|b);
            }


            B[A[i]]++;
//            cout << i << ' ' << A[i] << ' ' << B[A[i]] << endl;
            vector<int> P{A[i]};
            for (int j = 0; j < L; ++j) {
                if (A[i]&1<<j) {
                    int Q = P.size();
                    for (int k = 0; k < Q; ++k) {
                        int w = P[k]^1<<j;
                        if (B[w] < 2) {
                            B[w]++;

//                            cout << i << ' ' << w << ' ' << B[w] << endl;
                            P.push_back(w);
                        }
                    }
                }
            }
        }

        cout << best << endl;
    }
};
