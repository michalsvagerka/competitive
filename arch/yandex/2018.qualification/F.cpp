#include "../../../l/lib.h"
// #include "../l/mod.h"

class F {
public:
    vector<vector<int>> E;
    vector<pii> A;
    vector<int> Q;
    int N;

    int depth(int u, int p, int q) {
        int d = 0;
        int lo = 0;
        for (int v:E[u]) {
            if (v != p) {
                int cur = depth(v, u, q);
                d = max(d, cur);
                lo = min(lo, cur);
            }
        }
//        cerr << q << ' ' << u+1 << ' ' << d << ' ' << lo << endl;

        if (d >= q) {
            Q.push_back(u);
            return -q;
        } else if (d == 0 && lo < 0) {
            return lo + 1;
        } else if (lo < 0 && d + lo < 0) {
            return lo+1;
        } else {
            return d+1;
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 2) {
            cout << "1 2\n";
            return;
        }

        E.resize(N);
        A.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u,v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        int dist = bsl(0, N-1, [&](int k) {
            Q.clear();
            if (depth(0, -1, k) > 0) Q.push_back(0);
//            cerr << "Res " << k << ":" << Q;
            if (Q.size() > 2) return false;
            else {
                if (Q.empty()) {
                    A[k] = {0,1};
                } else if (Q.size() == 1) {
                    A[k] = {Q[0],Q[0]==0};
                } else {
                    A[k] = {Q[0],Q[1]};
                }

                return true;
            }
        });

//        cerr << "Distance " << dist << endl;
        cout << A[dist].x+1 << ' ' << A[dist].y+1 << endl;
    }
};
