#include "../l/lib.h"
// #include "../l/mod.h"

class database {
public:
    void solve(istream& cin, ostream& cout) {
        ui R, C; cin >> R >> C;
        string s; getline(cin, s);
        vector<pair<ui, vector<string>>> S(R);
        for (ui r = 0; r < R; ++r) {
            S[r].x = r+1;
            getline(cin, s);
            auto it = s.begin();
            for (ui c = 0; c < C-1; ++c) {
                auto comma = find(it, s.end(), ',');
                S[r].y.push_back(string(it, comma));
                it = comma+1;
            }
            S[r].y.push_back(string(it, s.end()));
        }

        for (int c1 = 0; c1 < C; ++c1) {
            for (int c2 = c1+1; c2 < C; ++c2) {
                sort(S.begin(),S.end(),
                     [=](const pair<ui, vector<string>>&a, const pair<ui, vector<string>>&b) {
                        return a.y[c1] < b.y[c1] || (a.y[c1] == b.y[c1] && a.y[c2] < b.y[c2]);
                     });

                for (int i = 0; i < R-1; ++i) {
                    if (S[i].y[c1] == S[i+1].y[c1] && S[i].y[c2] == S[i+1].y[c2]) {
                        cout << "NO\n";
                        cout << S[i].x << ' ' << S[i+1].x << '\n';
                        cout << c1+1 << ' ' << c2+1 << '\n';
                        return;
                    }
                }
            }
        }

        cout << "YES\n";
    }
};
