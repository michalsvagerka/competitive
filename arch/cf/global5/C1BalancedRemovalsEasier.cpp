#include "../../../l/lib.h"

class C1BalancedRemovalsEasier {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pair<pii,pii>> P(N);
        for (int i = 0; i < N; ++i) {
            cin >> P[i].x >> P[i].y.x;
            P[i].y.y = i;
        }

        sort(P.begin(),P.end());

        vector<pii> Ans;
        vector<bool> Used(N, false);
        for (int j = 0; j < 3; ++j) {
            for (int i = 1; i < P.size(); ++i) {
                if (!Used[P[i-1].y.y] && P[i-1].x == P[i].x) {
                    Used[P[i-1].y.y] = Used[P[i].y.y] = true;
                    Ans.push_back({P[i-1].y.y, P[i].y.y});
                }
            }

            vector<pair<pii,pii>> Q;
            for (int i = 0; i < P.size(); ++i) {
                if (!Used[P[i].y.y]) Q.push_back(P[i]);
            }
            swap(P,Q);
            if (j == 0) for (auto&p: P) swap(p.x.y, p.y.x);
            else if (j == 1) for (auto&p: P) swap(p.x.x, p.y.x);
            sort(P.begin(),P.end());
        }

        for (int j = 0; j < 3; ++j) {
            for (int i = 1; i < P.size(); ++i) {
                if (!Used[P[i-1].y.y] && P[i-1].x.x == P[i].x.x) {
                    Used[P[i-1].y.y] = Used[P[i].y.y] = true;
                    Ans.push_back({P[i-1].y.y, P[i].y.y});
                }
            }

            vector<pair<pii,pii>> Q;
            for (int i = 0; i < P.size(); ++i) {
                if (!Used[P[i].y.y]) Q.push_back(P[i]);
            }
            swap(P,Q);
            if (j == 0) for (auto&p: P) swap(p.x.x, p.x.y);
            else if (j == 1) for (auto&p: P) swap(p.x.x, p.y.x);
            sort(P.begin(),P.end());
        }

        for (int i = 0; i < P.size(); i += 2) {
            Ans.push_back({P[i].y.y, P[i+1].y.y});
        }
        for (pii ans: Ans) cout << ans.x+1 << ' ' << ans.y+1 << '\n';
    }
};
