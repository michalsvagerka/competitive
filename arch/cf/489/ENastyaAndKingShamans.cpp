#include "../../../l/lib.h"
#include "../../../l/fenwick.h"

class ENastyaAndKingShamans {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<int> A(N); cin >> A;
        vector<ll> B(N);

        for (int i = 0; i < N; ++i) B[i] = A[i];
        Fenwick<ll> F(B, 0);
        vector<set<int>> W(31);
        for (int i = 0; i < N; ++i) W[logceil(A[i])].insert(i);
        for (int q = 0; q < Q; ++q) {
            int p, x; cin >> p >> x; --p;
            F.add(p, x-A[p]);
            W[logceil(A[p])].erase(p);
            A[p] = x;
            W[logceil(A[p])].insert(p);

            int ans = -1;
            for (int i = 0; i <= 30; ++i) {
                if (!W[i].empty()) {
                    int a = *W[i].begin();
                    if (F.sum(a+1) == 2*A[a]) {
                        ans = a+1;
                        break;
                    }

                    if (W[i].size() >= 2) {
                        a = *next(W[i].begin());
                        if (F.sum(a+1) == 2*A[a]) {
                            ans = a+1;
                            break;
                        }
                    }
                }
            }
            cout << ans << '\n';
        }
    }
};
