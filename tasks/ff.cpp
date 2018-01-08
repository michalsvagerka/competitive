#include "../l/lib.h"
#include "../l/tree.h"

class ff {
public:
    void solve(istream& cin, ostream& cout) {
        ui F,P; cin >> P >> F;
        vector<ui> O(P); cin >> O;
        for (ui&o:O) --o;

        vector<int> L(F); cin >> L;
        vector<ui> N(P, P);
        vector<ui> I(F, P);
        vector<bool> R(P, true);
        for (ui i = P-1; i != -1; --i) {
            if (I[O[i]] != P) {
                N[i] = I[O[i]];
                R[I[O[i]]] = false;
            }
            I[O[i]] = i;
        }

        AddMaxTree<ll> T;
        T.setup(P, 0);
        for (ui i = 0; i < P; ++i) {
            if (R[i]) {
                T.put(i, N[i]-1, L[O[i]]);
            }
        }
        ll ans = T.get(0, P-1);
        for (ui i = 0; i < P; ++i) {
            T.put(i, N[i]-1, -L[O[i]]);
            if (N[i] != P) {
                T.put(N[i], N[N[i]]-1, L[O[i]]);
                ans = max(ans, T.get(0, P-1));
            }
        }

        cout << ans << endl;
    }
};
