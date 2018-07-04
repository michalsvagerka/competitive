#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int K; cin >> K;
    int G = 30;
    vector<string> S(3*G+2, string(3*G+2,'N'));
    auto a = [&](int c,int d) { S[c][d] = S[d][c] = 'Y'; };
    a(0,2);
    a(2*G+1,1);
    a(3*G+1,1);
    for (int i = 0; i < G-1; ++i) {
        a(2+i,3+i);
        a(2+i+G,3+i+G);
        a(2+i+2*G,3+i+G);
        a(2+i+G,3+i+2*G);
        a(2+i+2*G,3+i+2*G);
    }

    for (int b = 0; b < G; ++b) {
        if (K & (1<<b)) {
            a(G+1-b,2*G+1-b);
        }
    }

    cout << 3*G+2 << endl;
    for (string s:S) cout << s << '\n';
}
};
