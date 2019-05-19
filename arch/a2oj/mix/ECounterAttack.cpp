#include "../l/lib.h"
// #include "../l/mod.h"

class ECounterAttack {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
//        vector<set<int>> S(N);
        unordered_set<pii> S;
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            S.insert({min(a,b),max(a,b)});
//            S[a].insert(b);
//            S[b].insert(a);
        }

        vector<int> C(N);
        set<int> V;
        vector<vector<int>> U(N);
        for (int i = 0; i < N; ++i) {
            C[i] = i;
            U[i] = {i};
            V.insert(i);
        }

        for (int i = 0; i < N; ++i) {
            int c = C[i];
            vector<int> MergeWith;
            for (int v : V) {
                if (v != c) {
                    for (int w: U[v]) {
                        if (w > i) {
                            auto it = S.find({i,w});
                            if (it == S.end()) {
                                MergeWith.push_back(v);
                                break;
                            }
                        }
                        //else S[i].erase(it);
                    }
                }
            }

            for (int m: MergeWith) {
                if (U[m].size() > U[c].size()) swap(m, c);
                for (int u: U[m]) {
                    C[u] = c;
                    U[c].push_back(u);
                }
                U[m].clear();
                V.erase(m);
            }
        }

        cout << V.size() << endl;
        for (int i = 0; i < N; ++i) {
            if (!U[i].empty()) {
                cout << U[i].size();
                for (int u: U[i]) cout << ' ' << u+1;
                cout << '\n';
            }
        }
    }
};
