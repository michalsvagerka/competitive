#include "../l/lib.h"

class TAASquares {
public:
    vector <string> construct(int N) {
        if (N % 2 == 0) {
            vector<string> A(N, string(N, '0'));
            for (int i = 0; i < N; ++i) A[i][0] = '2';
            for (int i = 0; i < N; ++i) {
                for (int j = 1; j+i < N-1; ++j) {
                    A[i][j] = '2';
                }
                if (i < N/2) A[i][N-i-1] = '1'; else A[i][N-i-1] = '2';
            }
            return A;
        } else {
            vector<string> A(N, string(N, '0'));
            for (int i = 0; i < N; ++i) A[i][0] = '1';
            for (int i = 0; i < N; ++i) {
                for (int j = 1; j+i < N; ++j) {
                    A[i][j] = '2';
                }
            }
            return A;
        }
    }
    void solve(istream& cin, ostream& cout) {
        for (int i = 1; i <= 10; ++i) {
            for (string s: construct(i)) {
                cout << s << endl;
            }
            cout << endl;
        }
    }
};
