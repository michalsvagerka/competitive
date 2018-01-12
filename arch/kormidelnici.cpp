#include "../l/lib.h"
// #include "../l/mod.h"

class kormidelnici {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        vector<pair<pii,ui>> P(N),R;
        for (ui i = 0; i < N; ++i) {
            cin >> P[i].x.x >> P[i].x.y;
            P[i].y = i;
        }
        R = P;
        for (auto&p:R) swap(p.x.x,p.x.y);
        sort(P.begin(),P.end());
        sort(R.begin(),R.end());
        vector<vector<pii>> E(N);
        for (int i = 0; i < N-1; ++i) {
            E[P[i].y].emplace_back(P[i+1].y, P[i+1].x.x - P[i].x.x);
            E[P[i+1].y].emplace_back(P[i].y, P[i+1].x.x - P[i].x.x);
            E[R[i].y].emplace_back(R[i+1].y, R[i+1].x.x - R[i].x.x);
            E[R[i+1].y].emplace_back(R[i].y, R[i+1].x.x - R[i].x.x);
        }

        vector<ll> D(N, 1e16);
        minheap<pair<ll,int>> Q;
        D[0] = 0ll;
        Q.push({0ll,0});
        while(!Q.empty()) {
            auto q=Q.top(); Q.pop();
            if (D[q.y] != q.x) continue;
            for (auto e:E[q.y]) {
                ll x = q.x + e.y;
                if (D[e.x] > x) {
                    D[e.x] = x;
                    Q.push({x,e.x});
                }
            }
        }
        cout << D.back() << endl;
    }
};
