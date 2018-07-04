#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector<int> A(N); cin >> A;

    int b = 0;
    vector<pii> R;
    while (b < N) {
        int e = b;
        while (e+1 < N && A[e+1] > A[e]) ++e;
        R.push_back({b, e});
        b = e+1;
    }

    if (R.size() == 1) {
        cout << N << endl;
    } else {
        int ans = 0;
        for (pii r:R) ans = max(ans, r.y - r.x + 2);

        int Z = R.size();
        for (int i = 0; i < Z-1; ++i) {
            if (R[i+1].x != R[i+1].y && A[R[i+1].x+1] >= A[R[i].y] + 2) {
                ans = max(ans, R[i+1].y - R[i].x + 1);
            } else if (R[i].x != R[i].y && A[R[i+1].x] >= A[R[i].y-1] + 2) {
                ans = max(ans, R[i+1].y - R[i].x + 1);
            }
        }
        cout << ans << '\n';
    }

}
};
