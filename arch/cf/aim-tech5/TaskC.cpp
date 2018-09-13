#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector2<int> X(4, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> X[j][i];
        }
    }

    vector2<int> P(4, N+1), S(4, N+1);
    for (int j = 0; j < 4; ++j) {
        S[j][N] = P[j][0] = j < 2 ? -2e9 : 2e9;
        for (int i = 0; i < N; ++i) {
            P[j][i+1] = j < 2 ? max(P[j][i], X[j][i]) : min(P[j][i], X[j][i]);
            S[j][N-i-1] = j < 2 ? max(S[j][N-i], X[j][N-i-1]) : min(S[j][N-i], X[j][N-i-1]);
        }
    }
    

    for (int i = 0; i < N; ++i) {
        vector<int> W(4);
        for (int j = 0; j < 4; ++j) {
            W[j] = j < 2 ? max(P[j][i], S[j][i+1]) : min(P[j][i], S[j][i+1]);
        }
        if (W[0] <= W[2] && W[1] <= W[3]) {
            cout << W[0] << ' ' << W[1] << endl;
            return;
        }
    }

}
};
