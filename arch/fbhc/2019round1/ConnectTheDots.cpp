#include "../l/lib.h"
#include "../l/fenwick.h"

constexpr int MX = 2e9 + 3;
class ConnectTheDots {
public:
    int T = 0;
    void solve(istream& cin, ostream& cout) {
        cout << "Case #" << ++T << ": ";
        int ans = MX;
        int N, H, V; cin >> N >> H >> V;
        ll X1, X2, AX, BX, CX, DX; cin >> X1 >> X2 >> AX >> BX >> CX >> DX;
        ll Y1, Y2, AY, BY, CY, DY; cin >> Y1 >> Y2 >> AY >> BY >> CY >> DY;
        if (H + V < N) {
            cout << -1 << '\n';
            return;
        }

        vector<pii> P{{X1, Y1}, {X2, Y2}};
        for (int i = 2; i < N; ++i) {
            P.emplace_back(1 + (AX * P[i-2].x + BX * P[i-1].x + CX) % DX, 1 + (AY * P[i-2].y + BY * P[i-1].y + CY) % DY);
        }
        sort(P.begin(),P.end());
        multiset<int> LargeY;
        vector<pair<pii, int>> Q;
        for (int i = 0; i < N; ++i) Q.push_back({{P[i].y, P[i].x}, i});
        for (int i = 0; i < N; ++i) LargeY.insert(P[i].x);
        sort(Q.begin(),Q.end());

        Fenwick<int> F(N, 0);
        for (int i = 0; i <= N; ++i) {
            if (N - i <= H) {
                // Use i..N-1 for horizontal
                int horiz = 0;
                if (i != N) {
                    assert(!LargeY.empty());
                    horiz = *LargeY.rbegin();
                }

                // Use max(0, V-i) from 0..i-1 for horizontal; pick the smallest
                if (i > V) {
                    int s = F.max_lower(i-V) + 1;
                    assert(s < N);
                    horiz = max(horiz, P[s].x);
                }

                // Use some subset of 0..i-1 for vertical
                int vert = i == 0 ? 0 : Q[i-1].x.x;

                ans = min(ans, vert + horiz);
            }

            if (i != N) {
                auto it = LargeY.find(Q[i].x.y);
                assert(it != LargeY.end());
                LargeY.erase(it);

                F.add(Q[i].y, 1);
            }
        }
        cout << ans << '\n';
    }
};
