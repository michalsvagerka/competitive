#include "../../../l/lib.h"
// #include "../l/mod.h"

class zipline {
public:
    void persistentLIS(const vector<int> &H, vector<map<int, int>> &S, vector<int> &L, vector<int> &R, bool lt) {
        int N = H.size();
        int g = lt ? 0 : int(1e9+7);
        S.push_back({{-1,g}});
        vector<int> G{g};
        for (int i = 0; i < N; ++i) {
            int k = bsh(0, (int)G.size()-1, [&](int t) { return lt ? G[t] < H[i] : G[t] > H[i]; });
            if (k == (int)G.size()-1) {
                G.push_back(H[i]);
                S.push_back({{i,H[i]}});
            } else {
                if (lt ? G[k+1] > H[i] : G[k+1] < H[i]) {
                    G[k+1] = H[i];
                    S[k+1][i] = H[i];
                }
            }
            L.push_back(k+1);
            R.push_back(S.size());
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> H(N); cin >> H;

        vector<map<int,int>> S1, S2;
        vector<int> L1, L2, R1, R2;
        persistentLIS(H, S1, L1, R1, true);
        reverse(H.begin(),H.end());
        persistentLIS(H, S2, L2, R2, false);
        reverse(H.begin(),H.end());

        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            int ans = R1.back()-2;

            --a;
            int k = a == 0 ? 0 : bsh(0, R1[a-1]-1, [&](int r) { return prev(S1[r].lower_bound(a))->y < b;});
            int l = a == N-1 ? 0 : bsh(0, R2[N-a-2]-1, [&](int r) { return prev(S2[r].lower_bound(N-a-1))->y > b;});
            ans = max(ans, k+l+1);

            int r = L1[a]-1;
            int s = a == 0 ? 0 : prev(S1[r].lower_bound(a))->y;
            int t = a == N-1 ? 0 : bsh(0, R2[N-a-2]-1, [&](int r) { return prev(S2[r].lower_bound(N-a-1))->y > s;});
            ans = max(ans, r+t);

            int u = L2[N-a-1]-1;
            int v = a == N-1 ? 0 : prev(S2[u].lower_bound(N-a-1))->y;
            int w = a == 0 ? 0 : bsh(0, R1[a-1]-1, [&](int r) { return prev(S1[r].lower_bound(a))->y < s;});
            ans = max(ans, u+w+1);

            cout << ans << endl;
        }

    }
};
