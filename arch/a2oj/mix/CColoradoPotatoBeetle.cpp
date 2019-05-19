#include "../l/lib.h"
// #include "../l/mod.h"

class CColoradoPotatoBeetle {
public:
    vector<int> RG, CG;
    vector<vector<int>> S;

    void dfs(int x, int y) {
        if (x >= 0 && x < RG.size() && y >= 0 && y < CG.size() && !S[x][y]) {
            S[x][y] = 2;
            dfs(x+1, y);
            dfs(x-1, y);
            dfs(x, y+1);
            dfs(x, y-1);
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int r = 0, c = 0;

        set<int> R, C;
        R.insert(-2e9);
        R.insert(2e9);
        C.insert(-2e9);
        C.insert(2e9);
        vector<pair<char,int>> T;
        for (int i = 0; i < N; ++i) {
            char d; int l;
            cin >> d >> l;
            T.push_back({d,l});
            R.insert(r-1);
            R.insert(r);
            R.insert(r+1);
            C.insert(c-1);
            C.insert(c);
            C.insert(c+1);
            switch (d) {
                case 'U':
                    r -= l;
                    break;
                case 'D':
                    r += l;
                    break;
                case 'R':
                    c += l;
                    break;
                case 'L':
                    c -= l;
                    break;
            }
            R.insert(r-1);
            R.insert(r);
            R.insert(r+1);
            C.insert(c-1);
            C.insert(c);
            C.insert(c+1);
        }

        RG = vector<int>(R.begin(),R.end());
        CG = vector<int>(C.begin(),C.end());
        map<int, int> RI, CI;
        for (int i = 0; i < RG.size(); ++i) RI[RG[i]] = i;
        for (int i = 0; i < CG.size(); ++i) CI[CG[i]] = i;
        S = vector2<int>(RG.size(), CG.size(), 0);

        r = c = 0;
        for (int i = 0; i < N; ++i) {
            char d = T[i].x; int l = T[i].y;
            switch (d) {
                case 'U':
                    for (int j = RI[r-l]; j <= RI[r]; ++j) S[j][CI[c]] = 1;
                    r -= l;
                    break;
                case 'D':
                    for (int j = RI[r]; j <= RI[r+l]; ++j) S[j][CI[c]] = 1;
                    r += l;
                    break;
                case 'R':
                    for (int j = CI[c]; j <= CI[c+l]; ++j) S[RI[r]][j] = 1;
                    c += l;
                    break;
                case 'L':
                    for (int j = CI[c-l]; j <= CI[c]; ++j) S[RI[r]][j] = 1;
                    c -= l;
                    break;
            }
        }
        
        dfs(0,0);

        ll ans = 0;
        for (int i = 0; i < RG.size(); ++i) {
            for (int j = 0; j < CG.size(); ++j) {
                if (S[i][j] != 2) {
                    ans += ll(RG[i+1] - RG[i]) * (CG[j+1] - CG[j]);
                }
            }
        }
        cout << ans << endl;
    }
};
