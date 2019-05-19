#include "../l/lib.h"
 #include "../l/mod.h"

class BMashmokhAndACM {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<FieldMod> D(N+1, 0);
        D[1] = 1;
        for (int i = 0; i < K; ++i) {
            vector<FieldMod> E(N+1, 0);
            for (int j = 1; j <= N; ++j) {
                for (int k = j; k <= N; k += j) {
                    E[k] += D[j];
                }
            }
            swap(E,D);
        }

        FieldMod ans = 0;
        for (int i = 1; i <= N; ++i) ans += D[i];
        cout << ans << '\n';

    }
};
