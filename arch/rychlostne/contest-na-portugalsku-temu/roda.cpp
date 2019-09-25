#include "../l/lib.h"


class roda {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        cout << fixed << setprecision(10);
        vector<double> Prob(1<<N, 0);
        vector<double> Wait(N, 0);
        vector<int> Next(N);
        Prob[0] = 1;
        for (int i = 0; i < (1<<N)-1; ++i) {
            int x = __builtin_popcount(i);
            int t = 0;
            int f = 0;
            while ((i>>f)&1) ++f;
            for (int j = N-1; j >= 0; --j) {
                if (0 == ((i>>j)&1)) f = j;
                Next[j] = f;
            }
            
            for (int j = 0; j < N; ++j) {
                int k = Next[j] - j + N;
                k = k >= N ? k - N : k;
                t += k;
                Prob[i|(1<<Next[j])] += Prob[i] / N;
            }
            Wait[x] += t * Prob[i] / N;
        }

        for (int i = 0; i < N; ++i) {
            cout << Wait[i] << '\n';
        }
    }
};
