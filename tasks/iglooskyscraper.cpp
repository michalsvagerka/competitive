#include "../l/lib.h"
 #include "../l/util.h"

class iglooskyscraper {
public:
    vector<LinearEnvelope::Upper<ll>> E;
    vector<vector<pii>> T;

    void put(int l, int r, int i, int L, int R, int t, int q) {
        if (l >= R || r <= L) return;
        if (l <= L && r >= R) T[i].push_back({t,q});
        else {
            put(l,r,2*i,L,(L+R)/2,t,q);
            put(l,r,2*i+1,(L+R)/2,R,t,q);
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        int M = 1<<logceil(N);
        vector<pair<pii,int>> W(N);
        for (int i = 0; i < N; ++i) {
            cin >> W[i].x.y >> W[i].x.x;
            W[i].y = i;
        }
        sort(W.begin(),W.end());

        E.resize(2*M);
        T.resize(2*M);
        for (int i = 0; i < N; ++i) {
            int j = M + W[i].y;
            while (j) {
                E[j].insert_line(W[i].x.x, W[i].x.y, W[i].y+1);
                j /= 2;
            }
        }

        for (int q = 0; q < Q; ++q) {
            int l,r,t; cin >> l >> r >> t;
            --l;
            put(l,r,1,0,M,t,q);
        }

        vector<pair<ll,int>> Ans(Q, {0,-1});
        for (int i = 1; i < M+N; ++i) {
            sort(T[i].begin(),T[i].end());
            int l = 0;
            for (pii t:T[i]) {
                Ans[t.y] = max(Ans[t.y], E[i].advance(t.x-l));
                l = t.x;
            }
        }

        for (auto&ans:Ans) cout << ans.y << '\n';
    }
};
