#include "../l/lib.h"
#include "../l/tree.h"

class platforms {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        vector<pair<int,pii>> P(N);
        vector<int> X(2*N);
        for (ui i = 0; i < N; ++i) {
            cin >> P[i].x >> P[i].y.x >> P[i].y.y;
            P[i].y.y--;
            X[2*i] = P[i].y.y;
            X[2*i+1] = P[i].y.x;
        }

        sort(P.begin(),P.end());
        sort(X.begin(),X.end());
        auto end = unique(X.begin(),X.end());
        X.erase(end,X.end());
        
        AssignMaxTree<int> S;
        S.setup(X.size(),0);
        ll ans = 0;
        for (auto &p: P) {
            int x1 = distance(X.begin(),lower_bound(X.begin(),X.end(),p.y.x));
            int x2 = distance(X.begin(),lower_bound(X.begin(),X.end(),p.y.y));
            ans += 2*p.x - S.get(x1) - S.get(x2);
            S.put(x1, x2, p.x);
        }
        cout << ans << endl;
    }
};
