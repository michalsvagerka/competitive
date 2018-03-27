#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    int N1,N2;
    vector<vector<int>> E, F;

    void euler(const vector<vector<int>> &E, vector<int> &out, int u, int d) {
        out.push_back(d);
        for (int v:E[u]) {
            euler(E,out,v, d+1);
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N1;
        E.resize(N1);
        for (int i = 1; i < N1; ++i) {
            int p; cin >> p; --p;
            E[p].push_back(i);
        }
        cin >> N2;
        F.resize(N2);
        for (int i = 1; i < N2; ++i) {
            int p; cin >> p; --p;
            F[p].push_back(i);
        }

        vector<int> A,B;
        euler(E, A, 0, 0);
        euler(F, B, 0, 0);

        vector2<int> D(N1+1,N2+1,0);
        for (int i = 0; i <= N1; ++i) {
            for (int j = 0; j <= N2; ++j) {
                if (i != N1 && j != N2 && A[i] == B[j]) {
                    D[i+1][j+1] = max(D[i+1][j+1], D[i][j] + 1);
                }
                if (i!=N1) D[i+1][j] = max(D[i+1][j], D[i][j]);
                if (j!=N2) D[i][j+1] = max(D[i][j+1], D[i][j]);
            }
        }
        cout << N1 + N2 - 2*D[N1][N2] << endl;
    }
};
