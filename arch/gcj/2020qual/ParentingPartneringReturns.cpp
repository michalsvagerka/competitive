#include "../l/lib.h"

class ParentingPartneringReturns {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<pair<pii,int>> A(N);
            for (int i = 0; i < N; ++i) {
                cin >> A[i].x;
                A[i].y = i;
            }
            sort(A.begin(),A.end());

            int C = 0, J = 0;
            string R = string(N, '?');
            for (auto a: A) {
                if (a.x.x >= C) {
                    R[a.y] = 'C';
                    C = a.x.y;
                } else if (a.x.x >= J) {
                    R[a.y] = 'J';
                    J = a.x.y;
                }
            }

            if (count(R.begin(),R.end(),'?')) R = "IMPOSSIBLE";
            cout << "Case #" << t+1 << ": " << R << '\n';
        }
    }
};
