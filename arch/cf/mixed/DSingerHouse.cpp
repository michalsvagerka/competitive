#include "../l/lib.h"
#include "../l/mod.h"

class DSingerHouse {
public:
    void solve(istream& cin, ostream& cout) {
        int K; cin >> K;
        auto F = FieldMod::fact(K+2);
        auto I = FieldMod::invfact(K+2);
        vector<FieldMod> D(K, 0);
        D[0] = D[1] = 1;
        for (int i = 1; i < K; ++i) {
            vector<FieldMod> E(K, 0);
            for (int j = 0; j < K; ++j) {
                if (D[j] == 0) continue;
                for (int k = 0; k < K; ++k) {
                    if (j + k > K) break;
                    auto f = D[j] * D[k];
                    if (j+k < K) E[j+k] += (2*(j+k)+1) * f;
                    if (j+k+1 < K) E[j+k+1] += f;
                    if (j+k-1 < K && j+k >= 2) E[j+k-1] += (j+k) * (j+k-1) * f;
                }
            }

            swap(D,E);
        }

        cout << D[1] << endl;
    }
};
