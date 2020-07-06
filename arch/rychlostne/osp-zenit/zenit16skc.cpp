#include "../l/lib.h"

class zenit16skc {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<vector<int>> C(3);
        for (int i = 0; i < N; ++i) {
            C[A[i]%3].push_back(i);
        }
        for (int i = 0; i < 3; ++i) {
            if (C[i].size() >= 3) {
                cout << A[C[i][0]] << ' '  << A[C[i][1]] << ' '  << A[C[i][2]] << endl;
                return;
            }
        }

        cout << A[C[0][0]] << ' '  << A[C[1][0]] << ' '  << A[C[2][0]] << endl;
    }
};
