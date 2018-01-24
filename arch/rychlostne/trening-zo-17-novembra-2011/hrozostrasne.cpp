#include "../l/lib.h"
// #include "../l/mod.h"

class hrozostrasne {
public:


    void solve(istream& cin, ostream& cout) {
        map<char,int> Z;
        for (char i:"aeiouyAEIOUY") Z[i] = 1;
        for (char i:"bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ") Z[i] = 2;

        int N; cin >> N;
        string S;
        getline(cin, S);
        for (int i = 0; i < N; ++i) {
            getline(cin, S);
            vector<int> C(3,0);
            for (char c:S) C[Z[c]]++;
            cout << fixed << setprecision(12) << 100.0*C[1]/(C[1]+C[2]) << '\n';
        }
    }
};
