#include "../l/lib.h"

class CNumbersOnACircle {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N), B(N);
        cin >> A >> B;
        for (int i = 0; i < N; ++i) {
            if (A[i] > B[i]) {
                cout << "-1\n";
                return;
            }
        }

        auto is_big = [&](int i) {
            if (B[i] == A[i]) return false;
            if (i == 0) return B[0] > B[N-1] && B[0] > B[1];
            else if (i == N-1) return B[N-1] > B[N-2] && B[N-1] > B[0];
            else return B[i] > B[i-1] && B[i] > B[i+1];
        };

        vector<int> Q;
        for (int i = 0; i < N; ++i) {
            if (is_big(i)) Q.push_back(i);
        }

        ll ans = 0;
        for (int q = 0; q < Q.size(); ++q) {
            int i = Q[q];
            int j = i == 0 ? N-1 : i-1;
            int k = i == N-1 ? 0 : i+1;
            int mn = max(max(B[j], B[k]) - (B[j]+B[k]) + 1, A[i]);
            int cnt = (B[i] - mn) / (B[j] + B[k]);

            if (cnt == 0) {
                cout << "-1\n";
                return;
            }
            B[i] -= cnt * (B[j] + B[k]);
            ans += cnt;

            if (is_big(i)) Q.push_back(i);
            if (is_big(j)) Q.push_back(j);
            if (is_big(k)) Q.push_back(k);
        }

        for (int i = 0; i < N; ++i) {
            if (A[i] != B[i]) {
                cout << "-1\n";
                return;
            }
        }

        cout << ans << '\n';
    }
};
