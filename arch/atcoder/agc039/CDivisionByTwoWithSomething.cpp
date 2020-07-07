#include "../../../l/lib.h"
#include "../../../l/mod.h"
typedef Field<998244353> FF;

class CDivisionByTwoWithSomething {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string X; cin >> X;
//        for (int i = 0; i < (1<<N); ++i) {
//            int j = i, c = 0;
//            do {
//                ++c;
//                j = (j | ((j&1)^1) << N) >> 1;
//            } while (j != i);
//            cout << i << ' ' << c << endl;
//        }

        FF cnt = 0;
        for (int i = 0; i < N; ++i) {
            cnt *= 2;
            cnt += X[i]-'0';
        }
        cnt++;

        FF ans = cnt * (2*N);

        vector<FF> Q(N+1, 0);
        for (int i = 1; i < N; ++i) {
            if (N%i == 0 && N/i >= 3 && (N/i)%2 == 1) {
                FF lt = 0;
                for (int k = 0; k < i; ++k) {
                    lt *= 2;
                    lt += X[k]-'0';
                }

                string T(N, ' ');
                for (int k = 0; k < i; ++k) T[k] = X[k];
                for (int k = i; k < 2*i; ++k) T[k] = "01"[X[k-i] == '0'];
                for (int k = 2*i; k < N; ++k) T[k] = T[k-2*i];

                bool leq = true;
                for (int k = 0; k < N; ++k) {
                    if (T[k] < X[k]) break;
                    if (T[k] > X[k]) { leq = false; break; }
                }
                lt += leq;
                lt -= Q[i];
                for (int j = 3; j*i <= N; j += 2) Q[j*i] += lt;
                ans -= lt * (2*N - 2*i);

            }
        }

        cout << ans << endl;
    }
};
