#include "../l/lib.h"
#include "../l/util.h"

#define MASK(x) ((Remap[x]))

class DAbandoningRoads {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, A, B;
        cin >> N >> M >> A >> B;
        vector<vector<pii>> E(N);
        UnionFind U(N);
        for (int i = 0; i < M; ++i) {
            int a, b, c; cin >> a >> b >> c;
            --a; --b;
            E[a].push_back({b,c});
            E[b].push_back({a,c});
            if (c == A) U.unite(a,b);
        }

        vector<int> C(N), W(N);
        for (int i = 0; i < N; ++i) {
            W[i] = U.find(i);
            C[U.find(i)]++;
        }

        int cmp = 0;
        vector<int> Remap(N, -1);
        for (int i = 0; i < N; ++i) {
            if (C[i] >= 4) {
                Remap[i] = cmp++;
            }
        }
        vector<int> Mask(N);
        for (int i = 0; i < N; ++i) {
            int u = W[i];
            if (Remap[u] != -1) {
                Mask[i] = 1<<Remap[u];
            } else {
                Mask[i] = 0;
            }
        }
        
        vector2<int> D(N, 1<<cmp, int(1e9));
        D[0][Mask[0]] = 0;
        minheap<pair<int, pii>> H;
        H.push({0, {0,Mask[0]}});
        while (!H.empty()) {
            auto h = H.top(); H.pop();
            if (D[h.y.x][h.y.y] != h.x) continue;
            for (pii e: E[h.y.x]) {
                if (e.y == B && ((h.y.y & Mask[e.x]) != 0)) continue;
                if (e.y == B && W[e.x] == W[h.y.x]) continue;
                
                int nm = h.y.y | Mask[e.x];
                int nc = h.x + e.y;
                if (D[e.x][nm] > nc) {
                    D[e.x][nm] = nc;
                    H.push({nc, {e.x, nm}});
                }
            }
        }
        
        vector<int> Ans(N, int(1e9));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < (1<<cmp); ++j) {
                Ans[i] = min(Ans[i], D[i][j]);
            }
        }
        cout << Ans;
    }
};
