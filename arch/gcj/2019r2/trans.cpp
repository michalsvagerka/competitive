#include "../l/lib.h"
#include "../l/graph.h"
#include "../l/mod.h"

class trans {
public:

    vector<bool> Zero;
    vector<bool> Bounded;
    vector<vector<int>> E;
    vector<int> SCC, A;


    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int M; cin >> M;
            DirectedGraph G(M);
            vector<bool> Self(M, false);
            for (int i = 0; i < M; ++i) {
                int a, b; cin >> a >> b;
                --a; --b;
                G.addEdge(i, a);
                G.addEdge(i, b);
                Self[i] = a==i || b==i;
            }

            G.calcStronglyConnectedComponents();
            SCC = G.SCC;
            E = G.E;

            A.resize(M); cin >> A;

            vector<int> Perm = G.stronglyConnectedPermutation();
            map<int, vector<int>> Comps;
            vector<int> CompOrder;
            for (int p: Perm) {
                int c = G.SCC[p];
                if (Comps.count(c) == 0) {
                    CompOrder.push_back(c);
                }

                Comps[c].push_back(p);
            }
            reverse(CompOrder.begin(),CompOrder.end());

            vector<FieldMod> Ans(M, 0);
            Zero.assign(M, true);
            Bounded.assign(M, true);

            for (int cmp: CompOrder) {
                auto &PP = Comps[cmp];
                int p = PP[0];
                bool bnd = true;
                bool bndOut = true;
                bool zero = true;
                FieldMod tot = 0;
                for (int pp: PP) {
                    tot += A[pp] + Ans[pp];
                    if (A[pp] || !Zero[pp]) zero = false;
                    if (!Bounded[pp]) bnd = false;
                }

                if ((PP.size() >= 2 || Self[p]) && !zero) {
                    int a = 0, b = 0;
                    for (int pp: PP) {
                        for (int u: E[pp]) {
                            if (SCC[u] == SCC[pp]) ++a;
                            else ++b;
                        }
                    }
                    if (a > b) bnd = false;
                    bndOut = false;
                }

                if (!bnd) bndOut = false;

                for (int pp: PP) {
                    Zero[pp] = zero;
                    Bounded[pp] = bnd;
                    Ans[pp] = tot;
                }
                for (int pp: PP) {
                    for (int e: E[pp]) {
                        if (SCC[e] != SCC[pp]) {
                            if (!zero) Zero[e] = false;
                            Ans[e] += tot;
                            if (!bndOut) Bounded[e] = false;
                        }
                    }
                }
            }

            if (Bounded[0]) {
                cout << "Case #" << t+1 << ": " << Ans[0] << endl;
            } else {
                cout << "Case #" << t+1 << ": UNBOUNDED\n";
            }
        }
    }
};
