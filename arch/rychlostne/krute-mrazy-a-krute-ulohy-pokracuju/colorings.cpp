#include "../../../l/lib.h"
#include "../../../l/mod.h"

class colorings {
public:
    int N, M, C;
    vector<bool> Indep;
    set<int> Edges;
    vector<vector<int>> Trans;

    void gen(int b, int l, int r) {
        if (b == N) {
            if (Indep[r] && r != 0) {
                Trans[l].push_back(r);
            }
        } else {
            gen(b + 1, l, r);
            gen(b + 1, l|1<<b, r);
            gen(b + 1, l, r|1<<b);
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M >> C;
        Indep.resize(1<<N);
        Trans.resize(1<<N);
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int a,b; cin >> a >> b;
            E[a].push_back(b);
            E[b].push_back(a);
            Edges.insert(1<<a|1<<b);
        }

        for (int i = 0; i < N; ++i) {
            for (int a:E[i]) {
                for (int b:E[i]) {
                    if (a!=b) Edges.insert(1<<a|1<<b);
                }
            }
        }

        for (int i = 0; i < (1<<N); ++i) {
            Indep[i] = true;
            for (int edge:Edges) {
                if ((i&edge)==edge) {
                    Indep[i] = false;
                }
            }
        }

        gen(0,0,0);

        auto F = FieldMod::fact(1005);
        auto I = FieldMod::invfact(1005);
        FieldMod ans = 0;

        vector<FieldMod> R(1<<N, 0);
        R[0] = 1;
        for (int i = 0; i < N; ++i) {
            vector<FieldMod> Z(1<<N, 0);
            for (int j = 0; j < (1<<N); ++j) {
                if (R[j] != 0) {
                    for (int k : Trans[j]) {
                        Z[j|k] += R[j];
                    }
                }
            }
            if (i+1<=C) ans += Z[(1<<N)-1] * F[C] * I[i+1] * I[C-i-1];
            swap(R,Z);
        }

        cout << ans << endl;
    }
};
