#include "../../../l/lib.h"
// #include "../l/mod.h"

class BrownieGame {
public:
/*
 * vector2<int> D(M+1,M+1,0);
        for (int i = 1; i <= M; ++i) {
            D[i][1] = i-1;
            D[1][i] = -i+1;
        }

        for (int i = 2; i <= M; ++i) {
            for (int j = 2; j <= M; ++j) {
                D[i][j] = D[i/2][j/2];
            }
        }
 */

    int value(int r, int c) {
        if (r == 1) return c-1;
        if (c == 1) return -r+1;
        return value(r/2,c/2);
    }

    vector <int> HowToCheat(int n, vector <int> r, vector <int> c) {
//        for (int i = 1; i < 10; ++i) {
//            for (int j = 1; j < 10; ++j) {
//                cout << value(i,j) << ' ';
//            }
//            cout << endl;
//        }

        int g = 0;
        for (int i = 0; i < n; ++i) {
            g += value(r[i],c[i]);
        }

        return {max(0,g),max(0,g+1)};
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> R(N),C(N);
        cin >> R >> C;
        cout << HowToCheat(N, R, C);
    }
};
