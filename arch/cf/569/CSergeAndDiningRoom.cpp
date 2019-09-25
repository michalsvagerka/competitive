#include "../l/lib.h"
#include "../l/nsegtree.h"

constexpr int MX = 1000000;

class CSergeAndDiningRoom {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> S(MX+1, 0);
        vector<int> A(N), B(M); cin >> A >> B;
        for (int a: A) S[a]--;
        for (int b: B) S[b]++;
        for (int i = MX; i > 0; --i) {
            S[i-1] += S[i];
        }
        for (int&s: S) s -= MX;

        int Q; cin >> Q;
        LAddMinTree<int> T(S, 0, 0);
        for (int q = 0; q < Q; ++q) {
            int t; cin >> t;
            int i; cin >> i;
            int v; cin >> v;
            i--;
            if (t == 1) {
                T.put(0, A[i], 1);
                A[i] = v;
                T.put(0, A[i], -1);
            } else {
                T.put(0, B[i], -1);
                B[i] = v;
                T.put(0, B[i], 1);
            }
            
            int w = T.longestSuffix(MX, [&](int val) { return val >= -MX; });
            cout << w-1 << '\n';
        }

    }
};
