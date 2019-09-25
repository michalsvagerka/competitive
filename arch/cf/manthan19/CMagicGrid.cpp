#include "../l/lib.h"

class CMagicGrid {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<int> A(N, N, 0);
        for (int i = 0; i < N/4; ++i) {
            for (int j = 0; j < N/4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    for (int l = 0; l < 4; ++l) {
                        A[4*i+k][4*j+l] = 16*(i*(N/4)+j) + 4*k + l;
                    }
                }
            }
        }
        
        for (auto&a: A) cout << a;

//        for (int i = 0; i < N; ++i) {
//            int a = 0;
//            for (int j = 0; j < N; ++j) {
//                a ^= A[i][j];
//            }
//            if (a != 0) {
//                cout << "row " << i << endl;
//            }
//        }
//
//
//        for (int i = 0; i < N; ++i) {
//            int a = 0;
//            for (int j = 0; j < N; ++j) {
//                a ^= A[j][i];
//            }
//            if (a != 0) {
//                cout << "column " << i << ' ' << a << endl;
//            }
//        }
    }
};
