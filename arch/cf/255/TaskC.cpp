#include "../l/lib.h"
 #include "../l/mod.h"

typedef Field<1000000009> F;
constexpr int SIZE = 850;
constexpr int MOD = 1000000009;

vector<int> Z, A;

class TaskC {
public:
    struct Block {
        Block(int L, int R) : L(L), R(R), X(R-L+1, 0), w(0), x(0) {
            for (int i = 0; i < R-L; ++i) X[i+1] = X[i] + A[i+L];
        }

        ui sum(int l, int r) {
            if (l >= R || r <= L) return 0;
            int a = max(l,L)-L;
            int b = min(r,R)-L;
            return (X[b] - X[a] + MOD + ll(MOD+Z[b+2]-Z[a+2])*w + ll(MOD+Z[b+1]-Z[a+1])*x)%MOD;
        }

        void add(int l, int r) {
            if (l >= R || r <= L) return;
            if (l <= L && r >= R) {
                w += Z[L - l + 1];
                if (w >= MOD) w -= MOD;
                x += Z[L - l];
                if (x >= MOD) x -= MOD;
            } else {
                for (int i = max(l, L); i < min(r, R); ++i) {
                    int f = i - l + 1;
                    A[i] += Z[f];
                    if (A[i] >= MOD) A[i] -= MOD;
                }

                for (int i = max(l, L)-L; i < R-L; ++i) X[i+1] = X[i] + A[i+L];
            }
        }

        int L, R;
        vector<ll> X;
        int w,x;
    };


void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    A.resize(N); cin >> A;

    Z = vector<int>(300001, 0);
    Z[1] = Z[2] = 1;
    for (int i = 3; i < Z.size(); ++i) {
        Z[i] = (Z[i-1] + Z[i-2])%MOD;
    }

    vector<Block> B;
    for (int l = 0; l < N; l += SIZE) B.emplace_back(l, min(l+SIZE, N));

    for (int j = 0; j < M; ++j) {
        int t,l,r; cin >> t >> l >> r;
        --l;
        if (t == 1) {
            for (int i = l/SIZE; i < (r-1)/SIZE+1; ++i) B[i].add(l,r);
        } else {
            ll x = 0;
            for (int i = l/SIZE; i < (r-1)/SIZE+1; ++i) x += B[i].sum(l,r);
            cout << x%MOD << '\n';
        }
    }
}
};
