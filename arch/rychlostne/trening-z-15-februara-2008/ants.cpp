#include "../l/lib.h"
#include "../l/hungary.h"

class ants {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> M(N), D(N);
        for (int i = 0; i < N; ++i) {
            cin >> M[i].x >> M[i].y;
        }

        for (int i = 0; i < N; ++i) {
            cin >> D[i].x >> D[i].y;
        }

        vector2<double> Q(N,N,0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                Q[i][j] = -sqrt((M[i].x-D[j].x)*(M[i].x-D[j].x)+(M[i].y-D[j].y)*(M[i].y-D[j].y));
            }
        }

        Hungary<double> H(Q);
        H.hungarian();
        for (int z:H.xy) cout << z+1 << '\n';
    }
};
