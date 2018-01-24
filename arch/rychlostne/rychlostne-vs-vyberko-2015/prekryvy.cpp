#include "../l/lib.h"
// #include "../l/mod.h"

class prekryvy {
public:
    void solve(istream& cin, ostream& cout) {
        ui N, D; cin >> N >> D;
        vector<puu> L(D,{80000000,-1}), H(D,{0,-1});
        for (ui i = 0; i < N; ++i) {
            int z,k,d; cin >> z >> k >> d;
            --d;
            L[d] = min(L[d], {k, i+1});
            H[d] = max(H[d], {z, i+1});
        }

        for (ui d = 0; d < D; ++d) {
            if (L[d].x < H[d].x) {
                cout << "ANO " << L[d].y << ' ' << H[d].y << '\n';
            } else {
                cout << "NIE\n";
            }
        }

    }
};
