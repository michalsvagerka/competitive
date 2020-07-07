#include "../../../l/lib.h"
#include "../../../l/mod.h"
#include "../../../l/util.h"

class ChristmasSongBroadcast {
public:
    int minimizeCost(int T, vector <int> A, vector <int> B, vector <string> directCost) {
        int N = A.size();
        vector<pair<int, pii>> E;
        for (int i = 0; i < N; ++i) {
            FieldMod ainv = 1/FieldMod{A[i]};
            for (int c = 0; c <= 100; ++c) {
                ui s = (ui) (ainv * (FieldMod{c} - B[i]));
                if (s < T && s >= 0) {
                    E.push_back({c, {N, i}});
                    break;
                }
            }
            E.push_back({B[i], {N,i}});
        }

        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                int c = (int)directCost[i][j];
                E.push_back({c, {i,j}});
            }
        }

        sort(E.begin(),E.end());
        UnionFind UF(N+1);
        int ans = 0;
        for (auto e: E) {
            if (UF.unite(e.y.x, e.y.y)) {
                ans += e.x;
            }
        }
        return ans;
    }


    void solve(istream& cin, ostream& cout) {
        cout << minimizeCost(1000000007,{1, 10, 100},{7, 7, 7},{"-AA", "A-A", "AA-"}) << endl;
        cout << minimizeCost(1,{1, 1, 1},{1600, 1500, 1700},{"-01", "0-A", "1A-"}) << endl;
        cout << minimizeCost(2,{100, 100, 100, 100},{0, 35, 999999910, 123456789},{"-01z", "0-Az", "1A-z", "zzz-"}) << endl;
        cout << minimizeCost(1,{47},{1000000006},{"-"}) << endl;
//        cout << minimizeCost(30001,{1, 10, 100},{7, 7, 7},{"-AA", "A-A", "AA-"}) << endl;
    }
};
