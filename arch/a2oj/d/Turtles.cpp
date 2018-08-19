#include "../l/lib.h"
 #include "../l/mod.h"

class Turtles {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<string> S(N); cin >> S;

    vector2<FieldMod> Z(2, 2, 0);
    for (int x = 0; x < 2; ++x) {
        vector2<FieldMod> C(N, M, 0);
        C[x][1-x] = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (S[i][j] == '#') continue;
                if (i != 0) C[i][j] += C[i - 1][j];
                if (j != 0) C[i][j] += C[i][j - 1];
            }
        }

        Z[x][0] = C[N-2][M-1];
        Z[x][1] = C[N-1][M-2];
    }
    cout << (S[1][0] == '.' && S[0][1] == '.' ? Z[0][0] * Z[1][1] - Z[0][1] * Z[1][0] : 0) << endl;
}
};
