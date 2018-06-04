#include "../../../l/lib.h"
#include "../../../l/avl.h"

class treeandqueries {
public:
    int N, M;
    vector<vector<int>> E;
    vector<int> C, Ans;
    vector<vector<pii>> Q;

    struct Val {
        Val(int color) {
            T.insert({1, color}, 0);
            Q[color] = 1;
        }

        Val *merge(Val *v) {
            if (T.size() < v->T.size()) {
                return v->merge(this);
            } else {
                for (pii q: v->Q) {
                    if (Q[q.x]) T.remove({Q[q.x],q.x});
                    Q[q.x] += q.y;
                    T.insert({Q[q.x], q.x}, 0);
                }
                return this;
            }
        }

        int answer(int k) {
            return T.size() - T.smaller({k,-1});
        }

        avl<pii, int> T;
        map<int, int> Q;
    };

    Val* dfs(int u, int p) {
        Val *x = new Val(C[u]);
        for (int v:E[u]) {
            if (v != p) {
                x = x->merge(dfs(v, u));
            }
        }

        for (pii&q:Q[u]) {
            Ans[q.y] = x->answer(q.x);
        }
        return x;
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        C.resize(N); cin >> C;
        E.resize(N);
        Q.resize(N);
        Ans.resize(M);

        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        for (int i = 0; i < M; ++i) {
            int v,k; cin >> v >> k;
            --v;
            Q[v].push_back({k,i});
        }

        dfs(0, -1);
        for (int ans: Ans) cout << ans << '\n';
    }
};
