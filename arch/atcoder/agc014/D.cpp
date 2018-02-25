#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<set<int>> E(N);
        vector<int> C(N, 0);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].insert(v);
            E[v].insert(u);
            C[u]++;
            C[v]++;
        }

        vector<bool> H(N, false);
        vector<int> R;
        for (int i = 0; i < N; ++i) {
            if (C[i] == 1) {
                R.push_back(i);
            }
        }

        for (int r = 0; r < R.size(); ++r) {
            if (C[R[r]] == 0) {
                if (H[R[r]]) continue;
                cout << "First\n";
                return;
            }
            int p = *E[R[r]].begin();
//            cerr << "Coloring " << R[r]+1 << ' ' << p+1 << ' ' << C[R[r]] << endl;
            if (H[p]) {
                cout << "First\n";
                return;
            }

            H[p] = H[R[r]] = true;
            C[p] = 0;
            for (int w: E[p]) {
                E[w].erase(p);
                if (--C[w] == 1) {
//                    cerr << "Adding " << w+1 << endl;
                    R.push_back(w);
                }
            }
            E[p].clear();
        }

        cout << "Second\n";
    }
};
