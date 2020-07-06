#include "../l/lib.h"

class EInversionSwapSort {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        set<pii> B;
        for (int i = 0; i < N; ++i) {
            B.insert({A[i],i});
        }
        vector<int> C(N);
        int j = 0;
        for (pii b: B) {
            C[b.y] = j++;
        }

        vector<pii> Ans;
        vector<int> D = C;
        for (int i = N-1; i >= 0; --i) {
            vector<pii> Inv;
            for (int j = 0; j < i; ++j) {
                if (C[j] > C[i]) {
                    Inv.push_back({C[j], j});
                }
            }
            sort(Inv.begin(),Inv.end());
            for (pii inv: Inv) {
                Ans.push_back({inv.y+1, i+1});
                swap(D[inv.y], D[i]);
            }
        }
//        cout << D;
        cout << Ans.size() << '\n';
        for (pii ans: Ans) cout << ans << '\n';
    }
};
