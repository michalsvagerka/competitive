#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> D(N, 0), C(N, 0);
        C[0] = 1;
        for (int i = 1; i < N; ++i) {
            int p; cin >> p; --p;
            D[i] = D[p] + 1;
            C[D[i]]++;
        }

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            ans += C[i]%2;
        }
        cout << ans << endl;
    }
};
