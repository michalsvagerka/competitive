#include "../l/lib.h"

typedef pair<ll,ll> pll;
constexpr int MX = 1000000;
class TaskE {
public:
void solve(istream& cin, ostream& cout) {
    vector<int> S(MX, 0);
    S[1] = 1;
    for (int i = 2; i < MX; ++i) {
        if (S[i] == 0) {
            for (int j = i; j < MX; j += i) {
                S[j] = i;
            }
        }
    }

    int M; cin >> M;
    map<int, ll> Ans;
    vector<vector<pll>> W(MX);
    for (int i = 0; i < M; ++i) {
        int p; ll a;
        cin >> p >> a;
        W[p].emplace_back(0, a);
    }
    ll K; cin >> K;

    for (int i = MX-1; i >= 2; --i) {
        if (S[i] != i) continue;
        if (W[i].empty()) continue;

        vector<pii> F;
        int g = i-1;
        while (g != 1) {
            if (!F.empty() && F.back().x == S[g]) F.back().y++;
            else F.emplace_back(S[g], 1);
            g /= S[g];
        }

        for (pll p: W[i]) { if (p.y > K) Ans[i] += p.y - K; }

        for (pii f: F) {
            vector<pll> C(W[f.x].begin(), W[f.x].end());
            for (pll p: W[i]) {
                ll b = p.x+1;
                ll e = p.x + f.y*(min(K, p.y)-p.x) + 1;
                if (e > b) C.push_back({b, e});
            }
            if (C.empty()) continue;

            sort(C.begin(),C.end());
            vector<pll> G{C[0]};
            for (int i = 1; i < C.size(); ++i) {
                if (G.back().y >= C[i].x) {
                    G.back().y += C[i].y - C[i].x;
                } else {
                    G.push_back(C[i]);
                }
            }
            W[f.x] = G;
        }
    }

    cout << Ans.size() << '\n';
    for (auto ans: Ans) {
        cout << ans.x << ' ' << ans.y << endl;
    }
}
};
