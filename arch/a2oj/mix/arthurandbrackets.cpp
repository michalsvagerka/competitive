#include "../../../l/lib.h"
// #include "../l/mod.h"

class arthurandbrackets {
public:

    void fill(const vector2<int>&V, string&S, int l, int i, int p) {
        if (l == 0) {
            S[p] = '(';
            S[p+1] = ')';
        } else if (V[l][i] == -1) {
            S[p] = '(';
            S[p+2*l+1] = ')';
            fill(V, S, l-1, i+1, p+1);
        } else {
            fill(V, S, V[l][i]-1, i, p);
            fill(V, S, l-V[l][i], i+V[l][i], p+2*V[l][i]);
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> P(N); cin >> P;
        vector2<int> D(N, N, 0);
        for (int i = 0; i < N; ++i) {
            D[0][i] = -(P[i].x == 1);
        }

        for (int l = 1; l < N; ++l) {
            for (int i = 0; i+l <= N; ++i) {
                if (D[l-1][i+1] && in(P[i].x, 2*l+1, P[i].y+1)) {
                    D[l][i] = -1;
                } else {
                    for (int g = 1; g <= l; ++g) {
                        if (D[g-1][i] && D[l-g][i+g]) {
                            D[l][i] = g;
                        }
                    }
                }
            }
        }

        if (D[N-1][0]) {
            string S(2*N, '.');
            fill(D, S, N-1, 0, 0);
            cout << S << '\n';
        } else {
            cout << "IMPOSSIBLE\n";
        }

    }
};
