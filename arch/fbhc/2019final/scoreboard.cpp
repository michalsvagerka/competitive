#include "../l/lib.h"

class scoreboard {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            vector<string> S(N); cin >> S;
            bool possible = false;
            vector<bool> CanBeat(N, false);
            for (int i = 1; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (S[0][j] == 'Y' && S[i][j] == 'N') CanBeat[i] = true;
                }
            }

            for (int j = 1; j < N && !possible; ++j) {
                vector<bool> Tie(N, true);
                for (int k = 0; k < M; ++k) {
                    if (S[0][k] == 'Y' && S[j][k] == 'Y') {
                        for (int l = 0; l < N; ++l) {
                            Tie[l] = Tie[l] && S[l][k] == 'Y';
                        }
                    }
                }

                for (int k = 0; k < M; ++k) {
                    if (S[j][k] == 'Y' && S[0][k] == 'N') {
                        bool ok = true;
                        for (int i = 0; i < N; ++i) {
                            if (i != j && i != 0) {
                                if (S[i][k] == 'Y' && Tie[i]) ok = false;
                                if (Tie[i] && !CanBeat[i]) ok = false;
                            }
                        }
                        if (ok) possible = true;
                    }
                }
            }


            cout << "Case #" << t+1 << ": " << "NY"[possible] << '\n';
        }
    }
};
