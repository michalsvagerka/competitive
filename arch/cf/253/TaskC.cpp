#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    if (N <= 2) {
        cout << 0 << endl;
        return;
    }

    vector<int> A(N); cin >> A;
    vector<int> D;
    int M = 0;
    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        while (M >= 2 && A[i] >= D[M-1] && D[M-2] >= D[M-1]) {
            ans += min(A[i], D[M - 2]);
            D.pop_back();
            M--;
        }

        D.push_back(A[i]);
        ++M;
    }

    bool isUp = true, isDown = true;
    ll sum = D[M-1];
    for (int i = 0; i < M-1; ++i) {
        isUp &= D[i] <= D[i+1];
        isDown &= D[i] >= D[i+1];
        sum += D[i];
    }

    if (isUp) {
        ans += sum - D[M-1] - D[M-2];
    } else if (isDown) {
        ans += sum - D[0] - D[1];
    } else {
        for (int i = 1; i < M-1; ++i) {
            ans += min(D[i-1], D[i+1]);
        }
    }

    cout << ans << endl;
}
};
