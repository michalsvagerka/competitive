#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<string> S(N); cin >> S;
    vector<pii> A(N, {-1,-1});

    bool fail = false;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (S[i][j] == '.') {
                A[i] = {i+1,j+1};
            }
        }
        if (A[i] == pii{-1,-1}) fail = true;
    }

    if (fail) {
        fail = false;
        fill(A.begin(),A.end(),pii{-1,-1});
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (S[j][i] == '.') {
                    A[i] = {j+1,i+1};
                }
            }
            if (A[i] == pii{-1,-1}) fail = true;
        }
    }

    if (fail) {
        cout << "-1\n";
    } else {
        for (pii a:A) {
            cout << a << '\n';
        }
    }


}
};
