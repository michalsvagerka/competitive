#include "../l/lib.h"
#include "../l/frac.h"

class WormholeInOne {
public:
    struct Soln {
        int count;
        vector<pii> Pairs;
        Fraction angle;
        int firstHole;
    };

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<pii> P(N); cin >> P;
            map<Fraction, vector<pii>> Pts;
            for (int i = 0; i < N; ++i) {
                for (int j = i+1; j < N; ++j) {
                    ll dx = P[i].x - P[j].x;
                    ll dy = P[i].y - P[j].y;
                    Fraction F{dx, dy};
                    Pts[F].push_back({i,j});
                }
            }

            cout << "Case #" << t+1 << ": ";

            int best = 1;
            for (auto a: Pts) {
                vector<vector<int>> E(N);
                for (pii b: a.y) {
                    E[b.x].push_back(b.y);
                    E[b.y].push_back(b.x);
                }

                int ans = 0;
                for (int i = 0; i < N; ++i) {
                    if (!E[i].empty()) {
                        for (int j : E[i]) E[j].clear();
                        ans += E[i].size() + 1;
                    }
                }

                if (ans % 2 == 0) ans++;
                ans++;

                best = max(best, min(N, ans));
            }

            cout << best << endl;
        }
    }
};
