#include "../l/lib.h"

class straze {
public:
    int read(istream& cin) {
        int h,m,s; char c,d;
        cin >> h >> c >> m >> d >> s;
        return h*60*60 + m*60 + s;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        char t;
        vector<ll> C(86402, 0);
        for (int i = 0; i < N; ++i) {
            int a = read(cin);
            cin >> t;
            int b = read(cin);
            C[a]++;
            C[b+1]--;
            if (a > b) {
                C[86400]--;
                C[0]++;
            }
        }

        for (int i = 0; i <= 86400; ++i) C[i+1] += C[i];
        for (int i = 0; i <= 86400; ++i) C[i+1] += C[i];
        for (int i = 86401; i > 0; --i) C[i] = C[i-1];
        C[0] = 0;

        int Q; cin >> Q;
        cout << fixed << setprecision(10);
        for (int q = 0; q < Q; ++q) {
            int a = read(cin);
            cin >> t;
            int b = read(cin);
            ll c = C[b+1] - C[a], d = b-a+1;
            if (d < 1) {
                c += C[86400];
                d += 86400;
            }
            cout << (double)c/d << '\n';
        }
    }
};
