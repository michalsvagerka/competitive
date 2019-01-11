#include "../l/lib.h"
// #include "../l/mod.h"

class ASumInTheTree {
public:
    int N;
    vector<vector<int>> E;
    vector<int> S, A;


    void dfs(int u, int s) {
        if (S[u] == -1) {
            if (E[u].empty()) {
                A[u] = 0;
                return;
            }

            int lo = 1e9;
            for (int v : E[u]) {
                lo = min(lo, S[v] - s);
            }

            A[u] = lo;


        } else {

            A[u] = S[u] - s;
        }

        for (int v : E[u]) {
            dfs(v, s + A[u]);
        }

    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        S.resize(N);
        A.resize(N);
        for (int i = 1; i < N; ++i) {
            int p; cin >> p;
            E[p-1].push_back(i);
        }

        cin >> S;

        dfs(0, 0);
        ll tot = 0;
        for (int a:A) {
            if (a < 0) {
                cout << "-1\n";
                return;
            }
            tot += a;
        }
     
        cout << tot << endl;
    }
};
