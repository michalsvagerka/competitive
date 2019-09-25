#include "../l/lib.h"
#include "../l/util.h"

class Datacenter {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int R, C; cin >> R >> C;
            vector<string> S(R); cin >> S;
            cout << "Case #" << t+1 << ": ";
            UnionFind UF(R*C);
            vector<string> Ans(R-1, string(C-1,'.'));

            auto idx = [&](int r, int c) { return r*C + c; };
            vector<pii> Pt;
            for (int r = 0; r < R-1; ++r) {
                for (int c = 0; c < C - 1; ++c) {
                    if (S[r][c] == S[r+1][c+1] && S[r+1][c] == S[r][c+1] && S[r][c] != S[r+1][c]) {
                        Pt.push_back({r,c});
                    }
                }
            }

            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    if (r != R-1 && S[r][c] == S[r+1][c]) {
                        UF.unite(idx(r,c),idx(r+1,c));
                    }
                    if (c != C-1 && S[r][c] == S[r][c+1]) {
                        UF.unite(idx(r,c),idx(r,c+1));
                    }
                }
            }
            
            while (true) {
                if (Pt.empty()) break;
                
                bool any = false;
                for (int i = 0; i < Pt.size(); ++i) {
                    pii p = Pt[i];
                    if (UF.united(idx(p.x,p.y),idx(p.x+1,p.y+1))) {
                        UF.unite(idx(p.x,p.y+1),idx(p.x+1,p.y));
                        Ans[p.x][p.y] = '/';
                        any = true;
                        swap(Pt[i], Pt[Pt.size()-1]); Pt.pop_back();
                    } else if (UF.united(idx(p.x+1,p.y),idx(p.x,p.y+1))) {
                        UF.unite(idx(p.x,p.y),idx(p.x+1,p.y+1));
                        Ans[p.x][p.y] = '\\';
                        any = true;
                        swap(Pt[i], Pt[Pt.size()-1]); Pt.pop_back();
                    }
                }
                
                if (!any) {
                    sort(Pt.begin(),Pt.end());
                    pii p = Pt[0];
                    UF.unite(idx(p.x,p.y+1),idx(p.x+1,p.y));
                    Ans[p.x][p.y] = '/';
                    swap(Pt[0], Pt[Pt.size()-1]);
                    Pt.pop_back();
                }
            }

            if (UF.comp > 2) {
                cout << "IMPOSSIBLE\n";
            } else {
                cout << "POSSIBLE\n";
                for (string&ans: Ans) cout << ans << '\n';
            }
        }
    }
};
