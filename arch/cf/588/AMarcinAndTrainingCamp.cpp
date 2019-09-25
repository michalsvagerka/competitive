#include "../l/lib.h"

class AMarcinAndTrainingCamp {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N);
        vector<int> B(N);
        cin >> A >> B;
        ll ans = 0;
        
        map<ll, int> C;
        for (ll a: A) C[a]++;
        vector<ll> D;
        for (auto c: C) if (c.y >= 2) D.push_back(c.x);
//        if (D.empty()) {
//            cout << 0 << endl;
//            return;
//        }
        
        for (int i = 0; i < N; ++i) {
            bool ok = false;
            for (ll d: D) {
                if ((d&A[i])==A[i]) { ok = true; break; }
            }
            if (ok) ans += B[i];
        }
        cout << ans << endl;
    }
};
