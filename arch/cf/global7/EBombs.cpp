#include "../l/lib.h"
#include "../l/nsegtree.h"

class EBombs {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N), Q(N); cin >> P >> Q;
        for (int &q: Q) --q;

        vector<int> I(N+1);
        for (int i = 0; i < N; ++i) I[P[i]] = i;

        LAddMinTree<int> LL(N, 0, 0);
        LL.put(0, N-1, 100);

        AssignMaxTree<int> MT(N, 0, 0);
        for (int i = 0; i < N; ++i) MT.put(i, P[i]);

        vector<int> Ans(N);
        int mx = N;
        Ans[0] = N;
        set<int> avail;
        for (int i = 1; i <= N; ++i) avail.insert(i);
        for (int i = 0; i < N-1; ++i) {
            LL.put(Q[i], N-1, -1);

//            cout << "M";
//            for (int i = 0; i < N; ++i) cout << LL.get(i) << " \n"[i==N-1];
            while (LL.get(0, N-1) < 100) {
                int l = bsl(0, N-1, [&](int x) {
                    return LL.get(0, x) < 100;
                });
                int q = MT.get(0, l);
                avail.erase(q);
//                cout << "rem " << q << endl;
                MT.put(I[q], -1);
                LL.put(I[q], N-1, 1);
            }

//            for (int i = 0; i < N; ++i) cout << LL.get(i) << " \n"[i==N-1];

            Ans[i+1] = *avail.rbegin();
        }

        cout << Ans;
    }
};
