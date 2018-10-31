#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, A, B, T; cin >> N >> A >> B >> T;
    string R; cin >> R;

    vector<int> P(N+1, 0);

    for (int i = 0; i < N; ++i) {
        P[i+1] = P[i] + 1 + B*(R[i] == 'w');
    }

    if (P[N] + (N-1)*A <= T) {
        cout << N << endl;
        return;
    }

    if (P[1] > T) {
        cout << 0 << endl;
        return;
    }

    int ans = 0;
    for (int l = 0, r = 0; l < N-1; ++l) {
        while (r < N && P[l+1] + 2*l*A + P[N] + (N-r)*A - P[r] > T) ++r;
        if (P[l+1] + 2*l*A + P[N] + (N-r)*A - P[r] <= T) ans = max(ans, l + (N-r) + 1);
        if (P[l+1] + l*A <= T) ans = max(ans, l+1);
    }
    

    for (int r = 0, l = N-1; r < N-1; ++r) {
        while (l > 0 && P[N] - P[N-r] + r*2*A + l*A + P[l+1] > T) --l;
        if (P[N] - P[N-r] + r*2*A + l*A + P[l+1] <= T) ans = max(ans, l + r + 1);
        if (P[1] + P[N] - P[N-r] + r*A <= T) ans = max(ans, r+1);
    }
    
    cout << ans << endl;
}
};
