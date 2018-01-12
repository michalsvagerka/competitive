#include "../l/lib.h"
// #include "../l/mod.h"

class childgame {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        while(N) {
            vector<string> S(N); cin >> S;
            sort(S.begin(),S.end(),[](const string&a,const string&b) {
                return a+b > b+a;
            });

            for (auto &s:S) cout << s;
            cout << endl;

            cin >> N;
        }
    }
};
