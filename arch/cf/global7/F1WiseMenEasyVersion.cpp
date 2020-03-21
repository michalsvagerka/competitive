#include "../l/lib.h"

class F1WiseMenEasyVersion {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<string> P(N); cin >> P;

        int a = (N-1)/2;
        int b = N-1-a;
        vector<vector<vector<int>>> L(1<<N);
        for (int i = 0; i < (1<<N); ++i) {
            if (__builtin_popcount(i) <= b+1) {
                L[i] = vector2<int>(N, 1<<b, 0);
            }
        }

        for (int i = 0; i < N; ++i) L[1<<i][i][0] = 1;
        for (int j = 0; j < (1<<N); ++j) {
            int z = __builtin_popcount(j);
            if (z > b) continue;
            for (int i = 0; i < N; ++i) {
                for (int l = 0; l < 1<<(z-1); ++l) {
                    if (L[j][i][l] == 0) continue;
                    for (int k = 0; k < N; ++k) {
                        if (j&1<<k) continue;
                        L[j|1<<k][k][(l<<1)|(P[i][k]-'0')] += L[j][i][l];
                    }
                }
            }
        }


        vector<ll> Ans(1<<(N-1), 0);
        for (int i = 0; i < (1<<N); ++i) {
            if (__builtin_popcount(i) == a+1) {
                for (int c = 0; c < N; ++c) {
                    int ni = i^((1<<N)-1)^1<<c;
                    for (int l = 0; l < (1<<a); ++l) {
                        if (L[i][c][l] == 0) continue;
                        int g = 0;
                        for (int z = 0; z < a; ++z) {
                            if (l&1<<z) g |= 1<<(a-z-1);
                        }
                        for (int r = 0; r < (1<<b); ++r) {
                            Ans[g|r<<a] += ll(L[i][c][l]) * L[ni][c][r];
                        }
                    }
                }
            }
        }

        cout << Ans;
    }
};
