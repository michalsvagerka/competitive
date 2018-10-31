#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:

    vector<vector<int>> Ans, LO;
    vector<vector<bool>> V;
    map<int, vector<pii>> EA, EB;
    vector<int> MA, MB, UA, UB;

    int mx(pii x) {
        if (V[x.x][x.y]) return 0;
        V[x.x][x.y] = true;
        int ret = LO[x.x][x.y];

        if (UA[x.x] == 2) {
            UA[x.x] = 1;
            for (pii e: EA[x.x]) ret = max(ret, mx(e));

        }

        if (UB[x.y] == 2) {
            UB[x.y] = 1;
            for (pii e: EB[x.y]) ret = max(ret, mx(e));
        }

        return ret;
    }


    void assign(pii x, int v) {
        if (Ans[x.x][x.y]) return;

        Ans[x.x][x.y] = v;
        MA[x.x] = v;
        MB[x.y] = v;

        if (UA[x.x] == 1) {
            UA[x.x] = 0;
            for (pii e: EA[x.x]) assign(e, v);
        }

        if (UB[x.y] == 1) {
            UB[x.y] = 0;
            for (pii e: EB[x.y]) assign(e, v);
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<int> A(N, M);
        Ans = vector2<int>(N, M, 0);
        LO = vector2<int>(N, M, 0);
        V = vector2<bool>(N, M, false);

        cin >> A;
        map<int, vector<pii>> Q;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                Q[A[i][j]].push_back({i,j});
            }
        }
        MA.assign(N, 0);
        MB.assign(M, 0);
        UA.assign(N, 0);
        UB.assign(M, 0);

        for (auto&q: Q) {
            EA.clear(); EB.clear();

            for (auto e:q.y) {
                UA[e.x] = 2;
                UB[e.y] = 2;
                EA[e.x].push_back(e);
                EB[e.y].push_back(e);
                LO[e.x][e.y] = 1 + max(MA[e.x], MB[e.y]);
            }

            for (auto e:q.y) {
                if (!V[e.x][e.y]) {
                    int put = mx(e);
                    assign(e, put);
                }
            }
        }
        for (auto &ans: Ans) cout << ans;
    }
};
