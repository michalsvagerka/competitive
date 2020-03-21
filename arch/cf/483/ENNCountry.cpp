#include "../l/lib.h"
#include "../l/graph.h"

constexpr int LOGN = 20;

class ENNCountry {
public:
    TreeX T{1};
    vector<int> Ans, Enter, Exit;
    vector<vector<pii>> Question;
    vector<vector<int>> Up,Conn;

    int dfs(int u, int p) {
        for (int v : T.E[u]) if (v != p) {
            int z = dfs(v, u);
            if (T.depth(z) < T.depth(Up[0][u])) Up[0][u] = z;
        }
        return Up[0][u];
    }

    void dfs2(set<int>&S, int u, int p) {
        for (int v : T.E[u]) if (v != p) {
            set<int> SS;
            dfs2(SS, v, u);
            if (SS.size() > S.size()) swap(SS,S);
            for (int s: SS) S.insert(s);
        }

        for (int c: Conn[u]) {
            S.insert(Enter[c]);
        }

        for (pii q: Question[u]) {
            int v = q.x;
            int i = q.y;
            int a = Enter[v];
            int b = Exit[v];
            auto it = S.lower_bound(a);
            if (it != S.end() && *it < b) {
                Ans[i]--;
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N-1); cin >> P;
        T = TreeX(N);
        for (int i = 0; i < N-1; ++i) {
            T.addEdge(i+1, P[i]-1);
        }
        T.calcLA();

        int M; cin >> M;
        vector<pii> R(M); cin >> R;
        for (pii&r: R) { --r.x; --r.y; }
        Conn.resize(N);
        for (pii&r: R) { Conn[r.x].push_back(r.y); Conn[r.y].push_back(r.x); }

        int Q; cin >> Q;
        vector<pii> W(Q); cin >> W;
        for (pii&w: W) { --w.x; --w.y; }

        Up = vector2<int>(LOGN, N);
        for (int i = 0; i < N; ++i) Up[0][i] = i;

        for (int i = 0; i < M; ++i) {
            int a = R[i].x;
            int b = R[i].y;
            int c = T.lca(a,b);
            if (T.depth(c) < T.depth(Up[0][a])) Up[0][a] = c;
            if (T.depth(c) < T.depth(Up[0][b])) Up[0][b] = c;
        }

        dfs(0, -1);

        for (int l = 1; l < LOGN; ++l) {
            for (int i = 0; i < N; ++i) {
                Up[l][i] = Up[l-1][Up[l-1][i]];
            }
        }

        Ans.assign(Q, -1);
        Question.resize(N);
        for (int i = 0; i < Q; ++i) {
            int a = W[i].x;
            int b = W[i].y;
            int c = T.lca(a,b);
            if (T.depth(c) >= max(T.depth(Up[LOGN-1][a]), T.depth(Up[LOGN-1][b]))) {
                Ans[i] = 2;
                for (int j = LOGN-1; j >= 0; --j) {
                    if (T.depth(Up[j][a]) > T.depth(c)) {
                        Ans[i] += 1<<j;
                        a = Up[j][a];
                    }

                    if (T.depth(Up[j][b]) > T.depth(c)) {
                        Ans[i] += 1<<j;
                        b = Up[j][b];
                    }
                }

                if (c == a || c == b) {
                    Ans[i]--;
                } else {
                    Question[a].push_back({b, i});
                }
            }
        }

        DFSOrder DFS(T.E);
        Enter = DFS.enter();
        Exit = DFS.exit();

        set<int> Void;
        dfs2(Void, 0, -1);

        for (int ans: Ans) {
            cout << ans << '\n';
        }
    }
};
