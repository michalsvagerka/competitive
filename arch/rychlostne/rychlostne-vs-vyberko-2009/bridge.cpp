#include "../l/lib.h"
// #include "../l/mod.h"

class bridge {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        vector<ui> A(N); cin >> A;
        vector<ui> D = A;
        if (N >= 3) D[2] = A[0] + A[1] + A[2];
        for (ui i = 3; i < N; ++i) {
            D[i] += min(D[i-1], D[i-2] + 2*A[1]) + A[0];
        }
        cout << D.back() << endl;
    }
};
