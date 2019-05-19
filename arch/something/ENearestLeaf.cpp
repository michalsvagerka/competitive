#include "../l/lib.h"
#include "../l/segtree.h"

class ENearestLeaf {
public:
    vector<vector<pii>> E;
    vector<ll> D;
    AddMinTree<ll> T;
    vector<vector<pair<pii, int>>> Queries;
    vector<ll> Answers;
    vector<int> Enter, Exit;
    int TIME;

    void depth(int u, ll d) {
        Enter[u] = TIME++;
        D[u] = d;
        for (pii e:E[u]) depth(e.x, e.y + d);
        Exit[u] = TIME;
    }

    void answer(int u, int w) {
        T.put(Enter[u], Exit[u]-1, -2*w);
        for (auto &q: Queries[u]) {
            Answers[q.y] = T.get(q.x.x, q.x.y) + D[u];
            if (q.x.x == 1 && E[0].size() == 1) Answers[q.y] = min(Answers[q.y], D[u]);
        }

        for (pii e:E[u]) answer(e.x, e.y);
        T.put(Enter[u], Exit[u]-1, 2*w);
    }

    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<int> P(N-1), W(N-1);
        for (int i = 0; i < N - 1; ++i) cin >> P[i] >> W[i];
        E.resize(N);
        Enter.resize(N);
        Exit.resize(N);
        TIME = 0;

        for (int i = 0; i < N-1; ++i) E[P[i]-1].emplace_back(i+1, W[i]);
        D.resize(N);
        depth(0, 0LL);
        vector<ll> RR = D;
        for (int i = 0; i < N; ++i) if (!E[i].empty()) RR[i] = 1e17;
        T.setup(RR, 0LL);

        Queries.resize(N);
        Answers.resize(Q);
        for (int i = 0; i < Q; ++i) {
            int v, l, r; cin >> v >> l >> r;
            Queries[v-1].push_back({{l-1,r-1},i});
        }

        answer(0, 0);
        for (ll ans: Answers) cout << ans << '\n';
    }
};
