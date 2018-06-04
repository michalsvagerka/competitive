#include "../../../l/lib.h"
// #include "../l/mod.h"

class serejaandsquares {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> S(N); cin >> S;
        unordered_set<pii> T(S.begin(),S.end());
        vector<vector<pii>> H(1e5+1),V(1e5+1),D(2e5+1);
        for (pii&s:S) {
            H[s.x].push_back(s);
            V[s.y].push_back(s);
            D[s.x-s.y+1e5].push_back(s);
        }

        auto has = [&](pii g) { return T.find(g) != T.end(); };

        int ans = 0;
        for (pii&s:S) {
            if (H[s.x].size() <= V[s.y].size() && H[s.x].size() <= D[s.x-s.y+1e5].size()) {
                for (pii&t:H[s.x]) {
                    ans += t.y > s.y && has({s.x+t.y-s.y,s.y}) && has({s.x+t.y-s.y,t.y});
                }
            } else if (V[s.y].size() <= D[s.x-s.y+1e5].size()) {
                for (pii&t:V[s.y]) {
                    ans += t.x > s.x && has({s.x,s.y+t.x-s.x}) && has({t.x, s.y+t.x-s.x});
                }
            } else {
                for (pii&t:D[s.x-s.y+1e5]) {
                    ans += t.x > s.x && has({s.x,t.y}) && has({t.x,s.y});
                }
            }
        }
        cout << ans << endl;
    }
};
