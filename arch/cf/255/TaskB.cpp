#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N,M,K,P; cin >> N >> M >> K >> P;
    vector2<int> A(N, M); cin >> A;

    vector<int> S(N, 0);
    maxheap<ll> W;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            S[i] += A[i][j];
        }
        W.push(S[i]);
    }

    vector<ll> H(K+1, 0);
    for (int i = 1; i <= K; ++i) {
        ll c = W.top();
        W.pop();
        H[i] = H[i-1] + c;
        W.push(c - P*M);
    }

    maxheap<ll> R;
    vector<int> T(M, 0);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            T[i] += A[j][i];
        }
        R.push(T[i]);
    }

    vector<ll> V(K+1, 0);
    for (int i = 1; i <= K; ++i) {
        ll c = R.top();
        R.pop();
        V[i] = V[i-1] + c;
        R.push(c - P*N);
    }

    ll ans = -1e18;
    for (int h = 0; h <= K; ++h) {
        ans = max(ans, H[h] + V[K-h] - h * ll(K-h) * P);
    }
    cout << ans << endl;
}
};
