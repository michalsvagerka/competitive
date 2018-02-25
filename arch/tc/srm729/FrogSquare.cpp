#include "../../../l/lib.h"
#include "../../../l/geo.h"

class FrogSquare {
public:

    int minimalJumps(int n, int d, int sx, int sy, int tx, int ty) {
        Point<int> S{sx,sy}, T{tx,ty};
        if (S == T) {
            return 0;
        }

        vector<Point<int>> P{S};
        for (int i = 0; i < n; ++i) {
            P.emplace_back(0,i);
            P.emplace_back(n-1,i);
            P.emplace_back(i,0);
            P.emplace_back(i,n-1);
        }

        P.push_back(T);
        int M = P.size();
        vector<vector<int>> E(M);
        for (int i = 0; i < M; ++i) {
            for (int j = i+1; j < M; ++j) {
                if (P[i].squaredDistance(P[j]) >= d*d) {
                    E[i].push_back(j);
                    E[j].push_back(i);
                }
            }
        }

        vector<int> D(M, 1e8);
        D[0] = 0;
        vector<int> Q{0};
        while (!Q.empty()) {
            vector<int> R;
            for (int q:Q) {
                for (int v:E[q]) {
                    if (v == M-1) {
                        return D[q]+1;
                    }
                    int dd = D[q] + 1;
                    if (D[v] > dd) {
                        D[v] = dd;
                        R.push_back(v);
                    }
                }
            }
            swap(R,Q);
        }

        return -1;
    }

    void solve(istream& cin, ostream& cout) {
        int n, d, sx, sy, tx, ty;
        cin >> n >> d >> sx >> sy >> tx >> ty;
        cout << minimalJumps(n, d, sx, sy, tx, ty) << '\n';
    }
};
