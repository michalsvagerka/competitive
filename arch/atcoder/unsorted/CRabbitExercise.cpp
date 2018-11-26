#include "../l/lib.h"
#include <numeric>
// #include "../l/mod.h"

class CRabbitExercise {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> X(N); cin >> X;
    int M; ll K; cin >> M >> K;
    vector<int> A(M); cin >> A;

    vector<int> P(N-1);
    iota(P.begin(),P.end(),0);
    for (int a : A) swap(P[a-2], P[a-1]);

    auto comb = [&](const vector<int> &A, const vector<int> &B) {
        vector<int> C(N-1);
        for (int i = 0; i < N - 1; ++i) C[i] = A[B[i]];
        return C;
    };

    vector<int> R(N-1);
    iota(R.begin(),R.end(),0);
    while (K) {
        if (K&1) R = comb(R, P);
        P = comb(P, P);
        K /= 2;
    }

    vector<ll> DX(N-1);
    for (int i = 0; i < N - 1; ++i) DX[i] = X[i+1] - X[i];
    vector<ll> Ans(N);
    Ans[0] = X[0];
    for (int i = 1; i < N; ++i) Ans[i] = Ans[i-1] + DX[R[i-1]];
    for (int i = 0; i < N; ++i) cout << Ans[i] << ".0\n";
}
};
