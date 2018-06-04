#include "../../../l/lib.h"
#include "../../../l/string.h"
#include "../../../l/fft.h"

class fuzzysearch {
public:
    typedef Field<998244353u> FT;

    int trans(char c) {
        if (c=='A') return 0; else if (c=='G') return 1; else if (c=='C') return 2; else return 3;
    }

    void solve(istream& cin, ostream& cout) {
        int s,t, K; cin >> s >> t >> K;
        string S; cin >> S;
        string T; cin >> T;
        vector2<FT> D(4, 2*s, 0), E(4, 2*s, 0);
        for (int i = 0; i < s; ++i) {
            int j = trans(S[i]);
            D[j][max(0, i-K)]++;
            D[j][min(s, i+K+1)]--;
        }

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < s; ++j) {
                D[i][j+1] += D[i][j];
                if (D[i][j] != 0) D[i][j]=1;
            }
            for (int j = 0; j < t; ++j) {
                int k = trans(T[j]);
                E[k][t-j-1] = 1;
            }
        }


//        cout << D << E;

        FFT<998244353u> F;
        for (int j = 0; j < 4; ++j) {
            F.fft(D[j]);
            F.fft(E[j]);
            for (int i = 0; i < D[j].size(); ++i) D[j][i] *= E[j][i];
            F.fft(D[j], true);
        }

        vector<int> Q(s, 0);
        for (int i = 0; i < s; ++i) {
            for (int j = 0; j < 4; ++j) {
                Q[i] += (ui)D[j][i+t-1];
            }
        }
//        cout << Q;
//        cout << D;

        cout << count(Q.begin(),Q.end(),t) << endl;
    }
};
