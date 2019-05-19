#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<1000000000> FF;

class traildig {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, K; cin >> N >> M >> K;
        while (N % 10 == 0) N /= 10;
        FF ans = 0;
        if (N%2 == 0) {
            int p = 0;
            while (N % 2 == 0) { N /= 2; ++p; }
            ans = FF{5}.pow(p*M);
        } else {
            int p = 0;
            while (N % 5 == 0) { N /= 5; ++p; }
            ans = FF{2}.pow(p*M);
        }

        ll prt = ui(ans) + 10000000000LL;
        stringstream ss;
        ss << prt;
        string s = ss.str();
        cout << s.substr(11-K, K) << endl;
    }
};
