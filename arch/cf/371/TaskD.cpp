#include "../l/lib.h"
// #include "../l/mod.h"

int RMQ[11][1000][11][1000];

class TaskD {
public:
    
void solve(istream& cin, ostream& cout) {
    
    int N, M;
    cin >> N >> M;
    vector2<int> X(N, M), P(N + 1, M + 1, 0), S(N, M);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> X[i][j];
            P[i + 1][j + 1] = P[i + 1][j] + P[i][j + 1] - P[i][j] + X[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            S[i][j] = bsh(0, min(N - i, M - j), [&](int s) {
                return P[i + s][j + s] - P[i + s][j] - P[i][j + s] + P[i][j] == s * s;
            });
        }
    }

    // TODO: Extract 2D RMQ from here
    for(int ir = 0; ir < N; ir++)
    {
        for(int ic=0; ic < M; ic++)
            RMQ[0][ir][0][ic] = S[ir][ic];
        
        for (int jc = 1; jc <= 10; jc++)
            for (int ic = 0; ic+(1<<(jc-1)) < M; ic++)
                RMQ[0][ir][jc][ic] = max(RMQ[0][ir][jc-1][ic], RMQ[0][ir][jc-1][ic+(1<<(jc-1))]);
    }
    for (int jr = 1; jr <= 10; jr++) {
        for (int ir = 0; ir < N; ir++)
            for (int jc = 0; jc <= 10; jc++)
                for (int ic = 0; ic < M; ic++)
                    RMQ[jr][ir][jc][ic] = max(RMQ[jr-1][ir][jc][ic], RMQ[jr-1][ir+(1<<(jr-1))][jc][ic]);
    }

    
    auto query = [&](int x1, int y1, int x2, int y2) {
        int lenx=x2-x1+1;
        int kx=logceil(lenx)-1;
        int leny=y2-y1+1;
        int ky=logceil(leny)-1;

        int max_R1 = max(RMQ[kx][x1][ky][y1] , RMQ[kx][x1][ky][y2+1-(1<<ky)] );
        int max_R2 = max(RMQ[kx][x2+1-(1<<kx)][ky][y1], RMQ[kx][x2+1-(1<<kx)][ky][y2+1-(1<<ky)] );
        return max(max_R1, max_R2);
    };

    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        cout << bsh(0, 1+min(x2-x1, y2-y1), [&](int s) {
             return query(x1, y1, x2 - s + 1, y2 - s + 1) >= s;
        }) << '\n';
    }
    
}
};
