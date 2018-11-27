#include "../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> P(2*N); cin >> P;
        vector<int> S(2*N, -1);
        vector<bool> A(2*N, true);
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            --a; --b;
            S[a] = b;
            S[b] = a;
        }

        int T; cin >> T;
        bool me = T == 1;
        int last = -1;
        for (int i = 0; i < 2*N; ++i) {
            if (me) {
                if (last != -1 && S[last] != -1 && A[S[last]]) {
                    cout << S[last] + 1 << endl;
                    A[S[last]] = false;
                } else {
                    
                    bool playedCouple = false;
                    for (int j = 0; j < 2*N; ++j) {
                        if (A[j] && S[j] != -1) {
                            int k = S[j];
                            if (P[k] > P[j]) {
                                cout << k + 1 << endl;
                                A[k] = false;
                            } else {
                                cout << j + 1 << endl;
                                A[j] = false;
                            }
                            
                            playedCouple = true;
                            break;
                        }
                    }
                    
                    if (!playedCouple) {
                        pii best = {-1, -1};
                        for (int j = 0; j < 2*N; ++j) {
                            if (A[j]) {
                                best = max(best, {P[j], j});
                            }
                        }
                        A[best.y] = false;
                        cout << best.y + 1 << endl;
                    };
                }
            } else {
                cin >> last;
                --last;
                A[last] = false;
            }
            
            me = !me;
        }

    }
};
