#include "../../../l/lib.h"
// #include "../l/mod.h"

class ncpc12j {
public:

    vector<vector<int>> E;
    vector<int> C, R, T;

    vector<int> solve(int u) {
        vector<int> Q(C[u]+1, 0);
        if (R[u] <= C[u]) Q[R[u]] = 1;
        for (int v : E[u]) {
            auto A = solve(v);
            vector<int> S(C[u]+1, 0);
            for (int i = 0; i <= C[v]; ++i) {
                for (int j = 0; j + i <= C[u]; ++j) {
                    S[i+j] = max(S[i+j], A[i] + Q[j]);
                }
            }
            swap(Q,S);
        }
        return Q;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        E.resize(N);
        C.resize(N);
        R.resize(N);
        for (int i = 0; i < N; ++i) {
            int p,c,r;
            cin >> p >> r >> c;
            if (p == 0) T.push_back(i);
            else E[p-1].push_back(i);
            R[i] = r;
            C[i] = c;
        }

        int ans = 0;
        for (int t: T) {
            auto A = solve(t);
            ans += *max_element(A.begin(),A.end());
        }
        cout << ans << '\n';
    }
};
