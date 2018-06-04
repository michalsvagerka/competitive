#include "../../../l/lib.h"
// #include "../l/mod.h"

class ma3xparity {
public:
    void solve(istream& cin, ostream& cout) {
        string X,Y; cin >> X >> Y;
        int S = X.size(), T = Y.size();
        reverse(X.begin(),X.end());
        reverse(Y.begin(),Y.end());

        int s = 0, t = 0;
        for (char x: X) s += x == '1';
        for (char y: Y) t += y == '1';
        if ((s+t)%2==1) {
            cout << "-1\n";
            return;
        }

        vector<string> A(S, string(T, '1'));
        vector<int> P,Q;
        for (int i = 0; i < S; ++i) if ((X[i]=='0')==T%2) P.push_back(i);
        for (int i = 0; i < T; ++i) if ((Y[i]=='0')==S%2) Q.push_back(i);
        for (int i = 0; i < min(P.size(),Q.size()); ++i) A[P[i]][Q[i]] = '0';
        for (int i = Q.size(); i < P.size(); ++i) A[P[i]][T-1] = '0';
        for (int i = P.size(); i < Q.size(); ++i) A[S-1][Q[i]] = '0';

        reverse(A.begin(),A.end());
        for (string &a:A) {
            reverse(a.begin(),a.end());
            cout << a << '\n';
        }
    }
};
