#include "../l/lib.h"
// #include "../l/mod.h"

class BAliceAndHairdresser {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, L; cin >> N >> M >> L;
    vector<ll> A(N+2, 0);
    for (int i = 0; i < N; ++i) cin >> A[i+1];

    int cost = 0;
    for (int i = 1; i <= N; ++i) {
        cost += A[i] > L && A[i+1] <= L;
    }

    for (int i = 0; i < M; ++i) {
        int t; cin >> t;
        if (t == 0) {
            cout << cost << '\n';
        } else {
            int p, d; cin >> p >> d;
            cost -= A[p] > L && A[p+1] <= L;
            cost -= A[p-1] > L && A[p] <= L;
            A[p] += d;
            cost += A[p] > L && A[p+1] <= L;
            cost += A[p-1] > L && A[p] <= L;
        }
    }


}
};
