#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class serejaandsets {
public:
    void solve(istream& cin, ostream& cout) {
        auto F = FieldMod::fact(2000);
        auto I = FieldMod::invfact(2000);

        int N, K; cin >> N >> K;
        if (K == 0) {
            cout << "1\n";
            return;
        }

        vector<FieldMod> PW(N*N+1, 1);
        for (int i = 1; i <= N*N; ++i) PW[i] = PW[i-1] * 2;

        vector2<FieldMod> W(N+1,K+1,0);
        W[0][0] = 1;
        for (int i = 1; i <= N; ++i) {
            W[i][1] += PW[i]-1;
            for (int j = 0; j < i; ++j) {
                for (int k = 1; k < K; ++k) {
                    if (W[j][k] == 0) break;
                    // add one
                    // (i-j) options for begin
                    // additional j begins * (i-j) ends
                    W[i][k+1] += W[j][k] * (PW[i-j]-1) * PW[j*(i-j)];
                }
            }
        }


        FieldMod ans = 0;
        for (int i = 0; i <= N; ++i) ans += W[i][K] * PW[i*(N-i)];
        cout << ans << endl;
    }
};
