#include "../../../l/lib.h"
#include "../../../l/fenwick.h"

class TaskD {
public:
    int N, T;
    int Ans;
    vector<vector<pii>> E;
    vector<ll> C;
    vector<int> Enter,Exit;

    void dfs(int u, int p) {
        ll d = 0;
        for (pii v: E[u]) {
            if (v.x != p) {
                dfs(v.x, u);
                d = max(d, C[v.x] + v.y);
            }
        }
        C[u] = d;
    }

    void dfs2(int u, int p, ll a) {
        C[u] = max(C[u], a);
        vector<ll   > Z;
        for (pii v:E[u]) {
            if (v.x != p) {
                Z.push_back(C[v.x] + v.y);
            }
        }
        vector<ll> L(Z.size()+1, a), R = L;
        for (int i = 0; i < Z.size(); ++i) {
            L[i+1] = max(L[i], Z[i]);
            R[Z.size()-i-1] = max(R[Z.size()-i], Z[Z.size()-i-1]);
        }

        int i = 0;
        for (pii v:E[u]) {
            if (v.x != p) {
                dfs2(v.x, u, max(L[i], R[i+1]) + v.y);
                ++i;
            }
        }
    }

    void dfs3(int u, int p) {
        Enter[u] = T++;
        for (pii v:E[u]) {
            if (v.x!=p) {
                dfs3(v.x,u);
            }
        }
        Exit[u] = T;
    }

//    void dfs3(int u, int p, ll L, multiset<ll>& Z) {
//        Z.insert(C[u]);
//        for (pii v:E[u]) {
//            if (v.x != p) {
//                multiset<ll> M;
//                dfs3(v.x, u, L, M);
//                if (M.size() > Z.size()) swap(M, Z);
//                for (ll m:M) Z.insert(m);
//            }
//        }
//
//        while (*prev(Z.end()) > *Z.begin() + L) {
//            Z.erase(prev(Z.end()));
//        }
//
//        Ans = max(Ans, (int)Z.size());
//    }

void solve(istream& cin, ostream& cout) {
    cin >> N;
    E.resize(N);
    C.resize(N);
    Enter = Exit = vector<int>(N, 0);
    T = 0;
    for (int i = 0; i < N - 1; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        --u;
        --v;
        E[u].push_back({v,c});
        E[v].push_back({u,c});
    }
    dfs(0, -1);
    dfs2(0, -1, 0);

    vector<pair<ll,int>> W;
    for (int i = 0; i < N; ++i) W.push_back({C[i],i});
    sort(W.begin(),W.end());

    dfs3(W[0].y, -1);

    int Q; cin >> Q;
    for (int q = 0; q < Q; ++q) {
        ll L; cin >> L;
        Ans = 0;
        Fenwick<int> F(N, 0);
        int e = 0;
        for (int b = 0; b < N; ++b) {
            while (e < N && W[e].x <= W[b].x + L) {
                F.add(Enter[W[e].y], 1);
                e++;
            }

            Ans = max(Ans, F.range(Enter[W[b].y], Exit[W[b].y]-1));

            F.add(Enter[W[b].y], -1);
        }
//        multiset<ll> Z;
//        dfs3(W[0].y, -1, L, Z);
        cout << Ans << '\n';
    }
}
};
