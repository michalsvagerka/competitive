#include "../l/lib.h"

class EEarthWindAndFire {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> S(N);
        vector<int> T(N);
        for (int i = 0; i < N; ++i) {
            cin >> S[i].x;
            S[i].y = i+1;
        }
        cin >> T;
        sort(S.begin(),S.end());
        sort(T.begin(),T.end());
        ll A = 0, B = 0;
        for (pii s: S) A += s.x;
        for (int t: T) B += t;
        if (A != B) { cout << "NO\n"; return; }

        set<pair<pii,int>> L, R;
        for (int i = 0; i < N; ++i) {
            if (S[i].x < T[i]) {
                R.insert({{S[i].x, T[i]}, S[i].y});
            } else if (S[i].x > T[i]) {
                L.insert({{S[i].x, T[i]}, S[i].y});
            }
        }
        
        vector<pair<pii, int>> Ans;
        while (!R.empty()) {
            auto b = R.begin();
            auto l = L.lower_bound({{b->x.x + 2, -1}, -1});
            if (l == L.end()) { cout << "NO\n"; return; }
            auto r = prev(R.lower_bound({{l->x.x - 1, -1}, -1}));
            int d = min((l->x.x - r->x.x) / 2, min(l->x.x - l->x.y, r->x.y - r->x.x));
            auto A = *l, B = *r;
            L.erase(l); R.erase(r);
            Ans.push_back({{B.y, A.y}, d});
            A.x.x -= d;
            B.x.x += d;
            if (A.x.x != A.x.y) L.insert(A);
            if (B.x.x != B.x.y) R.insert(B);
        }
        
        cout << "YES\n";
        cout << Ans.size() << endl;
        for (auto &ans: Ans) cout << ans << '\n';
    }
};
