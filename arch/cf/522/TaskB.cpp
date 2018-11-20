#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;
    sort(A.begin(),A.end());

    int diff = 1;
    for (int i = 1; i < N; ++i) {
        diff += (A[i] != A[i-1]);
    }
    if (diff <= 2) {
        cout << N << endl;
        return;
    }

    int ans = 1;
    for (int i = 1; i <= 100; ++i) {
        int c = count(A.begin(),A.end(), i);
        if (c == 0) continue;

        vector<bitset<10001>> B(c+1);
        B[0][0] = true;
        for (int a:A) {
            if (a != i) {
                for (int k = c-1; k >= 0; --k) {
                    B[k+1] |= B[k] << a;
                }
            }
        }

        int k = 1;
        while (k <= c && !B[k][k*i]) ++k;
        ans = max(ans, k-1);
    }

    cout << ans << '\n';
}
};
