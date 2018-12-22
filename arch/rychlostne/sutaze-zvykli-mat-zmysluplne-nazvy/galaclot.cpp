#include "../l/lib.h"
#include "../l/bigint.h"

class galaclot {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        Num X; cin >> X;

        vector<pair<Num, string>> L(N);
        for (int i = 0; i < N; ++i) {
            cin >> L[i].y >> L[i].x;
        }

        sort(L.begin(),L.end());
        reverse(L.begin(),L.end());
        vector<string> Ans;
        for (auto &l: L) {
            if (X >= l.x) {
                X -= l.x;
                Ans.push_back(l.y);
            }
        }
        
        if (X == 0) {
            cout << Ans.size() << '\n';
            for(auto s:Ans) cout << s << '\n';
        } else {
            cout << "0\n";
        }
    }
};
