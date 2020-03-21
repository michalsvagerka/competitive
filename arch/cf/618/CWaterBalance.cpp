#include "../l/lib.h"

class CWaterBalance {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<pair<int, ll>> C{{1, A[0]}};
        for (int i = 1; i < N; ++i) {
            C.push_back({1, A[i]});
            while (C.size() >= 2 && C[C.size()-2].y * C[C.size()-1].x >= C[C.size()-1].y * C[C.size()-2].x) {
                C[C.size()-2].x += C[C.size()-1].x;
                C[C.size()-2].y += C[C.size()-1].y;
                C.pop_back();
            }
        }


        cout << fixed << setprecision(15);
        for (auto c: C) {
            for (int d = 0; d < c.x; ++d) cout << c.y * 1.0 / c.x << '\n';
        }
    }
};
