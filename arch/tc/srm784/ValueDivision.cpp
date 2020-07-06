#include "../l/lib.h"

class ValueDivision {
public:

    vector <int> getArray(vector <int> A) {
        int N = A.size();
        map<int, vector<int>> Pos;
        for (int i = 0; i < N; ++i) {
            Pos[A[i]].push_back(i);
        }
        int mx = 1e9+7;
        while (true) {
            auto it = Pos.lower_bound(mx);
            if (it == Pos.begin()) break;
            --it;
            mx = it->x;
            if (mx == 1) break;
            vector<int> pos = it->y;
            sort(pos.begin(),pos.end());
            int g = pos.size();
            if (g >= 2) {
                Pos[mx].clear();
                for (int i = 0; i < g-1; ++i) {
                    Pos[mx-1].push_back(pos[i]);
                }
                Pos[mx].push_back(pos[g-1]);
            }
        }
        vector<int> Ans(N);
        for (auto i: Pos) {
            for (int j: i.y) {
                Ans[j] = i.x;
            }
        }
        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
        cout << getArray({2, 3, 3}) << '\n';
        cout << getArray({1, 5, 7, 4, 5, 4, 1}) << '\n';
        cout << getArray({7}) << '\n';
        cout << getArray({7, 4}) << '\n';
        cout << getArray({7, 7, 7, 7}) << '\n';

    }
};
