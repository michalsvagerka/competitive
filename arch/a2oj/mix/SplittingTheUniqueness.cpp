#include "../l/lib.h"
// #include "../l/mod.h"

class SplittingTheUniqueness {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<pii> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i].x;
        S[i].y = i;
    }
    sort(S.begin(),S.end());
    vector<int> A(N), B(N);
    for (int i = 0; i < N/3; ++i) {
        A[S[i].y] = i;
        B[S[i].y] = S[i].x - i;
    }

    for (int i = N/3; i < 2*N/3; ++i) {
        B[S[i].y] = i;
        A[S[i].y] = S[i].x - i;
    }

    for (int i = 2*N/3; i < N; ++i) {
        B[S[i].y] = N - 1 - i;
        A[S[i].y] = S[i].x - B[S[i].y];
    }

    cout << "YES\n" << A << B;

}
};
