#include "../l/lib.h"

class zenit17skb {
public:
    void solve(istream& cin, ostream& cout) {
        int J,E; cin >> J >> E;
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        int j = count(A.begin(),A.end(),J);
        int e = count(A.begin(),A.end(),E);
        if (j > e) cout << "Jergus\n";
        else if (j < e) cout << "Ema\n";
        else cout << "remiza\n";
    }
};
