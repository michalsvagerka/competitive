#include "../l/lib.h"

class HTilesPlacement {
public:
    void bip(int u, int p, int q, const vector<vector<int>> &E, vector<int> &Ans) {
        Ans[u] = q;
        for (int v : E[u]) if (v != p) bip(v, u, 3-q, E, Ans);
    }

    bool fail;
    int N, K;
    vector<vector<int>> E;
    vector<int> D;

    bool path(int u, int p, int t, vector<int> &P) {
        if (u == t) {
            P.push_back(u);
            return true;
        }

        P.push_back(u);
        for (int v : E[u]) if (v != p) {
            if (path(v, u, t, P)) return true;
        }
        P.pop_back();
        return false;
    }

    int depth(int u, int p) {
        D[u] = 0;
        for (int v : E[u]) if (v != p) D[u] = max(D[u], depth(v, u) + 1);
        return D[u];
    }

    pii dist(int u, int p) {
        pii ans = {0, u};
        for (int v : E[u]) if (v != p) ans = max(ans, dist(v, u));
        ans.x++;
        return ans;
    }

    void fill(int u, int p, int d, int s, vector<int> &Ans) {
        Ans[u] = d;
        for (int v : E[u]) if (v != p) fill(v, u, (d+s+K)%K, s, Ans);
    }

    void dfs(int u, int p, int top) {
        vector<int> A, V;
        for (int v : E[u]) if (v != p) { V.push_back(v); A.push_back(D[v] + 1); }
        int M = A.size();
        vector<int> S(M+1, 0), P(M+1, 0);
        for (int i = 0; i < M; ++i) {
            P[i+1] = max(P[i], A[i]);
            S[M-i-1] = max(S[M-i], A[M-1-i]);
        }

        if (top != 0) A.push_back(top);
        if (A.size() >= 3) {
            sort(A.begin(),A.end());
            reverse(A.begin(),A.end());
            if (A[1] + A[2] + 1 >= K) fail = true;
        }
        
        for (int i = 0; i < M; ++i) {
            dfs(V[i], u, 1 + max(top, max(P[i], S[i+1])));
        }
    }



    void solve(istream& cin, ostream& cout) {
        cin >> N >> K;
        E.resize(N);
        D.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        fail = false;
        if (K == 2) {
            vector<int> Ans(N, -1);
            bip(0, -1, 1, E, Ans);
            cout << "Yes\n" << Ans;
        } else {
            depth(0, -1);
            dfs(0, -1, 0);
            if (fail) {
                cout << "No\n";
                return;
            }
            pii q = dist(0, -1);
            pii r = dist(q.y, -1);
            vector<int> P;
            path(q.y, -1, r.y, P);

            vector<int> Ans(N, -1);
            for (int i = 0; i < P.size(); ++i) {
                Ans[P[i]] = i%K;
            }

            for (int i = 0; i < P.size(); ++i) {
                int u = P[i];
                for (int v: E[u]) if (Ans[v] == -1) {
                    int s = (2*i < P.size()) ? -1 : 1;
                    fill(v, u, (Ans[u]+K+s)%K, s, Ans);
                }
            }
            for (int&a: Ans) ++a;

            cout << "Yes\n" << Ans;
        }
    }
};
