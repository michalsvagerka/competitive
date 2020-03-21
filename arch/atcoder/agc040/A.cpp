#include "../l/lib.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();

        vector<int> X;
        for (int i = 0; i < N; ++i) {
            if (i == 0 || S[i] != S[i-1]) {
                X.push_back(1);
            } else {
                X.back()++;
            }
        }

        ll ans = 0;
        for (int x: X) {
            ans += ll(x)*ll(x-1)/2;
        }
        
        for (int i = (S[0] == '<'); i <= X.size(); i += 2) {
            int l = i == 0 ? 0 : X[i-1];
            int r = i == X.size() ? 0 : X[i];
            ans += max(l,r);
        }
        
        cout << ans << endl;
    }
};
