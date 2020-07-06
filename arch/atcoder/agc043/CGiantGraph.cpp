#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;
class CGiantGraph {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<vector<int>> E(3, N);
        vector2<set<int>> G(3, N);
        vector2<int> Mex(3, N, 0);
        for (int i = 0; i < 3; ++i) {
            int M; cin >> M;
            for (int j = 0; j < M; ++j) {
                int a, b; cin >> a >> b;
                --a; --b;
                E[i][a].push_back(b);
                E[i][b].push_back(a);
            }

            for (int j = N-1; j >= 0; --j) {
                while (G[i][j].count(Mex[i][j])) ++Mex[i][j];
                for (int k : E[i][j]) if (k < j) G[i][k].insert(Mex[i][j]);
            }
        }

        FF base = FF{10}.pow(18);
        vector2<FF> MX(3, 1<<11, 0);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < N; ++j) {
                MX[i][Mex[i][j]] += base.pow(j+1);
            }
        }


        vector<FF> Ans = MX[0];
        for (int i = 1; i < 3; ++i) {
            vector<FF> E(1<<11, 0);
            for (int j = 0; j < (1<<11); ++j) {
                for (int k = 0; k < (1<<11); ++k) {
                    E[j^k] += Ans[j] * MX[i][k];
                }
            }
            swap(E,Ans);
        }
        cout << Ans[0] << '\n';


//        FF base = FF{10}.pow(18);
//        FF ans = 0;
//        vector2<FF> Q(3, 2, 0);
//
//
////        cout << base.pow(9) + base.pow(7) + base.pow(5) + base.pow(8) + base.pow(6) + base.pow(4) + base.pow(7) + base.pow(5) + base.pow(3) << '\n';
////        cout << base.pow(9) + base.pow(8) + base.pow(7) + base.pow(7) + base.pow(6) + base.pow(5) << endl;
//        for (int k = 0; k < 3; ++k) {
//            for (int i = 0; i < N; ++i) {
//                if (A[k][i] && B[k][i]) continue;
//                Q[k][A[k][i]] += base.pow(i + 1);
//            }
//        }
//
//        for (int i = 0; i < 2; ++i) {
//            for (int j = 0; j < 2; ++j) {
//                for (int k = 0; k < 2; ++k) {
//                    if (i^j^k) ans += Q[0][i] * Q[1][j] * Q[2][k];
//                }
//            }
//        }
////
////            for (int k = 0; k < N; ++k) {
////                if (A[2][k] && B[2][k]) continue;
////                if (1 == A[2][k]) {
////                    ans += (Q[0][0] * Q[1][0] + Q[0][1] * Q[1][1]) * base.pow(k+1);
////                } else {
////                    ans += (Q[0][1] * Q[1][0] + Q[0][0] * Q[1][1]) * base.pow(k+1);
////                }
////            }
//////        }
//        cout << ans << '\n';
    }
};
