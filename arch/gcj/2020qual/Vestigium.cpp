#include "../l/lib.h"

class Vestigium {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector2<int> A(N, N); cin >> A;
            int k = 0;
            for (int i = 0; i < N; ++i) {
                k += A[i][i];
            }

            int r = 0;
            for (int i = 0; i < N; ++i) {
                vector<bool> S(N, false);
                for (int j = 0; j < N; ++j) {
                    S[A[i][j]-1] = true;
                }
                r += count(S.begin(),S.end(),false) > 0;
            }


            int c = 0;
            for (int i = 0; i < N; ++i) {
                vector<bool> S(N, false);
                for (int j = 0; j < N; ++j) {
                    S[A[j][i]-1] = true;
                }
                c += count(S.begin(),S.end(),false) > 0;
            }
            cout << "Case #" << t+1 << ": " << k << ' ' << r << ' ' << c << endl;
        }
    }
};
