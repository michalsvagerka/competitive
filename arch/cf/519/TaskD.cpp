#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector2<int> A(M, N); cin >> A;
    vector<int> Next(N+1, -1);
    for (int i = 0; i < N - 1; ++i) {
        Next[A[0][i]] = A[0][i+1];
    }
    vector<bool> Good(N+1, true);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N-1; ++j) {
            Good[A[i][j]] = Good[A[i][j]] && (A[i][j+1] == Next[A[i][j]]);
        }
        Good[A[i][N-1]] = false;
    }


    vector<bool> Use(N);
    for (int i = 0; i < N; ++i) {
        Use[i] = Good[A[0][i]];
    }

    int run = 0;
    ll ans = N;
    for (int i = 0; i < N; ++i) {
        ans += run;
        if (Use[i]) {
            run++;
        } else {
            run = 0;
        }
    }
    cout << ans << endl;
}
};
