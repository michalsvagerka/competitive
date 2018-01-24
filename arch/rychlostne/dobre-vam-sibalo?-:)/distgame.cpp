#include "../l/lib.h"
// #include "../l/mod.h"

class distgame {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        string F; cin >> F;
        vector<ui> A(N); cin >> A;
        if ((F == "Zuzka") ^ (N%2==1)) {
            cout << bsh(0,1000000000,[&](int d) {
                ui e = 0, c = 0;
                for (ui b = 0; b < N; ++b) {
                    while (e < N && A[e]-A[b]<d) ++e;
                    c = max(c, e-b);
                }
                return c < (N+1)/2+1;
            }) << endl;
        } else {
            cout << bsh(0,1000000000,[&](int d) {
                ui c = 0;
                for (ui b = 0; b < N; ) {
                    ui e = b;
                    while (e < N && A[e]-A[b]<d) ++e;
                    c += e-b-1;
                    b = e;
                }
                return c <= N/2-1;
            }) << endl;
        }
    }
};
