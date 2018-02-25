#include "../../../l/lib.h"
// #include "../l/mod.h"

class StonesOnATree {
public:
    vector<vector<int>> E;
    int N;
    vector<int> W;

    int best(int u) {
        int ans;
        if (E[u].size() == 0) {
            ans = W[u];
        } else if (E[u].size() == 1) {
             ans = max(W[u] + W[E[u][0]], best(E[u][0]));
        } else {
            vector<int> C;
            for (int v:E[u]) {
                C.push_back(best(v));
            }

//            ans = W[u] + W[E[u][0]] + W[E[u][1]];
            int left = max(C[0] + W[E[u][1]], C[1]);
            int right = max(C[1] + W[E[u][0]], C[0]);
            ans = min(left, right);
            ans = max(ans,  W[u] + W[E[u][0]] + W[E[u][1]]);
//            ans = max(ans, C[0] + W[E[u][1]]);
//            ans = max(ans, C[1] + W[E[u][0]]);

        }
//        cerr << u << ' ' << ans << endl;
        return ans;
    }

    int minStones(vector <int> p, vector <int> w) {
        W = w;
        N = w.size();
        E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            E[p[i]].push_back(i+1);
        }
//        cerr << E;

        return best(0);
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N-1), W(N);
        cin >> P >> W;
        cout << minStones(P,W);
    }
};
