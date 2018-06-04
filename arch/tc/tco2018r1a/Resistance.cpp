#include "../../../l/lib.h"
// #include "../l/mod.h"

class Resistance {
public:

    vector<bool> spies;
    vector<int> cnt;
    int tot;
    vector<string> M;

    void gen(int i, int P, int j, int S) {
        if (i == P) {
            if (j != S) return;

            for (string &m : M) {
                if (m[0] == 'F') {
                    bool ok = false;
                    for (int k = 0; k < P; ++k) {
                        if (m[k+1] == '1' && spies[k]) {
                            ok = true;
                        }
                    }
                    if (!ok) return;
                }
            }

            ++tot;
            for (int k = 0; k < P; ++k) {
                if (spies[k]) {
                    cnt[k]++;
                }
            }


        } else {
            if (j != S) {
                spies[i] = true;
                gen(i+1, P, j+1, S);
            }

            spies[i] = false;
            gen(i+1, P, j, S);

        }
    }

    vector <double> spyProbability(int P, int S, vector <string> missions) {
        M = missions;
        spies.resize(P);
        tot = 0;
        cnt = vector<int>(P, 0);
        gen(0, P, 0, S);
        if (tot == 0) {
            return {};
        } else {
            vector<double> res(P);
            for (int i = 0; i < P; ++i) {
                res[i] = double(cnt[i])/tot;
            }
            return res;
        }
    }

    void solve(istream& cin, ostream& cout) {
        int P,S,N;
        cin >> P >> S >> N;
        vector<string> M(N); cin >> M;
        cout << fixed << setprecision(10) << spyProbability(P,S,M);
    }
};
