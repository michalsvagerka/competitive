#include "../l/lib.h"

class EVladikAndCards {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        for (int &a: A) --a;
        vector3<int> Next(10,N+2, 8, N+1);
        for (int i = N-1; i >= 0; --i) {
            for (int j = 0; j < 8; ++j) {
                Next[0][i][j] = Next[0][i+1][j];
            }
            Next[0][i][A[i]] = i+1;
        }

        for (int l = 1; l < 10; ++l) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < 8; ++j) {
                    Next[l][i][j] = Next[l-1][Next[l-1][i][j]][j];
                }
            }
        }

        auto get = [&](int digit, int count, int from) {
            for (int i = 0; i < 10; ++i) {
                if (count&1<<i) {
                    from = Next[i][from][digit];
                }
            }
            return from;
        };

        int ans = 0;
        for (int lo = 0; lo <= N/8; ++lo) {
            vector2<int> D(256, 9, N+1);
            D[0][0] = 0;
            for (int i = 0; i < 255; ++i) {
                for (int e = 0; e <= 8; ++e) {
                    if (D[i][e] != N+1) {
                        for (int j = 0; j < 8; ++j) {
                            if (i&1<<j) continue;
                            D[i|1<<j][e] = min(D[i|1<<j][e], get(j, lo, D[i][e]));
                            D[i|1<<j][e+1] = min(D[i|1<<j][e+1], get(j, lo+1, D[i][e]));
                        }
                    }
                }
            }

            for (int i = 0; i <= 8; ++i) {
                if (D[255][i] != N+1) ans = 8*lo + i;
            }
        }
        cout << ans << endl;
    }
};
