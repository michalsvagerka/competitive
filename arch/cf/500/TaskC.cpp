#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    ll inf = 1e12;
    vector2<ll> D(3, N+4, inf);
    D[0][0] = 0;
    for (int i = 0; i < N; ++i) {
        vector2<ll> E(3, N+4, inf);
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < N; ++k) {
                if (D[j][k] == inf) continue;
                E[max(j-1,0)][k] = min(E[max(j-1,0)][k], D[j][k]);
                if (j == 0) {
                    ll cost = 0;
                    if (i >= 1 && A[i-1] >= A[i]) cost += A[i-1] - A[i] + 1;
                    if (i != N-1 && A[i+1] >= A[i]) cost += A[i+1] - A[i] + 1;
                    E[2][k+1] = min(E[2][k+1], D[j][k] + cost);
                } else if (j == 1) {
                    ll cost = 0;
                    if (i >= 2 && min(A[i-1], A[i-2]-1) >= A[i]) cost += min(A[i-1], A[i-2]-1) - A[i] + 1;
                    if (i != N-1 && A[i+1] >= A[i]) cost += A[i+1] - A[i] + 1;
                    E[2][k+1] = min(E[2][k+1], D[j][k] + cost);
                }
            }
        }
        swap(E,D);
    }

    vector<ll> Ans((N+1)/2, inf);
    for (int i = 0; i < (N+1)/2; ++i) {
        for (int j = 0; j < 3; ++j) {
            Ans[i] = min(Ans[i], D[j][i+1]);
        }
    }
    cout << Ans;
}
};
