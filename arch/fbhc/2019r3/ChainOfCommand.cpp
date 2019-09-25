#include "../l/lib.h"
#include "../l/mod.h"
#include "../l/fenwick.h"

class ChainOfCommand {
public:
    vector<vector<int>> E;
    vector<int> LO;
    int N;
    Fenwick<int> F, G;
    vector<int> Ans, Bans;
    
    int lo(int u) {
        LO[u] = u;
        for (int v : E[u]) {
            LO[u] = min(LO[u], lo(v));
        }
        return LO[u];
    }

    void dfs(int u) {
//        Bans[u] -= G.sum(u);
//        G.add(u, 1);
        
        Ans[u] += F.sum(u); // no of ancestors of u available at time < u
        
        vector<int> X;
        for (int v : E[u]) {
            X.push_back(LO[v]);
        }
        int W = E[u].size();
        vector<int> Pref(W+1, N), Suf(W+1, N);
        for (int i = 0; i < W; ++i) Pref[i+1] = min(Pref[i], X[i]);
        for (int i = 0; i < W; ++i) Suf[W-i-1] = min(Suf[W-i], X[W-i-1]);
        for (int i = 0; i < W; ++i) {
            int d = min(Pref[i], Suf[i+1]);
            d = min(d, u);
            Bans[d] -= G.sum(d);
            F.add(d, 1);
            dfs(E[u][i]);
            F.add(d, -1);

            Bans[d] += G.sum(d);
        }
        
        G.add(u, 1);
        
//        Bans[u] += G.sum(u);
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> N;
            vector<int> P(N); cin >> P;
            for (int &p: P) --p;
            E.clear();
            E.resize(N);
            int root = 0;
            for (int i = 0; i < N; ++i) {
                if (P[i] != -1) {
                    E[P[i]].push_back(i);
                } else {
                    root = i;
                }
            }

            LO.resize(N);
            lo(root);
            Ans.assign(N, 0);
            Bans.assign(N, 0);
            F = Fenwick<int>(N+1, 0);
            G = Fenwick<int>(N+1, 0);

            dfs(root);
            
            vector<FieldMod> S(N, 0);
            for (int i = 0; i < N; ++i) {
                S[i] = Ans[i] + Bans[i] + 1;
            }
            for (int i = 1; i < N; ++i) {
                S[i] += S[i-1];
            }
//            cout << Ans << Bans;
//            cout << S;
            
            FieldMod ans = 1;
            for (auto s: S) ans *= s;
//            for (int i = 0; i < N; ++i) {
//                int cur = 0;
//                for (int j = 0; j <= i; ++j) {
//                    int prev = -1;
//                    int k = j;
//                    while (k != -1) {
//                        if (k <= i) ++cur;
//                        else {
//                            for (int l : E[k]) {
//                                if (l != prev && LO[l] <= i) {
//                                    ++cur;
//                                    break;
//                                }
//                            }
//                        }
//                        prev = k;
//                        k = P[k];
//                    }
//                }
//                ans *= cur;
//            }

            cout << "Case #" << t+1 << ": " << ans << endl;
        }
    }
};
