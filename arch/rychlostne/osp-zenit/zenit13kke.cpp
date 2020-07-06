#include "../l/lib.h"

class zenit13kke {
public:
    void solve(istream& cin, ostream& cout) {
        int N, S; cin >> N >> S;
        vector<int> P(N), Q(N);
        for (int i = 0; i < N; ++i) {
            cin >> P[i] >> Q[i];
        }
        vector<pii> A(N), B(N);
        for (int i = 0; i < N; ++i) {
            if (i == S-1) {
                A[i] = {-P[i]-Q[i], i};
                B[i] = {-P[i], i};
            } else {
                B[i] = {-P[i]-Q[i], i};
                A[i] = {-P[i], i};
            }
        }

        sort(A.begin(),A.end());
        sort(B.begin(),B.end());
        for (int i = 0; i < N; ++i) {
            if (A[i].y == S - 1) cout << i + 1 << " ";
        }
        for (int i = 0; i < N; ++i) {
            if (B[i].y == S - 1) cout << i + 1 << "\n";
        }
    }
};
