#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector2<int> R(N+1, 4, 0);
        for (int i = 0; i < N; ++i) {
            R[i+1] = R[i];
            if (A[i] == 1) {
                R[i+1][0] = max(R[i+1][0], R[i][0]+1);
                R[i+1][2] = max(R[i+1][2], R[i][1]+1);
                R[i+1][2] = max(R[i+1][2], R[i][2]+1);
            } else {
                R[i+1][1] = max(R[i+1][1], R[i][0]+1);
                R[i+1][1] = max(R[i+1][1], R[i][1]+1);
                R[i+1][3] = max(R[i+1][3], R[i][2]+1);
                R[i+1][3] = max(R[i+1][3], R[i][3]+1);
            }
        }

        cout << *max_element(R[N].begin(),R[N].end()) << endl;
    }
};
