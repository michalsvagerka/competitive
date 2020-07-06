#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;
constexpr int MX = 100000;
class CArrayBeauty {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> A(N); cin >> A;
        sort(A.begin(),A.end());
        vector<int> LO(MX+1, N);
        for (int i = N-1; i >= 0; --i) LO[A[i]] = i;
        for (int i = MX-1; i >= 0; --i) LO[i] = min(LO[i], LO[i+1]);

        vector2<FF> D(N+1, K+1, 0);
        vector<FF> XX(MX/(K-1)+1, 0);
        for (int lo = 1; lo <= MX/(K-1); ++lo) {
            for (int i = 0; i <= N; ++i) {
                for (int j = 0; j <= K; ++j) {
                    D[i][j] = 0;
                }
            }
            D[0][1] = 1;
            for (int j = 0; j < K; ++j) {
                for (int i = 0; i < N; ++i) {
                    D[i+1][j] += D[i][j];
                    int realLo = A[i]+lo <= MX ? LO[A[i]+lo] : N;
                    if (realLo != N) D[realLo + 1][j + 1] += D[i + 1][j];
                }
            }

            for (int i = 0; i < N; ++i) D[i+1][K] += D[i][K];
            for (int i = 0; i < N; ++i) XX[lo] += D[i+1][K];
        }
        FF ans = 0;
        for (int i = 0; i <= MX/(K-1); ++i) ans += XX[i];
        cout << ans << '\n';
    }
};
