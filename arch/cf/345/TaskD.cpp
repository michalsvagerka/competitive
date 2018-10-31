#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<int> H(N); cin >> H;
    vector<vector<int>> F(1), G(1);
    vector<int> LF(N), LB(N);
    for (int i = 0; i < N; ++i) {
        int z = bsh(0, int(F.size())-1, [&](int j) { return j == 0 || H[F[j].back()] < H[i]; });
        if (z == F.size() - 1) F.push_back({});
        LF[i] = z+1;
        F[z+1].push_back(i);
    }

    for (int i = N-1; i >= 0; --i) {
        int z = bsh(0, int(G.size())-1, [&](int j) { return j == 0 || H[G[j].back()] > H[i]; });
        if (z == G.size() - 1) G.push_back({});
        LB[i] = z+1;
        G[z+1].push_back(i);
    }

    vector<int> C(N+1, 0);
    for (int i = 0; i < N; ++i) {
        if (LB[i] + LF[i] == F.size()) C[LF[i]]++;
    }

    vector<pair<pii, int>> Q(M);
    for (int i = 0; i < M; ++i) {
        Q[i].y = i;
        cin >> Q[i].x;
        Q[i].x.x--;
    }
    
    sort(Q.begin(), Q.end());
    vector<int> Ans(M, int(F.size())-2);

    vector<int> PX(F.size(), -1), PY(G.size());
    for (int i = 0; i < G.size(); ++i) PY[i] = G[i].size()-1;

    int l = -1, r = -1;
    for (auto q: Q) {
        while (l < q.x.x-1) PX[LF[++l]]++;
        while (r < q.x.x) PY[LB[++r]]--;

        int a = bsh(0, int(F.size())-1, [&](int j) {
            return j == 0 || (PX[j] != -1 && H[F[j][PX[j]]] < q.x.y);
        });

        int b = bsh(0, int(F.size())-1, [&](int j) {
            return j == 0 || (PY[j] != -1 && H[G[j][PY[j]]] > q.x.y);
        });

        Ans[q.y] = max(Ans[q.y], a + b + 1);
        
        if (LB[q.x.x] + LF[q.x.x] != F.size() || C[LF[q.x.x]] > 1) {
            Ans[q.y] = max(Ans[q.y], int(F.size())-1);
        }
    }

    for (int &ans: Ans) cout << ans << '\n';
}
};
