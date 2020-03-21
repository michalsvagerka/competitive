#include "../l/lib.h"

class CPrefixEnlightenment {
public:
    struct Group {
        vector<int> A[2];
        bool Req[2];
    };
    int sz(const Group&g) {
        return g.A[0].size() + g.A[1].size();
    }
    int cnt(const Group&g) {
        if (g.Req[0]) return g.A[0].size();
        else if (g.Req[1]) return g.A[1].size();
        else return min(g.A[0].size(), g.A[1].size());
    }

    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        string I; cin >> I;
        vector<vector<int>> S(K);
        vector<vector<int>> G(N);
        for (int i = 0; i < K; ++i) {
            int c; cin >> c;
            S[i].resize(c); cin >> S[i];
            for (int s: S[i]) G[s-1].push_back(i);
        }

        K = max(K, N);
        vector<Group> GR(K);
        vector<pii> W(K);
        for (int i = 0; i < K; ++i) {
            W[i] = {i, 0};
            GR[i].A[0].push_back(i);
        }

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            if (G[i].size() == 1) {
                int j = G[i][0];
                ans -= cnt(GR[W[j].x]);
                if (I[i] == '0') {
                    GR[W[j].x].Req[W[j].y] = true;
                } else {
                    GR[W[j].x].Req[1-W[j].y] = true;
                }
                ans += cnt(GR[W[j].x]);
            } else if (G[i].size() == 2) {
                bool disj = I[i] == '1';
                int a = G[i][0], b = G[i][1];
                if (W[a].x != W[b].x) {
                    int g = W[a].x, h = W[b].x;
                    if (sz(GR[g]) < sz(GR[h])) swap(g,h);
                    ans -= cnt(GR[g]);
                    ans -= cnt(GR[h]);
                    if (W[a].y == W[b].y) disj = !disj;
                    for (int j = 0; j < 2; ++j) {
                        int k = j;
                        if (disj) k = 1-k;
                        for (int v: GR[h].A[j]) {
                            GR[g].A[k].push_back(v);
                            W[v] = {g, k};
                        }

                        GR[g].Req[k] |= GR[h].Req[j];

                        GR[h].A[j].clear();
                    }
                    ans += cnt(GR[W[a].x]);
                }
            }


            cout << ans << '\n';
        }
    }
};
