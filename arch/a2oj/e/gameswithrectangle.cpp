#include "../../../l/lib.h"
#include "../../../l/mod.h"

class gameswithrectangle {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M,K; cin >> N >> M >> K;
        N -= 2*K;
        M -= 2*K;
        if (N<0 || M<0) {
            cout << "0\n";
            return;
        }
        auto F = FieldMod::fact(2001);
        auto I = FieldMod::invfact(2001);

        FieldMod ans = 0;
        for (int w = 0; w < N; ++w) {
            FieldMod a = F[w+K-1]*I[w];
            FieldMod c = F[N-w+K-1]*I[N-w-1];
            for (int h = 0; h < M; ++h) {
                FieldMod b = F[h+K-1]*I[h];
                FieldMod d = F[M-h+K-1]*I[M-h-1];
                ans += a*b*c*d;
            }
        }
        cout << ans*I[K-1]*I[K-1]*I[K]*I[K] << '\n';

//        vector2<FieldMod> D(N+1, M+1, 1);
//        for (int k = 0; k < K; ++k) {
//            vector2<FieldMod> E(N+1, M+1, 0);
//            for (int n = 1; n <= N; ++n) {
//                for (int m = 1; m <= M; ++m) {
//                    for (int pn = 1; pn <= n; ++pn) {
//                        for (int pm = 1; pm <= m; ++pm) {
//                            E[n][m] += (n+1-pn)*(m+1-pm)*D[pn][pm];
//                        }
//                    }
//                }
//            }
//            swap(E,D);
//        }
//        cout << D[N][M] << '\n';
    }
};
