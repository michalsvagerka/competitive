#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
    int N, M;
    vector<vector<int>> E;
    vector<int> C;
    vector<bool> P, V;
    vector<int> R, OC;
    unordered_map<pii, ll> A;
    bool odd;

    void dfs(int u, bool p) {
        if (V[u]) {
            if (!odd && P[u] != p) {
                odd = true;

                OC.push_back(u);
                for (int i = R.size()-1; R[i] != u; --i) {
                    OC.push_back(R[i]);
                }
            }
            return;
        }

        R.push_back(u);
        V[u] = true;
        P[u] = p;
        for (int v: E[u]) dfs(v, !p);
        R.pop_back();
    }

    ll dfs2(int u, int p) {
        if (V[u]) return 0;

        V[u] = true;
        ll bal = C[u];
        for (int v: E[u]) {
            if (v != p) {
                ll x = dfs2(v, u);
                A[{v,u}] += x;
                bal -= x;
            }
        }
        return bal;
    }

void solve(istream& cin, ostream& cout) {
    cin >> N >> M;
    C.resize(N); cin >> C;
    E.resize(N);
    P = V = vector<bool>(N, false);
    vector<pii> F;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        F.push_back({u,v});
        E[u].push_back(v);
        E[v].push_back(u);
    }
    odd = false;

    dfs(0, true);
    fill(V.begin(),V.end(),false);
//    cout << V << P << OC;
    if (OC.empty()) {
        if (dfs2(0, -1) != 0) {
            cout << "NO\n";
            return;
        }
    } else {
        ll z = dfs2(OC[0], -1);
        for (int i = 0; i < OC.size(); ++i) {
            int u = OC[i];
            int v = OC[(i+1)%OC.size()];
            A[{u,v}] -= i%2 ? z/2 : -z/2;
        }
    }

    vector<ll> Ans(M);
    for (int i = 0; i < M; ++i) {
        Ans[i] = A[{F[i].x, F[i].y}] + A[{F[i].y, F[i].x}];
    }
    cout << "YES\n";
    for (ll a:Ans) cout << a << '\n';
}
};
