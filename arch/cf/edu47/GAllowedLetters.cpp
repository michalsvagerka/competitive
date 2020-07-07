<<<<<<< HEAD
#include "../l/lib.h"
=======
#include "../../../l/lib.h"
>>>>>>> Another bunch.

class GAllowedLetters {
public:
    void solve(istream& cin, ostream& cout) {

        string S; cin >> S;
        int N = S.size();
        vector<int> X(N, 63), Cur(64, 0);
        int M; cin >> M;
        for (int i = 0; i < M; ++i) {
            int j; cin >> j; --j;
            string T; cin >> T;
            X[j] = 0;
            for (char t: T) X[j] ^= 1<<(t-'a');
        }

        auto add = [&](int mask, int val) {
            for (int i = 0; i < 64; ++i) if (mask&i) Cur[i] += val;
        };

        for (int i = 0; i < N; ++i) {
            add(1<<(S[i]-'a'), -1);
            add(X[i], 1);
        }

        for (int i = 0; i < 64; ++i) {
            if (Cur[i] < 0) {
                cout << "Impossible\n";
                return;
            }
        }

        string T; cin >> T;
        for (int i = 0; i < N; ++i) {
            add(X[i], -1);
            for (int j = 0; j < 6; ++j) {
                if ((X[i]&1<<j)) {
                    add(1<<j, 1);
                    if (*min_element(Cur.begin(),Cur.end()) == 0) {
                        T += char('a'+j);
                        break;
                    }
                    add(1<<j, -1);
                }
            }
        }
        cout << T << '\n';
    }
};
