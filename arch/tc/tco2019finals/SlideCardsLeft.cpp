#include "../l/lib.h"

class SlideCardsLeft {
public:
    vector <int> getPosition(int N, long long steps) {
        if (steps >= 1LL<<(N-1)) return {};

        vector<int> Ans(N, -1);
        for (int i = 0; i < N; ++i) {
            if (steps < (1LL<<i)) {
                Ans[i] = 0;
                for (int j = i+1; j < N; ++j) Ans[j] = j;
                if (i > 0) {
                    set<int> S;
                    for (int j = 1; j <= i; ++j) S.insert(j);

                    for (int j = i - 2; j >= 0; --j) {
                        if (steps & (1LL << j)) {
                            Ans[j + 1] = *prev(S.end());
                        } else {
                            Ans[j + 1] = *prev(prev(S.end()));
                        }
                        S.erase(Ans[j + 1]);
                    }
                    Ans[0] = *S.begin();
                }
                return Ans;
            }
        }
    }
    void solve(istream& cin, ostream& cout) {
        for (pii x:vector<pii>{{2, 0}, {2,1}, {2,2},{7,5},{47,0}}) {
            cout << "{";
            for (int y: getPosition(x.x, x.y)) {
                cout << y << ", ";
            }
            cout << "}\n";
        }
    }
};
