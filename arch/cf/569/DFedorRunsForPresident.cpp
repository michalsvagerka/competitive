#include "../l/lib.h"
#include "../l/envelope.h"

class DFedorRunsForPresident {
public:
    ll N;
    vector<vector<int>> E;
    vector<ll> S;
    ll ans;


    ll size(int u, int p) {
        S[u] = 1;
        for (int v : E[u]) if (v != p) S[u] += size(v, u);
        return S[u];
    }

    ll solve(int u, int p) {
        ll up = S[u] * (S[u] - 1) / 2;
        ans = min(ans, S[u] * (S[u] - 1) / 2 + (N-S[u]) * (N-S[u]+1)/2);
        vector<pair<ll,ll>> Q;
        for (int v : E[u]) {
            if (v != p) {
                ll x = solve(v, u);
                Q.push_back({x + (S[v] - (2*N-1)) * S[v] / 2, S[v]});
                up = min(up, x + (S[u] - S[v])*(S[u]-S[v]-1)/2);
                ans = min(ans, x + (N-S[v]) * (N-S[v]-1)/2);
            }
        }


        int M = Q.size();
//        for (int i = 0; i < M; ++i) {
//            ll cur = 10000;
//            for (int j = 0; j < i; ++j) {
//                ll c = N * (N-1)/2 + Q[i].x + Q[j].x + Q[i].y * Q[j].y;
//                cur = min(cur, c);
//            }
//            cerr << cur << endl;
//        }

        Envelope::Lower<ll> Env;
        for (int i = 0; i < M; ++i) {
            if (!Env.empty()) {
//                cerr << "best " << Q[i].y << ' ' << Env[Q[i].y] + Q[i].x << endl;
                ans = min(ans, Env[Q[i].y] + Q[i].x);
            }

//            cerr << "add line " << Q[i].x << ' ' << N * (N-1)/2 + Q[i].x << endl;
            Env.insert_line(Q[i].y, N * (N-1)/2 + Q[i].x);
//            for (int j = i+1; j < M; ++j) {
//                ll c = N * (N-1)/2 + Q[i].x + Q[j].x + Q[i].y * Q[j].y;
//                ans = min(ans, c);
//            }
        }

        return up;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        ans = N*(N-1)/2;

        E.resize(N);
        S.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        size(0, -1);
        solve(0, -1);

        cout << N*(N-1) - ans << '\n';
    }
};
