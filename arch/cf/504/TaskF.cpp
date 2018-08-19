#include "../l/lib.h"
 #include "../l/util.h"

#include "../l/graph.h"

class TaskF {
public:
    Tree T;
    vector<vector<int>> W;
    vector<pii> Bad;
    bool inf;

    inline bool isBad(int a, int b) {
        auto it = lower_bound(Bad.begin(), Bad.end(), pii{a,b});
        return it != Bad.end() && *it == pii{a,b};
    }

    ll calc(int u, map<int,int> &cur) {
        ll ans = 0;
        for (int v:T.E[u]) {
            if (v != T.P[u]) {
                map<int,int> Z;
                ans += calc(v, Z);
                if (Z.size() > cur.size()) swap(Z, cur);
                for (pii z:Z) cur[z.x] += z.y;
            }
        }


        for (int w:W[u]) {
            if (w > 0) {
                cur[w]++;
            } else {
                auto it = cur.find(-w);
                it->y -= 2;
                if (it->y == 0) cur.erase(it);
            }
        }


        if (u != 0 && !isBad(u,T.P[u])) {
            if (cur.empty()) inf = true;
            else ans += cur.begin()->x;
        }
        return ans;
    }

void solve(istream& cin, ostream& cout) {
    int N, M, K; cin >> N >> K >> M;

    W.resize(N);
    T = Tree(N);

    UnionFind UT(N);
    for (int i = 0; i < K; ++i) {
        int a,b; cin >> a >> b;
        --a; --b;
        UT.unite(a,b);
        T.addEdge(a,b);
    }

    vector<pair<pii,int>> E(M);
    for (int i = 0; i < M; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        --a;
        --b;
        if (UT.unite(a, b)) {
            T.addEdge(a, b);
            // this is a weird edge, remember that!
            Bad.push_back({b,a});
            Bad.push_back({a,b});
        }
        E[i] = {{a,b}, w};
    };
    sort(Bad.begin(),Bad.end());

    T.calcLA();
    UnionFind UF(N);
    for (int i = 0; i < M; ++i) {
        int a = E[i].x.x;
        int b = E[i].x.y;
        int w = E[i].y;
        if (UF.unite(a,b) && !isBad(a,b)) {
            W[a].push_back(w);
            W[b].push_back(w);
            W[T.lca(a,b)].push_back(-w);
        }
    }

    inf = false;
    map<int,int> Q;
//    ll ans = 183804793650LL;
    ll ans = calc(0, Q);
    if (inf) cout << -1 << '\n'; else cout << ans << '\n';
}
};
