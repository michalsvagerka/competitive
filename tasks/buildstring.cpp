#include "../l/lib.h"
 #include "../l/mincostmaxflow.h"

class buildstring {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N; cin >> N;
        MinCostMaxFlow<int> MF(N+26+2);
        for (char s: S) MF.AddEdge(0, s-'a'+1, 1, 0);

        for (int i = 0; i < N; ++i) {
            string T; int cap; cin >> T >> cap;
            for (char t: T) MF.AddEdge(t-'a'+1, 27+i, 1, 0);
            MF.AddEdge(27+i, 27+N, cap, i+1);
        }

        auto F = MF.GetMaxFlow(0, 27+N);
        if (F.x == S.size()) {
            cout << F.y << '\n';
        } else {
            cout << -1 << '\n';
        }

    }
};
