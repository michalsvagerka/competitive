#include "../../../l/lib.h"

class BATideOfRiverscape {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        string S; cin >> S;

        bool ok = false;
        for (int i = 0; i < K; ++i) {
            if (i+K >= N && S[i] == '.') S[i] = '1';

            for (int j = i+K; j < N; j += K) {
                if (S[i] == '.') {
                    if (S[j] == '.') {
                        S[j] = '1';
                        S[i] = '0';
                    } else {
                        S[i] = "01"[S[j]=='0'];
                    }
                } else if (S[j] == '.') {
                    S[j] = "01"[S[i]=='0'];
                }

                ok |= S[i] != S[j];
            }
        }
        if (ok) {
            cout << S << endl;
        } else {
            cout << "No\n";
        }
    }
};
