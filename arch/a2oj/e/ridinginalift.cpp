#include "../../../l/lib.h"
#include "../../../l/mod.h"

class ridinginalift {
public:
    void solve(istream& cin, ostream& cout) {
        int N,A,B,K;
        cin >> N >> A >> B >> K;
        if (A < B) {
            N = B-1;
            A = B-A-1;
        } else {
            N -= B;
            A -= B+1;
        }

        vector<FieldMod> D(N, 0), F(N+1, 0);
        D[A] = 1;
        for (int k = 0; k < K; ++k) {
            for (int i = 0; i < N; ++i) F[i+1] = F[i] + D[i];
            for (int j = 0; j < N; ++j) D[j] = F[N] - F[(j+1)/2] - D[j];
        }

        FieldMod ans = 0;
        for (int l = 0; l < N; ++l) {
            ans += D[l];
        }

        cout << ans << endl;
    }
};
