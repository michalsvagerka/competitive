#include "../l/lib.h"
// #include "../l/mod.h"

class posadky {
public:
    int N, M;
    vector<vector<pii>> E;
    vector<pii> A, R;
    vector<bool> Z;
    int X;

    bool dfs(int u, pii value) {
        if (abs(value.y) > 200000000) return false;

        if (Z[u]) {
            if (A[u] == value) {
                return true;
            } else if (X) {
                return A[u].x * X + A[u].y == value.x * X + value.y;
            } else if (A[u].x == value.x) {
                return false;
            } else {
                int a = A[u].x - value.x;
                int b = value.y - A[u].y;
                if (b%a != 0) {
                    return false;
                } else {
                    X = b/a;
                    return X > 0;
                }
            }
        } else {
            Z[u] = true;
            A[u] = value;
            for (pii&v: E[u]) {
                if (!dfs(v.x, {-value.x, v.y-value.y})) {
                    return false;
                }
            }

            return true;
        }
    }

    bool check(int val, ostream&cout) {
        if (val <= 0) return false;

        vector<pii> Val(N);
        for (int i = 0; i < N; ++i) {
            Val[i] = {A[i].x * val + A[i].y,i};
        }
        sort(Val.begin(),Val.end());
        vector<int> Ans(N);

        for (int i = 0; i < N; ++i) {
            if (Val[i].x != R[i].x) return false;
            Ans[Val[i].y] = R[i].y;
        }

        cout << Ans;
        return true;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        R.resize(N);
        A.resize(N);
        X = 0;

        for (int i = 0; i < N; ++i) {
            cin >> R[i].x;
            R[i].y = i+1;
        }
        sort(R.begin(),R.end());

        int lowest = R[0].x;

        Z = vector<bool>(N, false);

        cin >> M;
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u;
            --v;
            E[u].push_back({v,w});
            E[v].push_back({u,w});
        }

        if (dfs(0, {1,0})) {
            if (X) {
                if (check(X, cout)) return;
            } else {
                for (int i = -1; i <= 1; i += 2) {
                    int lo = 1000000000;
                    for (int j = 0; j < N; ++j) {
                        if (A[j].x == i) {
                            lo = min(lo, A[j].y);
                        }
                    }

                    if (i == -1) {
                        if (check(lo - lowest, cout)) return;
                    } else {
                        if (check(lowest - lo, cout)) return;
                    }
                }

            }
        }

        cout << "impossible\n";

    }
};
