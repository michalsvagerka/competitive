#include "../../../l/lib.h"
#include "../../../l/mod.h"

class validsets {
public:
    int D,N;
    vector<vector<int>> E;
    vector<int> A;

    FieldMod solve(int u, int p, int lo, pii hi) {
        if (A[u] < lo || pii{A[u],u} > hi) return 1;

        FieldMod ans = 1;
        for (int v:E[u]) {
            if (v != p) {
                ans *= solve(v, u, lo, hi);
            }
        }
        return ans + 1;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> D >> N;
        A.resize(N);
        cin >> A;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        FieldMod ans = 0;
        for (int i = 0; i < N; ++i) {
            ans += solve(i, -1, A[i]-D, {A[i],i});
        }
        cout << ans-N << '\n';
    }
};
