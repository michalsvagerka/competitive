#include "../../../l/lib.h"
#include "../../../l/geo.h"

class ncpc12e {
public:
    void solve(istream& cin, ostream& cout) {
        int J,R,D;
        cin >> J >> R >> D;
        double DD = D * (1 + 5e-7);
        vector<Point<ll>> C(J); cin >> C;
        vector<vector<int>> E(J);
        for (int i = 0; i < R; ++i) {
            int a, b; cin >> a >> b; --a; --b;
            E[a].push_back(b);
        }

        vector3<double> A(J,J,J);
        for (int i = 0; i < J; ++i) {
            for (int j = 0; j < J; ++j) {
                for (int k = 0; k < J; ++k) {
                    A[i][j][k] = angle(C[i],C[j],C[k]);
                }
            }
        }

        vector<double> F(J, 1e30);
        minheap<pair<double,int>> Q;
        F[0] = 0;
        Q.push({0.0, 0});

        while (!Q.empty()) {
            auto q = Q.top();
            Q.pop();
            if (F[q.y] < q.x * (1 - 1e-7)) continue;

            for (int w: E[q.y]) {
                double len = q.x + C[w].distance(C[q.y]);
                if (F[w] > len * (1 + 1e-7)) {
                    F[w] = len;
                    Q.push({len, w});
                }
            }
        }

        if (F[J-1] > DD) {
            cout << "Impossible\n";
            return;
        }



        double ans = bsld(0.0, PI, [&](double allowedTurn) {
            vector2<double> D(J,J, 1e30);
            minheap<pair<double,pii>> Q;
            for (int v: E[0]) {
                D[0][v] = C[0].distance(C[v]);
                Q.push({D[0][v], {0,v}});
            }

            while (!Q.empty()) {
                auto q = Q.top();
                Q.pop();
                if (D[q.y.x][q.y.y] < q.x * (1 - 1e-7)) continue;
                if (q.y.y == J - 1) {
                    return q.x <= DD;
                }

                for (int w: E[q.y.y]) {
                    if (A[q.y.y][w][q.y.x] + allowedTurn >= PI) {
                        double len = q.x + C[w].distance(C[q.y.y]);
                        if (D[q.y.y][w] > len * (1 + 1e-7)) {
                            D[q.y.y][w] = len;
                            Q.push({len, {q.y.y, w}});
                        }
                    }
                }
            }

            return false;
        }, 1e-7);

        cout << fixed << setprecision(15) << 180 * ans / PI << endl;
    }
};
