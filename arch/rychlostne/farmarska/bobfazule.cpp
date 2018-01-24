#include "../l/lib.h"
// #include "../l/mod.h"

class bobfazula {
public:
    ui N, F, G, M;
    vector<vector<ui>> E;
    vector<ui> P,S,A,B;

    bool dfs(ui u, ui p) {
        P.push_back(u);
        if (u == G) return true;
        for (ui v:E[u]) if (v!=p && dfs(v, u)) return true;
        P.pop_back();
        return false;
    }

    ui maxLen(ui u, ui ig1, ui ig2 = 200000) {
        ui ans = 0;
        for (ui v:E[u]) if (v!=ig1 && v!=ig2) ans = max(ans, maxLen(v,u));
        return ans+1;
    }

    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            ui u,v; cin >> u >> v;
            --u; --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        cin >> F >> G;
        --F; --G;
        dfs(F, N);
        M = P.size();

        S.resize(M);
        S[0] = maxLen(P[0], P[1]);
        S[M-1] = maxLen(P[M-1], P[M-2]);
        for (ui i = 1; i < M-1; ++i) {
            S[i] = maxLen(P[i], P[i-1], P[i+1]);
        }

        A.resize(M); B.resize(M);
        A[0] = S[0];
        B[M-1] = S[M-1];

        for (ui i = 1; i < M; ++i) {
            A[i] = max(A[i-1], i+S[i]);
            B[M-1-i] = max(B[M-i], i+S[M-1-i]);
        }

        ui ans = 0;
        for (ui i = 1; i < M; ++i) {
            ans = max(ans, min(A[i - 1], B[i]));
        }
        cout << ans << endl;
    }
};
