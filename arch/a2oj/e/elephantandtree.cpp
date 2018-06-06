#include "../../../l/lib.h"
// #include "../l/mod.h"

class elephantandtree {
public:
    struct Segment {
        int L,R;
        vector<int> C;
        int Min,Count,Delta;

        Segment(int l, int r) : L(l), R(r), C(r-l, 0), Min(0), Count(r-l), Delta(0) {}

        void add(int l, int r, int D) {
            if (r <= L || l >= R) return;
            if (l <= L && r >= R) {
                Delta += D;
                Min += D;
            } else {
                for (int i = max(L, l); i < min(R, r); ++i) C[i-L] += D;
                for (int i = 0; i < R-L; ++i) C[i] += Delta;
                Delta = 0;
                Min = *min_element(C.begin(),C.end());
                Count = count(C.begin(),C.end(),Min);
            }
        }

        int countZeros() {
            return Min ? 0 : Count;
        }
    };


    int N, M;
    vector<vector<int>> E, A;
    vector<int> Enter,Exit,Ans;
    vector<Segment> S;

    void dfs(int u, int p, int&t) {
        Enter[u] = t++;
        for (int v:E[u]) if (v!=p) dfs(v,u,t);
        Exit[u] = t;
    }

    void dfs2(int u, int p) {
        if (!A[u].empty()) for (auto&s:S) s.add(Enter[u], Exit[u], 1);
        for (int a:A[u]) for (auto&s:S) s.add(Enter[a], Exit[a], 1);
        Ans[u] = N-1;
        for (auto&s:S) Ans[u] -= s.countZeros();
        Ans[u] = max(Ans[u], 0);
        for (int v:E[u]) if (v!=p) dfs2(v,u);
        for (int a:A[u]) for (auto&s:S) s.add(Enter[a], Exit[a], -1);
        if (!A[u].empty()) for (auto&s:S) s.add(Enter[u], Exit[u], -1);
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        E.resize(N);
        A.resize(N);
        Enter.resize(N);
        Exit.resize(N);
        Ans.resize(N);

        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            A[a].push_back(b);
            A[b].push_back(a);
        }

        int t = 0;
        dfs(0, -1, t);

        for (int i = 0; i < N; i += 300) S.emplace_back(i,min(N,i+300));
        dfs2(0, -1);

        cout << Ans;
    }
};
