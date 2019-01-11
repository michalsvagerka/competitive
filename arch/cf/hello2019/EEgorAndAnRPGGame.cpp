#include "../l/lib.h"
// #include "../l/mod.h"

int Prev[int(1e5)+3];

class EEgorAndAnRPGGame {
public:


void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<vector<int>> Ans;
        while (!A.empty()) {
            int M = A.size();
            vector<vector<int>> B{{0}};
            for (int i = 0; i < M; ++i) {
                int s = bsh(0, int(B.size()-1), [&](int x) { return B[x].back() < A[i]; });
                if (s == B.size()-1) B.emplace_back();

                B[s+1].push_back(A[i]);
                Prev[A[i]] = B[s].back();
            }

            vector<int> Cur, Left;
            int idx = B.back().back();
            while (idx != 0) {
                Cur.push_back(idx);
                idx = Prev[idx];
            }
            reverse(Cur.begin(),Cur.end());

            int j = 0;
            for (int i = 0; i < M; ++i) {
                if (j != Cur.size() && Cur[j] == A[i]) ++j;
                else Left.push_back(A[i]);
            }
            int K = Cur.size();
            if (K * (K+1) / 2 >= A.size()) {
                swap(A, Left);
                Ans.push_back(Cur);
            } else {
                for (auto&b : B) {
                    if (b.front() == 0) continue;
                    Ans.emplace_back();
                    swap(Ans.back(), b);
                }
                break;
            }

        }

        cout << Ans.size() << endl;
        for (auto &ans: Ans) {
            cout << ans.size() << ' ' << ans;
        }
    }
}
};
