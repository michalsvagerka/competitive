#include "../../../l/lib.h"
#include "../../../l/nsegtree.h"

class FOneOccurrence {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        int Q; cin >> Q;
        vector<pii> I(Q); cin >> I;
        vector<int> Ans(Q, 0);
        vector<vector<pii>> QQ(N);
        for (int i = 0; i < Q; ++i) {
            QQ[I[i].x-1].emplace_back(I[i].y-1, i);
        }

        vector<int> Next(500001, N);
        vector<int> Foll(N);
        for (int i = N-1; i >= 0; --i) {
            Foll[i] = Next[A[i]];
            Next[A[i]] = i;
        }

//        cout << Foll;
        AssignMaxTree<int> W(N, 0, 0);
        for (int i = N-1; i >= 0; --i) {
            int n = Foll[i];
            if (n != N) W.put(n, -1);
            W.put(i, n);
//            for (int j = 0; j < N; ++j) cout << W.get(j) << ' ';
//            cout << endl;
            for (pii q: QQ[i]) {
                
                int s = W.longestPrefix(i, [&](int v) { return v <= q.x; });
                if (s < q.x) {
                    Ans[q.y] = A[s+1];
                }
//                cout << q.x << ' ' << s << '\n';
            }
        }
        for (int ans: Ans) cout << ans << '\n';

    }
};
