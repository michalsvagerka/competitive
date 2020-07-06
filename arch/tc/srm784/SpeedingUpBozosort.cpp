#include "../l/lib.h"
#include "../l/matrix.h"

typedef long double ld;

class SpeedingUpBozosort {
public:
    double expectedComparisons(vector <int> A, int numSwaps) {
        int N = A.size();
        if (N == 1) return 0;

        vector<int> B(A);
        sort(B.begin(),B.end());
        map<vector<int>, int> ID;
        vector<vector<int>> Q;
        do {
            ID[B] = Q.size();
            Q.push_back(B);
        } while (next_permutation(B.begin(),B.end()));

        int G = Q.size();
        Matrix<ld> M(G, G);
        for (int i = 0; i < G; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    vector<int> C = Q[i];
                    if (j != k) swap(C[j],C[k]);
                    M[i][ID[C]] += 1./(N*N);
                }
            }
        }

        if (numSwaps > 1) M = M.power(numSwaps);
        auto RR = M;//.transpose();

        vector<ld> Right(G, 0);
        Right[0] = 0;
        for (int i = 0; i < G; ++i) RR[0][i] = 0;
        for (int i = 0; i < G; ++i) {
            int c = 1;
            while (c < N-1 && Q[i][c-1] <= Q[i][c]) c++;
            Right[i] = -c;
            RR[i][i] -= 1;
        }

        auto Z = RR.solveFor(Right);
        return Z[ID[A]];
    }


    void solve(istream& cin, ostream& cout) {
        cout << expectedComparisons({1, 2, 3, 4},3) << endl;
        cout << expectedComparisons({1, 1, 2, 2, 2},5) << endl;
        cout << expectedComparisons({10, 0},1) << endl;
        cout << expectedComparisons({7, 4},47) << endl;
        cout << expectedComparisons({5, 3, 1, 4, 2},1) << endl;
        cout << expectedComparisons({5, 3, 1, 4, 2},2) << endl;
        cout << expectedComparisons({5, 3, 1, 4, 2},3) << endl;
        cout << expectedComparisons({5, 3, 1, 4, 2},4) << endl;
        cout << expectedComparisons({5, 3, 1, 4, 2},5) << endl;
        cout << expectedComparisons({1, 1, 2, 1},4) << endl;
        cout << expectedComparisons({1, 2, 3, 4, 5, 6}, 1000) << endl;
    }
};
