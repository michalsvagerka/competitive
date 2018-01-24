#include "../l/lib.h"
// #include "../l/mod.h"

int M = 100;

class chocogame2 {
public:
    void solve(istream& cin, ostream& cout) {
        vector2<int> D(M+1,M+1,0);
        for (int i = 1; i <= M; ++i) {
            D[i][1] = i-1;
            D[1][i] = -i+1;
        }

        for (int i = 2; i <= M; ++i) {
            for (int j = 2; j <= M; ++j) {
                D[i][j] = D[i/2][j/2];
            }
        }

        int N; cin >> N;
        int g = 0;
        for (int i = 0; i < N; ++i) {
            int a,b; cin >> a >> b;
            g += D[a][b];
        }

        if (g > 0) {
            cout << "Rowan\n";
        } else if (g < 0) {
            cout << "Colette\n";
        } else {
            cout << "second\n";
        }
    }
};
