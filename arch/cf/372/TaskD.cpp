#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    int Z = 50;
    ll L; cin >> L;


    ll P = 1;
    vector<pair<pii,pii>> Ans;
    for (int i = 0; i <= Z-6; i += 2) {
        int M = L % 6;
        L = L/6;
        P *= 6;

        Ans.push_back({{i+1,i+4},{i+1,i+5}});
        if (i != Z-6) Ans.push_back({{i+2,i+6},{i+2,i+7}});

        Ans.push_back({{i+4,i+1},{i+5,i+1}});
        if (i != Z-6) Ans.push_back({{i+6,i+2},{i+7,i+2}});

        if (M == 0 || M == 3) Ans.push_back({{i+1,i+3},{i+1,i+4}});
        if (M < 3) Ans.push_back({{i+2,i+3},{i+2,i+4}});
        Ans.push_back({{i+2,i+4},{i+3,i+4}});
        Ans.push_back({{i+2,i+5},{i+3,i+5}});

        if (M != 2 && M != 5) Ans.push_back({{i+3,i+1},{i+4,i+1}});
        Ans.push_back({{i+3,i+2},{i+4,i+2}});
        Ans.push_back({{i+4,i+2},{i+4,i+3}});
        Ans.push_back({{i+5,i+2},{i+5,i+3}});

    }
    
    if (L == 0) Ans.push_back({{Z-1,Z-3}, {Z,Z-3}});
    Ans.push_back({{Z-1,Z-2}, {Z,Z-2}});
    Ans.push_back({{Z-1,Z-1}, {Z,Z-1}});

    Ans.push_back({{Z-3,Z-1}, {Z-3,Z}});
    Ans.push_back({{Z-2,Z-1}, {Z-2,Z}});
    Ans.push_back({{Z-1,Z-1}, {Z-1,Z}});

    cout << "50 50\n";
    cout << Ans.size() << endl;
    for (auto ans: Ans) {
        cout << ans << endl;
    }
}
};
