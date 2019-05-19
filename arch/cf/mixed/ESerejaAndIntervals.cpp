#include "../l/lib.h"
#include "../l/mod.h"

class ESerejaAndIntervals {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, L; cin >> N >> M >> L;
        if (N > M) {
            cout << 0 << endl;
            return;
        }

        vector2<FieldMod> D(N+1, N+1, 0);
        D[0][0] = 1;
        for (int i = 1; i <= M; ++i) {
            for (int j = N; j >= 0; --j) {
                for (int k = j; k >= 0; --k) {
                    if (j > k && i != L) {
                        D[j][k+1] += D[j][k];
                    }

                    if (j < N) {
                        D[j+1][k+1] += D[j][k];
                        D[j+1][k] += D[j][k];
                    }
                    
                    if (i == L) D[j][k] = 0;
                }
            }
        }
        
        FieldMod ans = D[N][N];
        for (int i = 1; i <= N; ++i) {
            ans *= i;
        }
        
        cout << ans << endl;
    }
};
