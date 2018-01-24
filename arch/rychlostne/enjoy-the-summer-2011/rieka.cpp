#include "../l/lib.h"
// #include "../l/mod.h"

class rieka {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M; cin >> N >> M;
        vector<pii> P;
        for (int i = 0; i < N; ++i) {
            int a,b; cin >> a >> b;
            if (a > b) P.push_back({a,b});
        }
        sort(P.begin(),P.end());
        if (P.empty()) {
            cout << M << endl;
            return;
        }
        vector<int> B(P.size(), P.back().y);
        for (int i = P.size()-1; i > 0; --i) {
            B[i-1] = min(B[i], P[i-1].y);
        }
        int t = P[0].y;
        ll a = 0;
        for (int i = 1; i < P.size(); ++i) {
            if (B[i] > P[i-1].x) {
                a += P[i-1].x - t;
                t = M;
            }
            t = min(t, P[i].y);
        }
        a += P.back().x - t;

        cout << 2*a + M << endl;
    }
};
