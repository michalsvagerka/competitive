#include "../l/lib.h"
// #include "../l/mod.h"

class BGregAndGraph {
public:
void solve(istream& cin, ostream& cout) {
    int N; cin >> N;
    vector2<int> A(N, N); cin >> A;
    vector<int> X(N); cin >> X;
    vector<bool> U(N, false);
    vector<ll> Ans(N);
    for (int i = 0; i < N; ++i) {
        int n = X[N-1-i]-1;
        minheap<pii> H;
        for (int j = 0; j < N; ++j) if (U[j]) H.push({A[n][j], j});
        while (!H.empty()) {
            pii h = H.top(); H.pop();
            if (A[n][h.y] == h.x) {
                for (int j = 0; j < N; ++j) {
                    if (U[j] && A[n][j] > A[n][h.y] + A[h.y][j]) {
                        A[n][j] = A[n][h.y] + A[h.y][j];
                        H.push({A[n][j],j});
                    }
                }
            }
        }

        for (int j = 0; j < N; ++j) if (U[j]) H.push({A[j][n], j});
        while (!H.empty()) {
            pii h = H.top(); H.pop();
            if (A[h.y][n] == h.x) {
                for (int j = 0; j < N; ++j) {
                    if (U[j] && A[j][n] > A[h.y][n] + A[j][h.y]) {
                        A[j][n] = A[h.y][n] + A[j][h.y];
                        H.push({A[j][n],j});
                    }
                }
            }
        }
        
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (U[j] && U[k]) A[j][k] = min(A[j][k], A[j][n] + A[n][k]);
            }
        }
        U[X[N-1-i]-1] = true;

        ll ans = 0;
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (U[j] && U[k]) ans += A[j][k];
            }
        }
        Ans[N-1-i] = ans;
    }
    cout << Ans;
}
};
