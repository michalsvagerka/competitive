#include "../../../l/lib.h"
#include "../../../l/mod.h"
#include "../../../l/bigint.h"
#include "../../../l/suffixarray.h"

class dreamoonandbinary {
public:
    void solve(istream& cin, ostream& cout) {
        string S;
        cin >> S;
        int N = S.size();
        S += '$';
        SuffixArray<int, true, true> SA(S);
        vector<vector<FieldMod>> E(N+1);
        vector<vector<int>> M(N+1);
        for (int e = 1; e <= N; ++e) {
            E[e] = vector<FieldMod>(e+1, 0);
            E[e][0] = 1;

            M[e] = vector<int>(e+1,1e9);
            M[e][0] = 1;

            for (int b = 1; b < e; ++b) {
                if (S[b] == '0') {
                    E[e][b] = E[e][b - 1];
                    continue;
                }

                FieldMod x = 0;
                int l = e - b;
                int origin = b - l;
                int lo = max(origin + 1, 0), hi = b - 1;
                if (origin >= 0) {
                    int lcp = SA.lcp(origin, b);
                    if (lcp >= l) --lo;
                    else if (S[origin + lcp] < S[b + lcp]) --lo;
                }

                x += E[b][hi];
                if (lo) x -= E[b][lo - 1];
                E[e][b] = E[e][b - 1] + x;
                if (lo <= hi) M[e][b] = min(M[e][b], M[b][lo] + 1);
            }

            for (int b = e-2; b >= 1; --b) { M[e][b] = min(M[e][b], M[e][b+1]);  }
        }

        cout << E[N][N - 1] << endl;

        Num X = 0;
        int hi = N;
        for (int l = 0; l <= hi; ++l) {
            if (M[N][N-l] != 1e9) {
                Num Z{S.substr(N-l,l), 2};
                Z += Num{ll(M[N][N-l])};
                if (X == 0) {
                    swap(X,Z);
                    hi = min(N, max(20, l+1));
                } else if (X > Z) {
                    swap(X, Z);
                }
            }
        }
        cout << (X % Num{ll(1000000007)}).to_longlong() << endl;
    }
};
