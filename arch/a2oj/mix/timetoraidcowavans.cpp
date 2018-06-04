#include "../../../l/lib.h"
// #include "../l/mod.h"

class timetoraidcowavans {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> W(N); cin >> W;
        int P; cin >> P;
        vector<vector<pii>> R(N+1);
        for (int i = 0; i < P; ++i) {
            int a,b; cin >> a >> b;
            R[b].push_back({a-1,i});
        }
        vector<ll> A(P, -1), Z(N);

        int NN = int(sqrt(N));
        for (int b = 1; b < NN; ++b) {
            for (int i = 0; i < N; ++i) Z[i] = W[i];
            for (int i = N-b-1; i >= 0; --i) Z[i] += Z[i+b];
            for (pii&r:R[b]) A[r.y] = Z[r.x];
        }

        for (int b = NN; b <= N; ++b) {
            for (pii&r:R[b]) {
                A[r.y] = 0;
                for (int i = r.x; i < N; i += b) {
                    A[r.y] += W[i];
                }
            }
        }

        for (ll a:A) cout << a << '\n';
    }
};
