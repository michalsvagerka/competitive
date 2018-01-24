#include "../l/lib.h"
// #include "../l/mod.h"

const ll inf = 1e16;

class ubytuj {
public:
    void solve(istream& cin, ostream& cout) {
        int D,N; cin >> D >> N;
        if (D == 1) { cout << -1 << endl; return; }
        vector<ll> A(7,inf),B(7,inf);
        for (int i = 0; i < N; ++i) {
            int t,c; cin >> t >> c;
            if (t==2) A.push_back(c);
            else B.push_back(c);
        }
        sort(A.begin(),A.end());
        sort(B.begin(),B.end());
        ll best = inf;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 2; ++j) {
                if ((i*2+j*3) % 6 == D % 6) {
                    ll cost = 0;
                    for (int k = 0; k < i; ++k) cost += A[k];
                    for (int k = 0; k < j; ++k) cost += B[k];
                    int k = i, l = j;
                    while (k*2 + l*3 < D && cost < inf) {
                        ll costA = A[k]+A[k+1]+A[k+2];
                        ll costB = B[l]+B[l+1];
                        cost += min(costA, costB);
                        if (costA < costB) k+=3; else l+=2;
                    }
                    best = min(best, cost);
                }
            }
        }

        if (best == inf) cout << -1;
        else cout << best;
        cout << endl;
    }
};
