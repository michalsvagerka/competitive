#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr int S = 400001;

class Deadfish {
public:
    int shortestCode(int N) {
        vector<vector<int>> E(S);
        for (int i = 0; i < S; ++i) {
            if (i != 0) E[i].push_back(i-1);
            if (i != S-1) E[i].push_back(i+1);
            if (i < 1000) E[i].push_back(i*i);

            stringstream ss; ss << i;
            string s = ss.str();
            sort(s.begin(),s.end());
            reverse(s.begin(),s.end());
            stringstream st(s);
            int j; st >> j;
            E[i].push_back(j);
        }

        vector<int> D(S, -1);
        D[0] = 0;
        vector<int> Q{0};
        for (int i = 0; i < Q.size(); ++i) {
            for (int j: E[Q[i]]) {
                if (j < S && D[j] == -1) {
                    D[j] = D[Q[i]]+1;
                    Q.push_back(j);
                }
            }
        }


        return D[N];
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        cout << shortestCode(N) << endl;
    }
};
