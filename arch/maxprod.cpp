#include "../l/lib.h"
// #include "../l/mod.h"

const double EULER = 2.71828182845904523536;

class maxprod {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        auto c = (int)floor(N / EULER);
        int d = c + 1;
        double cc = pow(1.0*N/c,c);
        double dd = pow(1.0*N/d,d);
        double qc = c*log10(1.0*N/c);
        double qd = d*log10(1.0*N/d);
        double P = max(cc,dd);
        if (P < 1e9-0.5) cout << (int)round(P);
        else cout << 1+(int)floor(max(qc,qd));
        cout << '\n';
    }
};
