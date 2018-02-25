#include "../../../l/lib.h"
#include "../../../l/util.h"

class TaskF {
public:
    int N;
    vector<int> A,B;
    vector<ll> Ans;
    vector<vector<int>> E;

    typedef Envelope::Lower<ll> EL;

    EL* dfs(int u, int p) {
        vector<EL*> Q;
        for (int v:E[u]) {
            if (v!=p) {
                Q.push_back(dfs(v, u));
            }
        }
        for (int i = 1; i < Q.size(); ++i) {
            if (Q[i]->size() > Q[0]->size()) {
                swap(Q[i],Q[0]);
            }
        }

        if (Q.empty()) {
            Ans[u] = 0;
            Q.push_back(new EL());
        } else {
            for (int i = 1; i < Q.size(); ++i) {
                for (auto q:*Q[i]) {
                    Q[0]->insert_line(-q.m, -q.b);
                }
            }
            Ans[u] = (*Q[0])[A[u]];
        }

        Q[0]->insert_line(B[u],Ans[u]);
        return Q[0];
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        A.resize(N); B.resize(N); E.resize(N); Ans.resize(N);
        cin >> A >> B;
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        dfs(0, -1);
        cout << Ans << endl;
    }
};
