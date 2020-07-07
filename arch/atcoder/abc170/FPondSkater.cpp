#include "../../../l/lib.h"

class FPondSkater {
public:
    void solve(istream& cin, ostream& cout) {
        int H, W, K; cin >> H >> W >> K;
        int X1, Y1, X2, Y2; cin >> X1 >> Y1 >> X2 >> Y2;
        vector<string> A(H); cin >> A;

        X1--; X2--; Y1--; Y2--;
        vector<pii> Q{{X1,Y1}};
        vector3<bool> U(4, H, W, false);
        vector2<int> D(H,W,10000000);
        D[X1][Y1] = 0;
        vector<pii> Dir{{1,0}, {0,1},{-1,0},{0,-1}};
        while (!Q.empty()) {
            vector<pii> P;

            for (int d = 0; d < 4; ++d) {
                if (d == 0) {
                    sort(Q.begin(),Q.end(),[](const pii&a, const pii&b) { return a.x > b.x; });
                } else if (d == 1) {
                    sort(Q.begin(),Q.end(),[](const pii&a, const pii&b) { return a.y > b.y; });
                } else if (d == 2) {
                    sort(Q.begin(),Q.end(),[](const pii&a, const pii&b) { return a.x < b.x; });
                } else if (d == 3) {
                    sort(Q.begin(),Q.end(),[](const pii&a, const pii&b) { return a.y < b.y; });
                }
                for (int i = 0; i < Q.size(); ++i) {
                    pii q = Q[i];
                    for (int j = 1; j <= K; ++j) {
                        int x = q.x + j * Dir[d].x;
                        int y = q.y + j * Dir[d].y;
                        if (x < 0 || x >= H || y < 0 || y >= W) break;
                        if (A[x][y] == '@') break;
                        if (U[d][x][y]) break;
                        U[d][x][y] = true;
                        if (D[x][y] > D[q.x][q.y] + 1) {
                            D[x][y] = D[q.x][q.y] + 1;
                            P.push_back({x, y});
                        }
                    }
                }
            }
            swap(P, Q);
        }
        cout << (D[X2][Y2] == 10000000 ? -1 :(D[X2][Y2])) << '\n';
    }
};
