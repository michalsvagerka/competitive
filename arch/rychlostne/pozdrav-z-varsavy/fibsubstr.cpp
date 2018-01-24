#include "../l/lib.h"
#include "../l/string.h"

class fibsubstr {
public:
    void solve(istream& cin, ostream& cout) {
        ui t = 0, N;
        while (true) {
            string S; cin >> N >> S;
            if (S.empty()) return;
            int z = S.size()-1;
            KMP<string> K(S);
            vector<string> B(N+1), E(N+1);
            vector<ll> C(N+1,S=="0");
            if (z) B[0] = E[0] = "0";
            if (N != 0) {
                B[1] = E[1] = (z == 0 ? "" : "1");
                C[1] = S == "1";
            }
            for (int i = 2; i <= N; ++i) {
                C[i] = C[i-1] + C[i-2] + K.search(E[i-1] + B[i-2]).size();

                B[i] = B[i-1];
                if (B[i].size() < z) {
                    B[i] += B[i-2];
                    if (B[i].size() > z) B[i] = B[i].substr(0, z);
                }

                E[i] = E[i-2];
                if (E[i].size() < z) {
                    E[i] = E[i-1] + E[i-2];
                    if (E[i].size() > z) {
                        E[i] = E[i].substr(E[i].size()-z);
                    }
                }
            }
            cout << "Case " << ++t << ": " << C[N] << endl;
        }
    }
};
