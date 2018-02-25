#include "../../../l/lib.h"
#include "../../../l/mod.h"

class TaskE {
public:
    vector<FieldMod> F,I,P;

    FieldMod brute(int N, int K) {
        FieldMod ans = 0;
        for (int i = 1; i <= N; ++i) {
            ans += P[i] * F[N] * I[N - i] * I[i];
        }
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        F = FieldMod::fact(2*K + 1);
        I = FieldMod::invfact(2*K + 1);

        P.resize(2*K+1);
        for (int i = 0; i <= 2*K; ++i) {
            P[i] = FieldMod{i}.pow(K);
        }

        if (N <= 2*K) {
            cout << brute(N,K) << endl;
        } else {
            FieldMod p = 2;
            vector<FieldMod> Ext(2*K+1, 0);
            for (int i = 0; i <= K; ++i) {
                Ext[i] = brute(i, K);
                Ext[i] *= p.pow(K-i);
            }

            FieldMod ans = 0;
            for (int i = 0; i <= K; ++i) {
                FieldMod l = 1, k = 1;
                for (int j = 0; j <= K; ++j) {
                    if (i!=j) {
                        l *= FieldMod{N}-j;
                        k *= FieldMod{i}-j;
                    }
                }
                ans += l * Ext[i] / k;
            }

            cout << ans * p.pow(N-K);
        }
    }
};
