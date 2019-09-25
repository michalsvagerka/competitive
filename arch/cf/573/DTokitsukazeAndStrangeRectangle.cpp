#include "../l/lib.h"
#include "../l/fenwick.h"

class DTokitsukazeAndStrangeRectangle {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> A(N); cin >> A;
        set<int> X, Y;
        for (pii a: A) { X.insert(a.x); Y.insert(a.y); }
        map<int,int> IX, IY;
        int M = 0;
        for (int x: X) IX[x] = M++;
        int P = 0;
        for (int y: Y) IY[y] = P++;
        vector<vector<int>> B(P);
        for (pii a: A) B[P-1-IY[a.y]].push_back(IX[a.x]);
        Fenwick<int> F(M, 0);
        ll ans = 0;
        for (auto &b: B) {
            sort(b.begin(),b.end());
            for (int x : b) if (F.get(x) == 0) F.add(x, 1);
            ll g = F.range(0, M-1);
            ans += g*(g+1)/2;
            for (int i = 0; i < b.size()-1; ++i) {
                if (b[i] + 1 != b[i+1]) {
                    g = F.range(b[i] + 1, b[i+1] - 1);
                    ans -= g*(g+1)/2;
                }
            }
            if (b[0] != 0) {
                g = F.range(0, b[0]-1);
                ans -= g*(g+1)/2;
            }
            if (b.back() != M-1) {
                g = F.range(b.back()+1, M-1);
                ans -= g*(g+1)/2;
            }
        }
        cout << ans << endl;
    }
};
