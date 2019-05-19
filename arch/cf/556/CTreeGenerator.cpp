#include "../l/lib.h"
#include "../l/nsegtree.h"

class CTreeGenerator {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q;
        cin >> N >> Q;
        string S; cin >> S;

        int MX = 2*N-3;
        vector<int> Init(MX+1);
        int d = 0;
        for (int i = 0; i <= MX; ++i) {
            d += (S[i] == '(') - (S[i] == ')');
            Init[i] = d;
        }

        LAddMaxTree<int> Depth(Init, 0, 0);
        vector<int> Ans(MX+1);
        for (int i = 0; i <= MX; ++i) {
            Ans[i] = -2*Init[i];
            if (i != 0) Ans[i] += Depth.get(0, i-1);
            if (i != MX) Ans[i] += Depth.get(i+1, MX);
        }
        LAddMaxTree<int> Wow(Ans, 0, 0);

        int a, b;
        auto sufFix = [&](int c, int d, int e) {
            int ff = Depth.longestSuffix(b-1, [&](int v) { return v < c; }) - 1;
            int gg = Depth.longestSuffix(a-1, [&](int v) { return v < d; }) - 1;
            if (gg == -1) gg = 0;
            Wow.put(gg, ff-1, e);
        };

        auto prefFix = [&](int c, int d, int e) {
            int ff = Depth.longestPrefix(a, [&](int v) { return v < c; }) + 1;
            int gg = Depth.longestPrefix(b, [&](int v) { return v < d; }) + 1;
            if (gg > MX) gg = MX;
            Wow.put(ff+1, gg, e);
        };

        cout << Wow.get(0, MX) << '\n';
        for (int q = 0; q < Q; ++q) {
            cin >> a >> b;
            --a; --b;
            if (a > b) swap(a,b);

            int l = Depth.get(0, a-1);
            int m = Depth.get(a, b-1);
            int r = Depth.get(b, MX);
            int g = (S[a] == ')') - (S[a] == '(');

            if (m >= r-g) sufFix(r-g, m+g+1, g);
            if (m >= r-g+1) sufFix(r+1-g, m+g, g);
            if (m >= l-g) prefFix(l-g, m+g+1, g);
            if (m >= l-g+1) prefFix(l+1-g, m+g, g);
            Depth.put(a, b-1, 2*g);
            Wow.put(a, b-1, -4*g);
            swap(S[a], S[b]);
            
            cout << Wow.get(0, MX) << '\n';
        }
    }
};
