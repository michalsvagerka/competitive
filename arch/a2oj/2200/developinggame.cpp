#include "../../../l/lib.h"
#include "../../../l/segtree.h"

class developinggame {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pair<int,pii>> P(N);
        cin >> P;

        vector<vector<int>> In(3e5+1), Out(3e5+1);
        for (int i = 0; i < N; ++i) {
            In[P[i].x].push_back(i);
            Out[P[i].y.x].push_back(i);
        }

        AddMaxTree<int> A;
        A.setup(3e5+1, 0);

        pii best{-1, 0};
        for (int i = 1; i <= 3e5; ++i) {
            for (int j : In[i]) A.put(P[j].y.x, P[j].y.y, 1);
            int g = A.get(0, 3e5);
            best = max(best, {g, i});
            for (int j : Out[i]) A.put(P[j].y.x, P[j].y.y, -1);
        }


        int l = best.y;
        vector<int> X(3e5+2, 0);
        for (auto &p: P) {
            if (p.x <= l && p.y.x >= l) { X[p.y.x]++; X[p.y.y+1]--; }
        }

        pii ans{-1, 0};
        for (int i = 1; i <= 3e5; ++i) {
            X[i] += X[i-1];
            ans = max(ans, {X[i],i});
        }
        int x = ans.y;

        vector<int> Ans;
        for (int i = 0; i < N; ++i) {
            auto &p = P[i];
            if (p.x <= l && p.y.x >= l && p.y.x <= x && p.y.y >= x) {
                Ans.push_back(i+1);
            }
        }

        cout << best.x << '\n' << Ans;
        }
};
