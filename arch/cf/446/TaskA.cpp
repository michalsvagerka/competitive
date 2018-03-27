#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        if (N == 1 && A[0] == 1) {
            cout << "0\n";
            return;
        }
        int ans = N;
        for (int i = 0; i < N; ++i) {
            int g = A[i];
            for (int j = i+1; j < N; ++j) {
                g = gcd(A[j], g);
                if (g == 1) {
                    ans = min(j-i, ans);
                }
            }
        }

        cout << (ans == N ? -1 : ans + N-1 - count(A.begin(),A.end(),1)) << endl;
    }
};
